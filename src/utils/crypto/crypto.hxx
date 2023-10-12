#include <drogon/drogon.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cryptopp/sha.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/hex.h>
#include <iostream>

#ifndef LVIF_CRYPTO_HXX
#define LVIF_CRYPTO_HXX

namespace api::v1 {
    class Crypto {
    public:
        static std::string encrypt(std::string &pwd);

        static bool compare(std::string &pwd, std::string &encryptPwd);
    };
}

#endif //LVIF_CRYPTO_HXX
