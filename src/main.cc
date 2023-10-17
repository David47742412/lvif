#include <drogon/drogon.h>
#include <src/database/database.hxx>
#include <src/utils/crypto/crypto.hxx>
#include <fmt/format.h>

using namespace api::v1;

int main() {
    drogon::app().loadConfigFile("./config.json");

    MongoDb::init();

    std::string pwd = "password";
    std::string encryptPwd = fmt::format("78F3F7C140D6735F95921E00048D23C5AF6E2865F2C42F4C5CD6F4DB4FBE5515");

    LOG_DEBUG << Crypto::compare(pwd, encryptPwd);

    drogon::app().run();
    return 0;
}
