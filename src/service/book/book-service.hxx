#include <drogon/drogon.h>
#include <src/models/book/book-model.hxx>

#define LVIF_BOOK_SERVICE
#ifdef LVIF_BOOK_SERVICE

namespace api::v1 {
    class BookService {
    public:
        static Json::Value find();
    };
}

#endif //LVIF_BOOK_SERVICE
