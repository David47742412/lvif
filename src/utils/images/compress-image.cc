#include "compress-image.hxx"

using namespace api::v1;

bool
CompressImage::base64ToImage(std::string &base64, const std::string &name, std::vector<int> &&compressParams = {}) {
    try {
        std::string decoded_data = Base64::decode(base64);
        std::vector<uchar> data(decoded_data.begin(), decoded_data.end());

        cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);

        cv::imwrite(std::filesystem::current_path().parent_path() / "resource" / name, image, compressParams);
        return true;
    } catch (const std::exception &ex) {
        LOG_DEBUG << "Error process image" << ex.what();
        return false;
    }
}
