#include <iostream>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>
#include <algorithm>

#ifndef LVIF_BASE64_H
#define LVIF_BASE64_H

namespace api::v1 {
    class Base64 {
    public:
        static std::string decode(std::string &input);
    };
}

#endif //LVIF_BASE64_H
