#include "my_utils.h"
namespace phx {
    size_t FindLastSlash(const std::string str)
    {
        size_t pos{str.size()};
        for (auto it = str.rbegin(); ((it != str.rend()) && (*it != '/')); ++it) {
            --pos;
        }
        return (pos == 0U && (str.empty() || str[0U] != '/') ? std::string::npos : pos - 1U);
    }
}