#include <iostream>
#include <sstream>
using namespace std;


const int MAX_JUDGES = 100;


int main() {
    double* scores = new double[MAX_JUDGES];

    if (scores) {
        *scores = 1.0;
    }

    if (scores) {
        *scores = 3.0;
    }

    for (int i = 0 ; i<2; i++) {
        cout <<*scores++<< "  ";
    }

    string input;
    double result;
    while (true) {

        cout<< "enter any number between 0 to 10 inclusive,  enter empty to stop";
        getline(cin,input);
        cout<< "you input is "<< input<<endl;
    }
    return 0;


//  ....

bool checkAndCastToDouble(const std::string& str, double& number) {
    std::istringstream iss(str);
    return !(iss >> std::noskipws >> number).fail();
}

int main() {
    std::string inputString = "123.45";
    double result;

    if (checkAndCastToDouble(inputString, result)) {
        std::cout << "The string '" << inputString << "' is a number: " << result << std::endl;
    } else {
        std::cout << "The string '" << inputString << "' is not a number." << std::endl;
    }

    return 0;
}




}