#include "base64.hxx"

using namespace api::v1;

std::string Base64::decode(std::string &input) {
    using namespace boost::archive::iterators;
    typedef transform_width<binary_from_base64<remove_whitespace
            <std::string::const_iterator> >, 8, 6> ItBinaryT;

    try {
        // If the input isn't a multiple of 4, pad with =
        size_t num_pad_chars((4 - input.size() % 4) % 4);
        input.append(num_pad_chars, '=');

        size_t pad_chars(std::count(input.begin(), input.end(), '='));
        std::replace(input.begin(), input.end(), '=', 'A');
        std::string output(ItBinaryT(input.begin()), ItBinaryT(input.end()));
        output.erase(output.end() - pad_chars, output.end());
        return output;
    }
    catch (std::exception const &) {
        return "";
    }
}
