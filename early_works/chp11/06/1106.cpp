#include <iostream>
#include <sstream>
using namespace std;


const int MAX_JUDGES = 5; //  5 for test , change back to 100 later;

// check string is number 
bool checkAndCastToDouble(const string& str, double& number);


int main() {
    double *scores = new double[MAX_JUDGES];
    double *scores_2 = scores;
    double *scores_3 = scores;
    int num_judges = 0;
    string input;
    double result;
    // read in numbers
    cout<< "Enter an number in [0,10],  Enter a blank line to signal the end of the"<<\
    "list. (to stop recording and to compute result)"<< endl;
    while (true) {

        getline(cin,input);
        if (input =="") break;
        // check space in array is enough 
        if(num_judges == MAX_JUDGES) {
            cout<< "the maximum note number is limited to 100."<<endl;
            
            cout << "enter result to compute result from previous entered notes except this one "<<endl;
            cout << "enter any other charater to quick"<<endl;
            string command;
            getline(cin,command);
            if (command == "result")goto jump1;
            else {
                delete[] scores_3;
                return 0;
            };
            }

        // check input string is a number
        if (checkAndCastToDouble(input,result)) {
            // cout<< "you input is a number it is: " << result<<endl;

            // if it is number check it is within the valid range
            if (0 >= result || 10<= result) {
                cout<< "this number is out of range from [0,10]"<<endl;
                cout<< "please enter a new number which is valid "<<endl;
            }
            else {
                // cout << "ligit number ,new score recorded."<<endl;
                cout << "Judge # "<<num_judges + 1<<": "<<result<<endl;
                if(scores) *scores++ = result;         
                num_judges++;

            }
        }
        else {
            cout << "you input is not a number, please enter a valid number between 0 and 10 inclusive"<<endl;
        }
    }
jump1:
    // find max and min in the arr
    double *min_ptr =  nullptr;
    double *max_ptr =  nullptr;
    double sum_notes = 0;
    for( int i = 0; i < num_judges; i++) {
        if (scores_2 == nullptr) break;
        if(min_ptr == nullptr || *min_ptr > *scores_2) min_ptr = scores_2;
        if(max_ptr == nullptr || *max_ptr < *scores_2) max_ptr = scores_2;
        sum_notes += *scores_2;
        scores_2++;
    }
    // compute final result
    cout<< "-----result------"<< endl;
    if(min_ptr !=nullptr && max_ptr !=nullptr ) {
        cout << " maximal note among notes is : "<<*max_ptr <<endl<<
         " minimal note among notes is : "<< *min_ptr<<endl;
        cout<< " sum of notes is: "<< sum_notes<<endl;
        if (num_judges > 2){
            cout<< " average note is : "<< (sum_notes - *min_ptr - *max_ptr) / ( num_judges - 2)<<endl;
        }
        else {
            cout<< "in order to compute the average, num_judges must be greater than 2 !"<<endl;
        }      
    }

    delete[] scores_3;
    return 0;
}


// check wheter a string is number , if it is return 1 and write this number to number,
//else return 0
bool checkAndCastToDouble(const std::string& str, double& number) {
    std::istringstream iss(str);
    return !(iss >> std::noskipws >> number).fail();
}

