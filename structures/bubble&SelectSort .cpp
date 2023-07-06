// skipping special case handeling
// implemented bubble sort and select sort

#include <iostream>
#include <vector>

using namespace std;


void bubsort(vector<int> & vec) {

int sz = vec.size();
for (int i=0; i<sz; i++) {
    for (int j = 0; j < sz-1;j++) {
        if (vec[j] > vec[j+1]) swap(vec[j],vec[j+1]);
    }
}
}

// a better version of bubble sort implementation

void bubsort_(vector<int> & vec) {

int sz = vec.size();
for (int i=0; i<sz; i++) {
    //for (int j = 0; j < sz - 1 - i ;j++) {
    for (int j = 1; j < sz - i ;j++) {
        //if (vec[j] > vec[j+1]) swap(vec[j],vec[j+1]);
        if (vec[j-1] > vec[j]) swap(vec[j-1],vec[j]);
    }
}
}

void selectSort(vector<int> & vec) {

int sz = vec.size();
for (int i=0; i<sz; i++) {  
    int min = i;
    for (int cur = i;cur<sz;cur++) {     
        
        if(vec[cur]<vec[min]) min = cur;

    }
    swap(vec[i],vec[min]);

}

}
int main()

{   cout<<" vec to be sorted is:"<<endl;
    vector<int> q = {6,9,4,8,7,2,3,5,1};

    for (int i=0; i<q.size();++i) {
        cout<<q[i]<<endl;
    }
    cout<<" result of bubble sort"<<endl;
    //bubsort(q);
    bubsort_(q);
    
    for (int i=0; i<q.size();++i) {
        cout<<q[i]<<endl;
    }



    vector<int> p = {6,9,4,8,7,2,3,5,1};
    cout<<"result of select sort"<<endl;
    
    selectSort(p);
    for (int i=0; i<p.size();++i) {
        cout<<p[i]<<endl;
    }

    return 0;
}



