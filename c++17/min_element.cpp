#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int my_min_number (int n, vector<int> num_list){

    return std::min_element(num_list.begin(),num_list.end(),
    [&n] (int n1, int n2)-> bool {
        return n * n1 < n*n2;
    }) - num_list.begin();
}

int main() {


    vector<int> my_nums {3,2,6,9,1,0,-3,-9};
    int single_num = -1;

    cout<< my_min_number(single_num, my_nums)<<endl;
    return 0;

}