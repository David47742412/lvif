#include "Auth.hxx"

using namespace api::v1;

void Auth::login(const HttpRequestPtr &req,
                 std::function<void(const HttpResponsePtr &)> &&callback) {
    callback(AuthService::login(req));
}

void Auth::logout(const drogon::HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    Json::Value resJson;
    auto res = drogon::HttpResponse::newHttpJsonResponse(resJson);
    callback(res);
}
