#include "jwt-utils.hxx"

using namespace api::v1;

std::string api::v1::Jwt::sign(std::map<std::string, std::string> &payload) {
    try {
        const auto env = drogon::app().getCustomConfig();
        auto jwt = jwt::create();
        jwt.set_type("JWT")
                .set_issued_at(std::chrono::system_clock::now())
                .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(168))
                .set_issuer(env["jwt"]["issuer"].asString())
                .set_audience(env["jwt"]["issuer"].asString())
                .set_subject(env["jwt"]["host"].asString());

        for (auto &pair: payload) {
            jwt.set_payload_claim(pair.first, jwt::claim(pair.second));
        }

        return jwt.sign(jwt::algorithm::hs384(env["jwt"]["secret"].asString()));
    } catch (const std::runtime_error &ex) {
        LOG_DEBUG << ex.what();
        throw ex;
    }
}

jwt::decoded_jwt<jwt::traits::kazuho_picojson> api::v1::Jwt::verify(std::string &token) {
    try {
        const auto env = drogon::app().getCustomConfig();
        auto decoded = jwt::decode(token);
        auto verifier = jwt::verify()
                .with_type("JWT")
                .allow_algorithm(jwt::algorithm::hs384(env["jwt"]["secret"].asString()))
                .with_issuer(env["jwt"]["issuer"].asString())
                .with_audience(env["jwt"]["issuer"].asString())
                .with_subject(env["jwt"]["host"].asString());

        verifier.verify(decoded);
        return decoded;
    } catch (const std::exception &ex) {
        LOG_DEBUG << fmt::format("Error: {}", ex.what());
        throw ex;
    }
}
