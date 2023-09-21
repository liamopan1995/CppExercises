// 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。

// 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

 

// 示例 1：

// 输入: s = "leetcode", wordDict = ["leet", "code"]
// 输出: true
// 解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
// 示例 2：

// 输入: s = "applepenapple", wordDict = ["apple", "pen"]
// 输出: true
// 解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
//      注意，你可以重复使用字典中的单词。
// 示例 3：

// 输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
// 输出: false
 

// 提示：

// 1 <= s.length <= 300
// 1 <= wordDict.length <= 1000
// 1 <= wordDict[i].length <= 20
// s 和 wordDict[i] 仅由小写英文字母组成
// wordDict 中的所有字符串 互不相同


#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include <algorithm>
#include<unordered_set>
using namespace std;


class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (s.empty()) return true;
        sort(wordDict.begin(), wordDict.end(), [](const string &a, const string &b) {
        return a.length() > b.length();
        });
        for (auto word : wordDict) {
            int len = word.length();
            if (hash_list[s.substr(0,len)][word] == true)
                // s.substr(0,len)==word)
                {
                if(wordBreak(s.substr(len),wordDict)== true) {
                    return true;
                    }
            } else {
                if(s.substr(0,len)==word) {
                    hash_list[s.substr(0,len)][word] = true;
                    if(wordBreak(s.substr(len),wordDict)== true) {
                        return true;
                    }
                }
            }
        }
        return false;
    }


    /// optimal solustion:
    bool wordBreak_revised(string s, vector<string>& wordDict) {
        unordered_set<string> hashed_Dict (wordDict.begin(),wordDict.end());
        vector<int> dpi (s.length()+1,0);
        dpi[0] = 1;
        for(int i=1; i<= s.length();i++) {
            for(int j=i-1; j>=0;j--) {
                if ( dpi[j] && hashed_Dict.find(s.substr(j,i-j))!=hashed_Dict.end() ){
                    dpi[i] = 1;
                    break;
                }

            }
        }
        return dpi[s.length()];
    }
private:
    unordered_map<string,unordered_map<string,bool>> hash_list;

};

int main (){
    Solution sol;
    string s = "leetcode";
    vector<string> wordDict {"leet", "code"};

    cout<< sol.wordBreak(s,wordDict)<<endl;
    cout<< sol.wordBreak_revised(s,wordDict)<<endl;
    return 0;
}