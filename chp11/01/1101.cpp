#include <iostream>
#include <math.h>
using namespace std;


void generateBinaryCode(int nBits);
void generateBinaryCode_core(int nBits, string seq);
int BinaryToDecimal(string str);

int main() {
    int a;
    cout<< "please enter a positive integer"<<endl;
    cin>>a;
    generateBinaryCode(a);
    return 0;

    
}

void generateBinaryCode(int nBits){
    if (nBits < 0) {
         cout<<"invalid nBits!"<<endl;
    }
    else {
        string bitseq = "";
        generateBinaryCode_core(nBits,bitseq);
    }
}

void generateBinaryCode_core(int nBits, string seq) {

    //base case : 
    if (nBits == 0) {
        cout <<seq<<" → "<<BinaryToDecimal(seq)<<endl;
    }
    //
    else {
        nBits--;
        generateBinaryCode_core(nBits,seq+"0");
        generateBinaryCode_core(nBits,seq+"1");
    }
}

int BinaryToDecimal(string str){
    int result =0;
    int power = 0;
    for (int i = str.length()-1; i > -1; i--){

        if(str[i]=='1'){
            result += pow(2,power);
        }
        power++;
    }
    return result;
    // return str.length();
}

