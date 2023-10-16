#include <src/database/database.hxx>
#include <memory>
#include <regex>

#ifndef LVIF_USER_MODEL_HXX
#define LVIF_USER_MODEL_HXX

namespace api::v1 {
    class UserModel {
    public:
        std::string _id;
        std::string alias;
        std::string image;
        std::string lastName;
        std::string name;
        std::string password;
        std::string username;

        static std::shared_ptr<UserModel> findByEmailOrUsername(std::string &emailOrUsername);

        Json::Value toJson() const;

    };
}

#endif //LVIF_USER_MODEL_HXX
