#include<array>
#include<unordered_set>
#include<vector>
#include<iostream>

int Input[8]{ 4, 3, 2, 7, 8, 2, 3, 1};
std::vector<int> nums { 4, 3, 2, 7, 8, 2, 3, 1};

std::vector<int> findNumDissapeared(std::vector<int> nums);
std::vector<int> findDisappearedNumbers(std::vector<int>& nums);
int main (){

    int size = sizeof(Input)/sizeof(Input[0]);
    int maxnum = -1;
    std::unordered_set<int> numAppeared;

    for (int i = 0; i< size; ++i) {
        numAppeared.insert(Input[i]);
        maxnum = (maxnum > Input[i]) ? maxnum : Input[i]; 
    }
    std::vector<int> output;
    output.clear();

    for(int i=1; i <= maxnum; ++i) {
        if (numAppeared.find(i) == numAppeared.end()) {
            output.push_back(i);
        }

    }

    for (const auto& member : output){
        std::cout << member<<std::endl;

    }

    //trying the provided solution 
    output.clear();
    output = findNumDissapeared(nums) ;

    for (const auto& member : output){
        std::cout << member<<std::endl;

    }
    return 0;
}
// my solution after looked the provided solution
std::vector<int> findNumDissapeared(std::vector<int> nums) {
    std::vector<int> ans;
    for (auto &num :nums) {
        int pos = abs(num) -1;

        //
        // wrong :if (nums[pos] > 0 ) nums[pos] = -1;  
        //   
        // using abs(num) oso only taking its amount infomation and leave out the sign, 
        // if like what i did setting to -1 (nums[pos] > 0 ) nums[pos] = -1;  it will be wrong,
        // as the uninspected value beening wipped out
        if (nums[pos] > 0 ) nums[pos] = -nums[pos];  
        // by only adding a negative sign to the number at corresponding position
        // it indicates existence of the value, without losing infomation of the number at current position
        // which may not be insepcted yet.
    }

    for (int i=0; i< nums.size(); ++i) {
        if (nums[i] > 0) ans.push_back(i+1);
    }
    return ans;
    
} 
    

// Solution with lower space complexity:

std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
std::vector<int> ans;
for (const int & num: nums) {
int pos = abs(num) - 1;
if (nums[pos] > 0) {
nums[pos] = -nums[pos];
}
}
for (int i = 0; i < nums.size(); ++i) {
if (nums[i] > 0) {
ans.push_back(i + 1);
}
}
return ans;
}