#include "resource.hxx"

using namespace api::v1;

void Resource::get(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback, std::string &&fileName) {
    std::ifstream file(std::filesystem::current_path().parent_path() / "src" / "resource" / fileName,
                       std::ios::in | std::ios::binary);

    if (!file) {
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

void Resource::upload(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    try {
        MultiPartParser fileUpload;
        Json::Value res;
        if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() != 1) {
            res["statusCode"] = 400;
            res["message"] = "Must only be one file";
            auto resp = HttpResponse::newHttpJsonResponse(res);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
        auto &file = fileUpload.getFiles()[0];

        const char *fileData = file.fileData();
        size_t fileSize = file.fileLength();
        std::vector<uchar> buffer(fileData, fileData + fileSize);
        auto fileName = fmt::format("{}.{}", utils::getUuid(), "png");

        CompressImage::base64ToImage(buffer, fileName, {cv::IMWRITE_PNG_COMPRESSION, 9});

        res["statusCode"] = 200;
        res["url"] = fmt::format("{}/api/v1/resource/{}", drogon::app().getCustomConfig()["server"]["host"].asString(), fileName);
        auto resp = HttpResponse::newHttpJsonResponse(res);
        callback(resp);

    } catch (const std::exception &ex) {
        LOG_DEBUG << ex.what();
    }
}
