

#include <iostream>
#include <vector>
#include <string>

using namespace std;
/// Expected input:

// 3 5
// 1 2 3 3 5
// 2 4 5 6 7
// 4 5 6 2 1

/// Output to this:
// 12335
// 24567
// 45621

int main() {
    int a, b;
    
    while (cin >> a >> b) {
        // Initialize a 2D char array of size [a][b]
        vector<vector<char>> charArray(a, vector<char>(b));
        
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < b; ++j) {
                cin >> charArray[i][j];
            }
        }
        
        cin.ignore(); // Clear the newline character
        

        // Print the 2D char array
        for (const vector<char>& row : charArray) {
            for (char c : row) {
                cout << c;
            }
            cout << endl;
        }
    }
    
    return 0;
}
