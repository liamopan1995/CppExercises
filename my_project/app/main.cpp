#include <iostream>
#include <thread>
#include <vector>
// #include "my_utils.h"
#include "my_utils_dele.h"
#include "derived.h"

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << "Number of concurrent threads supported: " << n << std::endl;

    std::vector<int> vec {1, 2, 3};
    phx::ShowVec(vec);
    phx::Derived dr{};
    dr.m_id = 1;
    phx::Derived drSecond{};
    drSecond.m_id = 2;
    auto lam = [&drSecond]{
        int loopCnt {50U}; 
        while(loopCnt--) {
            drSecond.DoJob();
        }
    };
    
    dr.DoJob();
    std::thread t1(&phx::Derived::DoJob, &dr);
    std::thread t2(lam);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    t2.join();
    t1.join();
    return 0;
}