/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;
void sort(vector<int> & vec) ;
void quicksort (vector<int>& inp,int beg,int end) ;
int partition (vector<int>& inp, int start, int finish);

int main()

{
    vector<int> p = {6,9,4,8,7,2,3,5,1};
    cout<<"Hello World"<<endl;
    sort(p);
    for (int i=0; i<p.size();++i) {
        cout<<p[i]<<endl;
    }

    return 0;
}

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

// int partition(vector<int> & vec, int start, int finish) {
// int pivot = vec[start];
// int lh = start + 1;
// int rh = finish;
// while (true) {
// while (lh < rh && vec[rh] >= pivot) rh--;
// while (lh < rh && vec[lh] < pivot) lh++;
// if (lh == rh) break;

// swap(vec[lh],vec[rh]);
// }
// if (vec[lh] >= pivot) return start;
// swap(vec[start],vec[lh]);

// return lh;
// }

