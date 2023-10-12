#include "crypto.hxx"

using namespace api::v1;

std::string Crypto::encrypt(std::string &pwd) {
    try {
        std::string encryptedPwd;
        std::string &&salt = drogon::app().getCustomConfig()["crypto"]["secret"].asString();
        CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA512> pbkdf2;

        CryptoPP::byte derivedKey[32];
        pbkdf2.DeriveKey(
                derivedKey, sizeof(derivedKey), 0,
                reinterpret_cast<const CryptoPP::byte *>(pwd.data()), pwd.size(),
                reinterpret_cast<const CryptoPP::byte *>(salt.data()), salt.size(),
                10000
        );

        CryptoPP::StringSource transform(
                derivedKey, sizeof(derivedKey), true,
                new CryptoPP::HexEncoder(new CryptoPP::StringSink(encryptedPwd))
        );
        return encryptedPwd;

    } catch (const std::runtime_error &ex) {
        LOG_DEBUG << ex.what();
        throw ex;
    }
}

bool Crypto::compare(std::string &pwd, std::string &encryptPwd) {
    return encrypt(pwd) == encryptPwd;
}
