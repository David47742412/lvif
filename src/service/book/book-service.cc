#include "book-service.hxx"

using namespace api::v1;

Json::Value BookService::find() {
    return BookModel::find();
}
