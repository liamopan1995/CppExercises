
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        
        // dpi[0] = triangle[0][0];
        // int i = 0;
        // int layer =1;
        // for (auto row: triangle){
        //     for(auto ele : row ){
                
        //         dpi[i++] 
        //     }
        //     layer++;
        // }

        int depth = triangle.size();
        int total_element_num = depth + depth *(depth -1)/2;
        if (total_element_num ==0) return 0;
        vector<int> dpi(total_element_num+1);
        ///(euqal auto elem : triangle.back()) 
        for ( auto elem: triangle[depth -1]) {
            dpi[total_element_num] = elem;
            total_element_num--;
        }

        for (int j= depth-2; j >=0; j--) {
            for (auto ele : triangle[j]){
                dpi[total_element_num] = ele + min(dpi[total_element_num + j+1],dpi[total_element_num + j+2]);
                total_element_num--;
            }

        }
        return dpi[1];    
    }
};

int main (){
    Solution sol;
    vector<vector<int>> triangle {{2},{3,4},{6,5,7},{4,1,8,3}};
    cout<< sol.minimumTotal(triangle)<<endl;
    // cout<< -3%2<<endl;
    return 0;
}