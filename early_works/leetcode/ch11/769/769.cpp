#include<array>
#include<vector>
#include<iostream>

using namespace std;

vector<int> Input {1};
vector<int> Input1 {1, 0, 2, 3, 4, 8, 7, 6};
vector<int> Input2 {1, 0, 2, 3, 5, 4, 6, 7}; // 01 .2 .3 .456.7
vector<int> Input3 {1, 0, 2, 3, 4};//01,2,3,4
vector<int> Input4 {4, 0, 2, 3, 1};//01,2,3,4
int maxChunkToSorted (const vector<int>& vec);
int maxChunkToSortedAlternativ (const vector<int>& vec);
int maxChunksToSorted(vector<int>& arr);

int main () {
    cout<< maxChunkToSorted(Input2)<<endl;
    cout<< maxChunkToSortedAlternativ(Input2)<<endl;
    cout<< maxChunksToSorted(Input2)<<endl;

    cout<< maxChunkToSorted(Input3)<<endl;
    cout<< maxChunkToSortedAlternativ(Input3)<<endl;
    cout<< maxChunksToSorted(Input3)<<endl;

    cout<< maxChunkToSorted(Input)<<endl;
    cout<< maxChunkToSortedAlternativ(Input)<<endl;
    cout<< maxChunksToSorted(Input)<<endl;

    cout<< maxChunkToSorted(Input4)<<endl;
    cout<< maxChunkToSortedAlternativ(Input4)<<endl;
    cout<< maxChunksToSorted(Input4)<<endl;
    return 0;
}

// My ituitive solution
int maxChunkToSorted (const vector<int>& vec){  
    int vecSize = vec.size();
    int maxChunk = 0;
    int cur = -1;
    for (int i=0; i< vecSize; ++i) {
        if (vec[i] < cur) continue;
        else {
            maxChunk++;
            cur = vec[i];
        }
    }
    return maxChunk;
    
}

// my solution adopt concpet from provided solution
int maxChunkToSortedAlternativ (const vector<int>& vec){  
    int vecSize = vec.size();
    int curMax = 0;
    int maxChunk = 0;
    for (int i=0;i< vecSize; ++i) {
        curMax = max(curMax,vec[i]);
        if (curMax == i) maxChunk++;
    }
    return maxChunk;
    
}
// Provided solution
int maxChunksToSorted(vector<int>& arr) {
    int chunks = 0, cur_max = 0;
    for (int i = 0; i < arr.size(); ++i) {
        cur_max = max(cur_max, arr[i]);
        if (cur_max == i) {
            ++chunks;
        }
    }
    return chunks;
}