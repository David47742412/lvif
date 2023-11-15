#include <drogon/drogon.h>
#include <src/database/database.hxx>

using namespace api::v1;

int main() {
    drogon::app().loadConfigFile("./config.json");

    MongoDb::init();

    drogon::app().run();
    return 0;
}
