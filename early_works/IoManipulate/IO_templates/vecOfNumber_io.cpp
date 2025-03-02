// Mei tuan code exam

// written by Huxin 3. september 2023
#include <iostream>
#include <vector>
#include <algorithm>
int maxOperationsToMakeFirstLargest(std::vector<int>& numbers) ;
int maxOperationsToMakeFirstLargest_recur(std::vector<int>& numbers,int count);


int maxOperationsToMakeFirstLargest(std::vector<int>& numbers) {

    int count = 0;
    return maxOperationsToMakeFirstLargest_recur(numbers,count);

}


int maxOperationsToMakeFirstLargest_recur(std::vector<int>& numbers,int count){
    if(numbers.empty()) {
    return count;
    }

    int first_num = numbers[0];
    auto max_element_iter = std::max_element(numbers.begin(), numbers.end());
    int max_element = *max_element_iter;

    if(first_num >= max_element) return count;

    else{
        std::vector<int> numbers_mul= numbers;
        std::vector<int> numbers_dev = numbers;
        auto max_element_iter = std::max_element(numbers_dev.begin(), numbers_dev.end());


        numbers_mul[0] *=2;
        *max_element_iter /=2;
        int opt1_result = maxOperationsToMakeFirstLargest_recur(numbers_mul,count+1);
        int opt2_result = maxOperationsToMakeFirstLargest_recur(numbers_dev,count+1);

        return opt1_result < opt2_result? opt1_result : opt2_result;
    }


}



int main() 

{   //
    /*expected IO input:
    4
    4 7 8 9
    */
    int n;
    std::cin >> n;

    std::vector<int> numbers(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }


    // int count = 0;
    // int first_num = numbers[0];
    // auto max_element_iter = std::max_element(numbers.begin(), numbers.end());
    // int max_element = *max_element_iter;


    // std::vector<int> numbers_copy = numbers;
    // std::sort(numbers_copy.begin(),numbers_copy.end());

    // auto first_idx = std::find(numbers_copy.begin(), numbers_copy.end(), first_num);

    // while (first_idx != numbers_copy.end()) {
    //     // int index = std::distance(numbers_copy.begin(), it);
    //     std::cout << "Index of first_num in the sorted vector: " << *first_idx++ << std::endl;
    // // } else {
    // //     std::cout << "first_num not found in the sorted vector." << std::endl;
    // }


    // std::sort(numbers.begin(),numbers.end());
    // for(int i = 0; i < n; ++i) {
    //     std::cout << numbers[i]<<"  ";
    // }

    std::cout<<maxOperationsToMakeFirstLargest(numbers)<<std::endl;




    return 0;
}


// #include <iostream>
// #include <vector>
// using namespace std;

// int main(){
//     int n = 0;
//     cin >> n;
//     vector<int> nums(n, 0);
//     int maxNum = 0;
//     for(int i = 0; i < n; ++ i){
//         cin >> nums[i];
//         maxNum = maxNum > nums[i] ? maxNum : nums[i];
//     }
//     int minMul = 0, minDiv = 0;
//     int firstNum = nums[0];
//     while(firstNum <= maxNum){
//         firstNum *= 2;
//         ++ minMul;
//     }
//     firstNum = nums[0];
//     while(firstNum <= maxNum){
//         maxNum /= 2;
//         ++ minDiv;
//     }
//     cout << ((minMul < minDiv) ? minMul : minDiv);
// }