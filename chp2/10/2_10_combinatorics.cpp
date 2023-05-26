/*
 * File: combinatorics.h
 * -----------------
 * This file implements the combinatorics.h interface.
 */
 
#include "combinatorics.h"
using namespace std;
 


/*
 * Implementation notes: combination
 * Usage: int c = combination(n,k);
 * ----------------------------------------
 * this function returns the number of choice for given n choice to choose k from them, where orders don't matter.
 */
int combination(int n, int k);

{int result = 1;
for(k,k>0,k--) {
result *= k;
    }
return result = permutation(n,k)/result;    
}


/*
 * Implementation notes: permutation
 * Usage: int p = permutation(n,k);
 * ----------------------------------------
 * this function returns the number of choice for given n choice to choose k from them, where orders do matter.
 */
int permutation(int n, int k) {
int q = n-k+1;
    int result = 1;
    for(q;q<=n;q++){
        cout <<"q: "<<q<<endl;
        result *=q;
    }
    return result;    
}