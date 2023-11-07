#pragma once

#include <drogon/HttpController.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <fmt/format.h>
#include <src/utils/images/compress-image.hxx>

using namespace drogon;

namespace api::v1 {
    class Resource : public drogon::HttpController<Resource> {
    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(Resource::get, "/{1}", Get, Options);
            METHOD_ADD(Resource::upload, "", Post, Options, "api::v1::JwtFilter");
        METHOD_LIST_END

        static void get(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback, std::string &&fileName);

        static void upload(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    };
}
