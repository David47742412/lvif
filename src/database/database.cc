#include "database.hxx"

using namespace api::v1;

void MongoDb::init() {
    const auto env = drogon::app().getCustomConfig();
    mongocxx::instance instance{};
    std::string&& conn = env["database"]["uri"].asString();
    Client = mongocxx::client{mongocxx::uri{conn}};
    Db = Client[env["database"]["name"].asString()];
}

mongocxx::database &MongoDb::getConnection() {
    return Db;
}
