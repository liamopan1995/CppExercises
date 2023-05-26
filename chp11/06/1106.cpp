#include <iostream>
#include <sstream>
using namespace std;


const int MAX_JUDGES = 3; //100
bool checkAndCastToDouble(const string& str, double& number);


int main() {
    double* scores = new double[MAX_JUDGES];
    int num_judges = 0;

    // if (scores) {
    //     *scores = 1.0;
    // }

    // if (scores) {
    //     *scores = 3.0;
    // }

    // for (int i = 0 ; i<2; i++) {
    //     cout <<*scores++<< "  ";
    // }

    string input;
    double result;
    while (true) {
        

        cout<< "Enter an number in [0,10],  enter empty to stop"<< endl;
        

        getline(cin,input);
        if (input =="") break;

        if(num_judges == MAX_JUDGES) {
            cout<< "the maximum note number is limited to 100.,";break;
            }
            
        cout<< "you input is "<< input<<endl;

        if (checkAndCastToDouble(input,result)) {
            cout<< "you input is a number it is: " << result<<endl;
            if (0 >= result || 10<= result) {
                cout<< "this number is out of range from [0,10]";
            }
            else {
                cout << "new score recorded."<<endl;
                if(scores) *scores++ = result;
                num_judges++;

            }
        }
        else {
            cout << "you input is not a number, please enter a valid number between 0 and 10 inclusive"<<endl;
        }
    }
    return 0;
}

//  ....

bool checkAndCastToDouble(const std::string& str, double& number) {
    std::istringstream iss(str);
    return !(iss >> std::noskipws >> number).fail();
}




// int main() {
//     std::string inputString = "123.45";
//     double result;

//     if (checkAndCastToDouble(inputString, result)) {
//         std::cout << "The string '" << inputString << "' is a number: " << result << std::endl;
//     } else {
//         std::cout << "The string '" << inputString << "' is not a number." << std::endl;
//     }

//     return 0;
// }