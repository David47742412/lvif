#include <mongocxx/database.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <drogon/drogon.h>

#ifndef LVIF_DATABASE_HXX
#define LVIF_DATABASE_HXX

namespace api::v1 {
    class MongoDb {
    public:
        static void init();

        static mongocxx::database &getConnection();

    private:
        MongoDb() = default;
        ~MongoDb() = default;
        inline static mongocxx::database Db{};
        inline static mongocxx::client Client{};
    };
}

#endif //LVIF_DATABASE_HXX
