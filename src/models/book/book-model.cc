#include "book-model.hxx"
#include <fmt/format.h>

using namespace api::v1;

Json::Value BookModel::find() {
    Json::Value response;
    try {
        const auto &database = MongoDb::getConnection();
        auto collection = database["book"];

        mongocxx::pipeline pipeline;
        mongocxx::options::aggregate aggregate;
        aggregate.allow_disk_use(true);
        aggregate.max_time(std::chrono::seconds(15));

        pipeline.lookup(bsoncxx::from_json(R"({
            "from": "user",
            "localField": "user_id",
            "foreignField": "_id",
            "as": "user"
        })"))
                .match(bsoncxx::from_json(R"({
            "user.template.__deleted__": false,
            "template.__deleted__": false
        })"))
                .project(bsoncxx::from_json(R"({
            "user_id": 0,
            "template": 0,
            "user.template": 0,
            "user.password": 0
        })"))
                .unwind("$user");

        auto cursor = collection.aggregate(pipeline, aggregate);

        response["statusCode"] = 200;
        response["message"] = Json::arrayValue;
        Json::Reader reader;
        for (auto &&document: cursor) {
            Json::Value value;
            reader.parse(bsoncxx::to_json(document), value);
            response["body"].append(value);
        }

    } catch (const std::runtime_error &ex) {
        LOG_DEBUG << ex.what();
        response["statusCode"] = 500;
        response["message"]["error_code"] = "ERROR";
        response["message"]["message"] = fmt::format("Error: {}", ex.what());
        response["body"] = Json::arrayValue;
    }
    return response;
}

bool BookModel::insert(Json::Value &body, std::string &&userId, std::string &&workspace, std::string &&ip) {
    try {
        auto db = MongoDb::getConnection();
        auto bookColl = db["book"];

        auto builder = bsoncxx::builder::stream::document();

        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);


        auto docInsert = builder <<
                                 "_id" << drogon::utils::getUuid() <<
                                 "name" << body["name"].asString() <<
                                 "description" << body["description"].asString() <<
                                 "image" << "https://i.imgur.com/gf8iePU.jpeg" <<
                                 "user_id" << userId <<
                                 "template" << bsoncxx::builder::stream::open_document <<
                                 "__create_date__" << std::ctime(&now_time) <<
                                 "__update_date__" << std::ctime(&now_time) <<
                                 "__workspace_create__" << workspace <<
                                 "__workspace_update__" << workspace <<
                                 "__ip_request__" << ip <<
                                 "__deleted__" << false <<
                                 bsoncxx::builder::stream::close_document;

        bsoncxx::document::value docValue = docInsert << bsoncxx::builder::stream::finalize;
        bookColl.insert_one(docValue.view());
        return true;

    } catch (const std::runtime_error &ex) {
        LOG_DEBUG << ex.what();
        return false;
    }
}

bool BookModel::update(std::string &&bookId, Json::Value &body, std::string &&userId, std::string &&workspace,
                       std::string &&ip) {
    try {
        auto db = MongoDb::getConnection();
        auto collection = db["book"];

        auto builder = bsoncxx::builder::stream::document();

        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        auto document = builder << "$set" <<
                                bsoncxx::builder::stream::open_document <<
                                    "name" << body["name"].asString() <<
                                    "description" << body["description"].asString() <<
                                    "user_id" << userId <<
                                    "template.__update_date__" << std::ctime(&now) <<
                                    "template.__workspace_update__" << workspace <<
                                    "template.__ip_request__" << ip <<
                                bsoncxx::builder::stream::close_document <<
                                bsoncxx::builder::stream::finalize;


        auto filter = bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("_id", bookId),
                bsoncxx::builder::basic::kvp("template.__deleted__", false)
        );

        collection.update_one(
                filter.view(),
                document.view()
        );

        return true;

    } catch (const std::runtime_error &ex) {
        LOG_DEBUG << ex.what();
        return false;
    }
}
