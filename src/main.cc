#include <drogon/drogon.h>
#include <src/database/database.hxx>
#include <src/utils/crypto/crypto.hxx>

using namespace api::v1;

int main() {
    drogon::app().loadConfigFile("./config.json");

    MongoDb::init();

    std::string pwd = "password";

    //LOG_DEBUG << Crypto::encrypt(pwd);

    //LOG_DEBUG << drogon::utils::getUuid();

    drogon::app().run();
    return 0;
}
