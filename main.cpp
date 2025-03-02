#include <iostream>
#include <thread>
#include <vector>
#include "my_utils.h"
#include "derived.h"

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << "Number of concurrent threads supported: " << n << std::endl;
    std::vector<int> vec {1, 2, 3};
    phx::ShowVec(vec);
    phx::Derived dr{};
    dr.DoJob();
    return 0;
}