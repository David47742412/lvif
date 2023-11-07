#include <src/database/database.hxx>
#include <fmt/format.h>
#include <bsoncxx/builder/stream/document.hpp>

#ifndef LVIF_BOOK_MODEL_HXX
#define LVIF_BOOK_MODEL_HXX

namespace api::v1 {
    class BookModel {
    public:

        static Json::Value find();

        static void insert(Json::Value &body, std::string &userId);

        //static Json::Value update();

        //static Json::Value deleted();

        std::string _id;
        std::string name;
        std::string description;
        std::string image;
        std::string userId;

    };
}

#endif //LVIF_BOOK_MODEL_HXX
