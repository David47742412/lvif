#include "book-model.hxx"

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
        })"));

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
