#include <vector>
#include<iostream>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size()<3) return nums.size();
        int i =2;
        for(int j =2; j < nums.size(); ++j) {
            if(nums[j]!=nums[j-2]){
                nums[i++]=nums[j];
            }
        }
        return i;
    }
};

int main(){
    Solution sol;
    vector<int> input {1,1,1,2,2,3};
    int new_size =sol.removeDuplicates(input);
    cout<< new_size<<endl;
    for (int i=0;i<new_size;i++) {cout<<input[i]<<endl;}

    return 0;
}


