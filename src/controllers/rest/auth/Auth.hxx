#pragma once

#include <drogon/HttpController.h>
#include "src/service/auth/auth-service.hxx"

using namespace drogon;

namespace api::v1 {
    class Auth : public drogon::HttpController<Auth> {
    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(Auth::login, "/login", Post, Options);
            METHOD_ADD(Auth::logout, "/logout", Get, Options, "api::v1::JwtFilter");
        METHOD_LIST_END

        static void login(const HttpRequestPtr &req,
                          std::function<void(const HttpResponsePtr &)> &&callback);

        static void logout(const HttpRequestPtr &req,
                           std::function<void(const HttpResponsePtr &)> &&callback);

    };
}
