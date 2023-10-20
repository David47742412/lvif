#include <drogon/drogon.h>
#include <src/database/database.hxx>
#include <src/utils/crypto/crypto.hxx>
#include <fmt/format.h>

using namespace api::v1;

int main() {
    drogon::app().loadConfigFile("./config.json");

    MongoDb::init();

    drogon::app().run();
    return 0;
}
