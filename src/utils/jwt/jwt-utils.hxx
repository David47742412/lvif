#include <jwt-cpp/jwt.h>
#include <map>
#include <drogon/drogon.h>
#include <chrono>
#include <iostream>

#ifndef LVIF_JWT_UTILS_HXX
#define LVIF_JWT_UTILS_HXX

namespace api::v1 {
    class Jwt {
    public:
        static std::string sign(std::map<std::string, std::string> &payload);
        static jwt::decoded_jwt<jwt::traits::kazuho_picojson> verify(std::string &token);
    };
}

#endif //LVIF_JWT_UTILS_HXX
