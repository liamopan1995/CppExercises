// implementation of merge sort and quick sort as an exercise
// deciding wether to pass parameters by reference or not can be challaenging
// but also has a significant influence on developing , so it is better to think clearly
// from the beginning.
// this point also makes call stack analysis  an essentail part of writting fucntion ,
// investing more time in call stack analysis could pay a lot in return

// Implementation of merge sort and quick sort as an exercise
// Deciding whether to pass parameters by reference or not can be challenging,
// but it also has a significant influence on development. Therefore, it is better
// to think clearly from the beginning. This makes call stack analysis an essential
// part of writing functions. Investing more time in call stack analysis can yield
// substantial benefits.

#include <iostream>
#include <vector>

using namespace std;
void sort(vector<int> & vec) ;
void quicksort (vector<int>& inp,int beg,int end) ;
int partition (vector<int>& inp, int start, int finish);
void mergeSort (vector<int>& inp);
void merge(vector<int>& merged, const vector<int>& first, const vector<int>& second);

int main() {
    vector<int> p = {6,9,4,8,7,2,3,5,1};
    cout<<"the unsorted vec is :"<<endl;
    for (int i=0; i<p.size();++i) {
        cout<<p[i]<<endl;
    }
    cout<<"applying merge sort"<<endl;
    //sort(p);
    mergeSort(p);
    for (int i=0; i<p.size();++i) {
        cout<<p[i]<<endl;
    }
    cout<<"the unsorted vec is :"<<endl;
    vector<int> d = {6,9,23,44,111,99,4,};
        for (int i=0; i<d.size();++i) {
        cout<<d[i]<<endl;
    }
    cout<<"applying quick sort"<<endl;
    sort(d);
    //mergeSort(p);
    for (int i=0; i<d.size();++i) {
        cout<<d[i]<<endl;
    }

    return 0;
}


//  Implementation of quick sort
void sort(vector<int> & vec) {
quicksort(vec, 0, vec.size() - 1);
}

void quicksort (vector<int>& vec,int start,int finish) {
    if (start >= finish) return;
    int boundary = partition(vec, start, finish);
    quicksort(vec, start, boundary - 1);
    quicksort(vec, boundary + 1, finish);

}

int partition (vector<int>& inp, int start, int finish){
    
    int pivot = inp[start];
     // Moving the initialization of lp ,rp outside the loop to avoid resetting it in each iteration.
    int lp = start +1;
    int rp = finish;
    
    while (true) {
        
        //while (lp <rp && inp[lp]<pivot) lp++; //changee the order
        while (lp <rp && inp[rp]>=pivot) rp--;
        while (lp <rp && inp[lp]<pivot) lp++;
        if (rp ==lp) break;
        swap(inp[rp],inp[lp]);
        }
        if (inp[lp] >= pivot) return start;
        swap(inp[start],inp[rp]);
        return rp;
}



//  Implementation of merge sort
void merge(vector<int>& merged,const vector<int>& first, const vector<int>& second){
    size_t i =0, j=0;
    size_t sizeFirst = first.size();
    size_t sizeSecond = second.size();

    //while ( !first.empty() && !second.empty()) {
    while ( i < sizeFirst && j < sizeSecond){
        if(first[i]<second[j]) merged.push_back(first[i++]);
        else merged.push_back(second[j++]);
    }
    // Wrong 
    //while ( !first.empty()) {
    while (i < sizeFirst) {
        merged.push_back(first[i++]);
    }
    while (j < sizeSecond) {
        merged.push_back(second[j++]);
    }  
}

void mergeSort (vector<int>& inp){
    if (inp.size() <= 1) return;
    size_t mid = inp.size()/2;
    vector<int> first(inp.begin(), inp.begin() + mid);
    vector<int> second(inp.begin() + mid, inp.end());
    mergeSort(first);// first half of the vec
    mergeSort(second);// second half o f the vec
    // the idea of clearing inp and pass it as a empty container in merge is worth noticing
    inp.clear();
    merge (inp,first,second);// merge them

}
