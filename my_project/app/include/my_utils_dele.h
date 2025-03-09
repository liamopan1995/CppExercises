#ifndef MY_UTILS_DELE
#define MY_UTILS_DELE
#include <vector>
#include <iostream>
namespace phx {

template<typename T>
void ShowVec(const std::vector<T>& vec)
{
    for (const auto e : vec) {
        std::cout << e << std::endl;
    }
}
}
#endif



