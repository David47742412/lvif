#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <drogon/drogon.h>
#include <src/utils/base64/base64.hxx>
#include <filesystem>

#ifndef LVIF_COMPRESS_IMAGE_HXX
#define LVIF_COMPRESS_IMAGE_HXX

namespace api::v1 {
    class CompressImage {
    public:
        static bool base64ToImage(const std::vector<uchar> &buffer, const std::string &name, std::vector<int> &&compressParams);
    };
}

#endif //LVIF_COMPRESS_IMAGE_HXX
