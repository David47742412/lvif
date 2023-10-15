#include <src/models/user/user-model.hxx>
#include <src/utils/crypto/crypto.hxx>
#include <src/utils/jwt/jwt-utils.hxx>

#ifndef LVIF_USER_SERVICE_HXX
#define LVIF_USER_SERVICE_HXX

namespace api::v1 {
    class AuthService {
    public:
        static std::shared_ptr<drogon::HttpResponse> login(const drogon::HttpRequestPtr &req);
    };
}

#endif //LVIF_USER_SERVICE_HXX
