#include "auth-service.hxx"

using namespace api::v1;

std::shared_ptr<drogon::HttpResponse> AuthService::login(const drogon::HttpRequestPtr &req) {
    Json::Value resJson;
    try {
        std::string emailOrUsername = (*req->getJsonObject())["username"].asString();
        std::string pwd = (*req->getJsonObject())["password"].asString();
        auto userLogin = UserModel::findByEmailOrUsername(emailOrUsername);
        if (!userLogin) throw std::runtime_error("UNAUTHORIZED");

        if (!Crypto::compare(pwd, userLogin->password)) throw std::runtime_error("UNAUTHORIZED");

        std::map<std::string, std::string> payload;
        payload["user_id"] = userLogin->_id;
        payload["username"] = userLogin->username;

        std::string &&token = Jwt::sign(payload);
        auto userJson = userLogin->toJson();
        userJson["token"] = token;

        resJson["statusCode"] = 200;
        resJson["message"] = Json::arrayValue;
        resJson["body"] = userJson;

    } catch (...) {
        resJson["statusCode"] = 401;
        resJson["message"]["error_code"] = "UNAUTHORIZED";
        resJson["message"]["message"] = "Username or password incorrect";
        resJson["body"] = Json::arrayValue;
    }
    auto res = drogon::HttpResponse::newHttpJsonResponse(resJson);
    res->setCustomStatusCode(resJson["statusCode"].asInt());
    return res;
}
