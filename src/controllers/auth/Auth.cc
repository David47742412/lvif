#include "Auth.hxx"

using namespace api::v1;

void Auth::login(const HttpRequestPtr &req,
                 std::function<void(const HttpResponsePtr &)> &&callback) {
    callback(AuthService::login(req));
}
