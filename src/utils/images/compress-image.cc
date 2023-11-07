#include "compress-image.hxx"

using namespace api::v1;

bool CompressImage::base64ToImage(const std::vector<uchar> &buffer, const std::string &name,
                                  std::vector<int> &&compressParams) {
    try {
        cv::Mat image = cv::imdecode(cv::Mat(buffer), cv::IMREAD_COLOR);

        if (image.empty()) {
            LOG_DEBUG << "Error decoding image.";
            return false;
        }

        std::filesystem::path imagePath = std::filesystem::current_path().parent_path() / "src" / "resource" / name;
        bool writeResult = cv::imwrite(imagePath.string(), image, compressParams);

        if (!writeResult) {
            int errorCode = errno;
            LOG_DEBUG << "Error writing image. Error code: " << errorCode;
            return false;
        }

        return true;
    } catch (const std::exception &ex) {
        LOG_DEBUG << "Error processing image: " << ex.what();
        return false;
    }
}
