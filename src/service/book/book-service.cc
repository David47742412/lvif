#include "book-service.hxx"

using namespace api::v1;

Json::Value BookService::find() {
    return BookModel::find();
}

bool BookService::insert(Json::Value &book, std::string &userId, std::string &workspace, std::string &ip) {
    return BookModel::insert(book, userId.c_str(), workspace.c_str(), ip.c_str());
}

bool BookService::update(Json::Value &book, std::string &userId, std::string &workspace, std::string &ip) {
    std::string bookId = book["bookId"].asString();
    return BookModel::update(bookId.c_str(), book, userId.c_str(), workspace.c_str(), ip.c_str());
}

bool BookService::deleted(std::string& bookId, std::string &userId, std::string &workspace, std::string &ip) {
    return BookModel::deleted(bookId.c_str(), userId.c_str(), workspace.c_str(), ip.c_str());
}
