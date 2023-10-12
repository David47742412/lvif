#pragma once

#include <drogon/HttpFilter.h>
#include <src/utils/jwt/jwt-utils.hxx>

using namespace drogon;
namespace api::v1 {
    class JwtFilter : public HttpFilter<JwtFilter> {
    public:
        JwtFilter() = default;

        void doFilter(const HttpRequestPtr &req,
                      FilterCallback &&fcb,
                      FilterChainCallback &&fccb) override;
    };
}
