#include "user-model.hxx"

using namespace api::v1;

std::shared_ptr<UserModel> api::v1::UserModel::findByEmailOrUsername(std::string &emailOrUsername) {
    try {
        auto db = MongoDb::getConnection();
        auto userColl = db["user"];
        std::regex regexPattern("^[A-Za-z0-9+_.-]+@(.+)$"); // email?
        std::string &&prop = std::regex_match(emailOrUsername, regexPattern) ? "email" : "username";
        auto filter = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp(prop, emailOrUsername));

        auto userDb = userColl.find_one(filter.view());
        if (!userDb) {
            return nullptr;
        }

        std::shared_ptr<UserModel> userResult = std::make_shared<UserModel>();
        userResult->_id = (*userDb)["_id"].get_string();
        userResult->alias = (*userDb)["alias"].get_string();
        userResult->image = (*userDb)["image"].get_string();
        userResult->lastName = (*userDb)["lastName"].get_string();
        userResult->name = (*userDb)["name"].get_string();
        userResult->password = (*userDb)["password"].get_string();
        userResult->username = (*userDb)["username"].get_string();

        return userResult;

    } catch (const std::runtime_error &ex) {
        LOG_DEBUG << ex.what();
        throw ex;
    }
}

Json::Value UserModel::toJson() {
    Json::Value objValue;

    objValue["_id"] = this->_id;
    objValue["alias"] = this->alias;
    objValue["image"] = this->image;
    objValue["lastName"] = this->lastName;
    objValue["name"] = this->name;
    objValue["username"] = this->username;

    return objValue;
}
