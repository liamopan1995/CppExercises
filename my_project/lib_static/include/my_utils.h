#ifndef MY_UTILS
#define MY_UTILS
#include <vector>
#include <iostream>
#include <string>
namespace phx {

static inline void SayHello() // 「 static 」ensures that the function is local to each translation unit and is not used outside the translation unit
{
    std::cout << " hello " << std::endl;
}

template<typename T>
void ShowVec(const std::vector<T>& vec)
{
    for (const auto e : vec) {
        std::cout << e << std::endl;
    }
}

size_t FindLastSlash(const std::string str);
}
#endif