#ifndef MY_UTILS
#define MY_UTILS
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
void SayHello()
{
    std::cout << " hello " << std::endl;
}
}
#endif