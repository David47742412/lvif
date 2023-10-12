#include "jwt-filter.hxx"

using namespace drogon;
using namespace api::v1;

void JwtFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb) {
    std::string token = req->getHeader("Authorization");
    try {
        if (token.empty()) {
            throw std::runtime_error("invalid token");
        }
        std::string &&bearer = "Bearer ";
        token = token.replace(0, bearer.size(), "");

        auto decoded = Jwt::verify(token);
        req->setParameter("userId", decoded.get_payload_claim("user_id").as_string());

        fccb();

    } catch (...) {
        Json::Value resJson;
        resJson["statusCode"] = 401;
        resJson["message"]["error_code"] = "UNAUTHORIZED";
        resJson["message"]["message"] = "invalid token";
        resJson["body"] = Json::arrayValue;
        auto res = HttpResponse::newHttpJsonResponse(resJson);
        res->setStatusCode(k401Unauthorized);
        fcb(res);
    }
}
