#pragma once

#include <drogon/HttpController.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <fmt/format.h>

using namespace drogon;

namespace api::v1 {
    class Resource : public drogon::HttpController<Resource> {
    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(Resource::get, "/{1}", Get, Options);
        METHOD_LIST_END

        void get(const HttpRequestPtr &req,
                 std::function<void(const HttpResponsePtr &)> &&callback, std::string&& fileName);
    };
}
