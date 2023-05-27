// Rewrite the implementation of the merge sort algorithm from Figure 10-3 so
// that it sorts an array rather than a vector. The revised function should use the
// prototype

// void sort(int array[], int n)
// as in the reimplementation of the selection sort algorithm on page 503.

#include <iostream>

using namespace std;



void sort(int arry[], int n);
void merge(int arry1[],int arry2[],int result[],int size1, int size2);

// helper to pritnt array 
void printArr (int arry[], int n) {
    cout<< "  "<<endl;
    for (int i = 0; i < n; i++) {
        cout << arry[i] << " ";
    } 
    cout<< "  "<<endl;

}



int main () {
    int arrsize = 5;
    int arr[arrsize] {2,5,3,1,10};
    cout<< "original array";
    printArr(arr,arrsize);
    sort (arr,arrsize);
    cout<< "sorted array";
    printArr(arr,arrsize);

    arrsize = 7;
    int arr_2[arrsize] {2,5,3,3,3,1,10};
    cout<< "original array";
    printArr(arr_2,arrsize);
    sort (arr_2,arrsize);
    cout<< "sorted array";
    printArr(arr_2,arrsize);

    arrsize = 1;
    arr_2[arrsize] ={2};
    cout<< "original array";
    printArr(arr_2,arrsize);
    sort (arr_2,arrsize);
    cout<< "sorted array";
    printArr(arr_2,arrsize);

    return  0 ;
}


void sort(int arry[], int n){
    int arrfirst[n/2];
    int arrsecond[n - n/2];
    if (n <=1) return;// base case 

    for (int i= 0;i<n;i++){
        if (i < n/2) {
            arrfirst[i] = arry[i];
        } 
        else {
            arrsecond[i - n/2] = arry[i];
        }
    }
    
    sort(arrfirst, n/2);
    sort(arrsecond,(n- n/2));
    merge(arrfirst,arrsecond,arry,n/2,n-n/2);
    
    // memory deallocation ? 
    // No not here, only when arrays were created using new[] command !
    // The arrfirst and arrsecond arrays are created as stack-allocated arrays within 
    // the sort function. They are not dynamically allocated using new[],
    // so there is no need to manually deallocate them.
    // delete[] arrfirst;
    // delete[] arrsecond;


}

void merge(int arry1[],int arry2[],int result[],int size1, int size2){
    
    int n1 = 0, n2 = 0, j = 0;

    //The issue in your code lies with the size calculation in the merge function. 
    //When passing arrays to functions, they decay into pointers, 
    //and the sizeof operator no longer gives you the correct size of the array.

    // int size1 = sizeof(arry1) / sizeof(arry1[0]);
    // int size2 = sizeof(arry2) / sizeof(arry2[0]);

    
    while (n1 < size1 && n2 <size2) {    
        result[j++] = (arry1[n1]<arry2[n2])? arry1[n1++]:arry2[n2++];
    }
    while(n1 < size1) {
        result[j++] = arry1[n1++];
    }
    while(n2 < size2) {
        result[j++] = arry2[n2++];
    }

}