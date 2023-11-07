#include <drogon/drogon.h>
#include <src/models/book/book-model.hxx>


#define LVIF_BOOK_SERVICE
#ifdef LVIF_BOOK_SERVICE

namespace api::v1 {
    class BookService {
    public:
        static Json::Value find();

        static bool insert(Json::Value &book, std::string &userId, std::string &workspace, std::string &ip);
    };
}

#endif //LVIF_BOOK_SERVICE
