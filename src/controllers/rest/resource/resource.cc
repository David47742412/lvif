#include "resource.hxx"

using namespace api::v1;

void Resource::get(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback, std::string &&fileName) {
    std::ifstream file(std::filesystem::current_path().parent_path() / "resource" / fileName, std::ios::in | std::ios::binary);

    if (!file)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k204NoContent);
        callback(resp);
        return;
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);

    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(std::string(buffer.begin(), buffer.end()));
    resp->setStatusCode(HttpStatusCode::k200OK);
    resp->setContentTypeCode(ContentType::CT_IMAGE_PNG);
    callback(resp);
}
