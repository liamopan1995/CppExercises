#ifndef MY_UTILS
#define MY_UTILS
#include <vector>
#include <iostream>
#include <string>
namespace phx {

void SayHello()
{
    std::cout << " hello " << std::endl;
}

size_t FindLastSlash(const std::string str)
{
    size_t pos{str.size()};
    for (auto it = str.rbegin(); ((it != str.rend()) && (*it != '/')); ++it) {
        --pos;
    }
    return (pos == 0U && (str.empty() || str[0U] != '/') ? std::string::npos : pos - 1U);
}
}
#endif