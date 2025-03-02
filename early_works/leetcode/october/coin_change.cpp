
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    /// SUBOPTIMAL SOLUTION
    // int coinChange(vector<int>& coins, int amount) {
        
    //     std::sort(coins.begin(), coins.end());
    //     vector<int> dpi(amount+1,-1);
    //     dpi[0] = 0;

    //     for(int i = 1;i<=amount;i++){
    //         vector<int>dp;
    //         for(auto coin : coins){
    //             if(coin >i) continue;
    //             if(coin == i) { dpi[i] = 1;break; }
    //             if(dpi[i-coin] != -1) dp.push_back(dpi[i-coin]);   
    //         }
    //         if(dpi[i]==-1){dpi[i] = dp.empty() ? -1: *(min_element(dp.begin(), dp.end()))+1;}
    //     }
    //     return dpi[amount];
    //     }


        int coinChange(vector<int>& coins, int amount) {
        
        std::sort(coins.begin(), coins.end());/// sort to asending  order 1 ,2,5,8 f.e.
        vector<int> dpi(amount+1,amount+1);
        dpi[0] = 0;

        for(int i = 1;i<=amount;i++){
            for(auto coin : coins){
                if(coin >i) break;
                if(coin == i) { dpi[i] = 1;break; }
                if(dpi[i-coin] != -1) dpi[i]= min (dpi[i],dpi[i-coin]+1);   
            }
            if(dpi[i]==amount+1)dpi[i] = -1;
        }
        return dpi[amount];
        }
        
};

int main (){
    Solution sol;
    vector<int> coins {186,419,83,408};
    int amount = 6249;
    cout<< sol.coinChange(coins,amount)<<endl;
    // cout<< -3%2<<endl;
    return 0;
}