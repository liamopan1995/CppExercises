// Yes, you can update the indices `i` and `j` within the nested loops to achieve this behavior.

// When a condition is fulfilled for a particular `(i, j)` pair, you can increment `i` (to go to the next row) and set `j` to `0` (to start from the first column of the new row). After doing so, you'd also want to use a `continue` statement in the inner loop to ensure that you actually start iterating from the beginning of the next row.

// Here's a simple example illustrating this. Let's assume you want to skip to the next row when you encounter the character `'X'`:

// ```cpp

// Meituan mian shi ti
#include <iostream>
#include <set>

using namespace std;

const int MAX_SIZE = 10000; // Adjust as needed


class mei_array {

public:
    // char *array_;


    mei_array(int row, int col){
        if (row * col > MAX_SIZE) {
        cerr << "Array dimensions exceed maximum allowed size." << endl;
        }

        row_=row;
        col_=col;
        array_ = new char[row_*col_];
        meituan_ = {'m','e','t','u','a','n'};
    };

    ~mei_array(){
        delete[] array_;
    };


    void has_meituan() {
        if(row_ <meituan_.size()) {cout<<"NO"<<endl;return;}

         for (int i = 0; i < row_; ++i) {
            for (int j = 0; j < col_; ++j) {
                cout <<i<<", "<<j<< endl; 
                char cur =array_[i * col_ + j];
                // Example condition: if the character is 'X', skip to the next row
                if (meituan_.find(cur)!= meituan_.end()) {
                    cout<<"\n"<<endl;
                    meituan_.erase(cur);
                    if(meituan_.empty()) {cout<< "YES"<<endl; return ;}
                    i++;
                    j = -1; // Setting j to -1 since after this iteration, j will be incremented by the loop to 0

                    if (i >= row_) { // Check if we're out of bounds after incrementing i
                        break;
                    }
                }
            }
        }
        cout<<"NO"<<endl;
    }


private:
    set<char> meituan_;
    int row_;
    int col_;
    char *array_;


    friend istream& operator>>(istream& input, mei_array& obj);
    friend ostream& operator<<(ostream& ouput, mei_array& obj);
    friend void has_the_set(set<char> the_set,mei_array& obj);

};

istream& operator>>(istream& input, mei_array& obj) {
    for (int i = 0; i < obj.row_; ++i) {
        for (int j = 0; j < obj.col_; ++j) {
            input >> obj.array_[i * obj.col_ + j];
        }
    }
    return input;
}
ostream& operator<<(ostream& output, mei_array& obj){
    for (int i = 0; i < obj.row_ ; ++i  ) {
        for (int j = 0; j < obj.col_; ++j) {
            output <<','<< obj.array_[i*obj.col_ + j];
        }
        cout << endl;
    }
    return output;
}


void has_the_set(set<char> the_set,mei_array& obj) {
        if(obj.row_ <the_set.size()) {cout<<"NO"<<endl;return;}
        int row_ = obj.row_ ;
        int col_ = obj.col_ ;
         for (int i = 0; i < row_; ++i) {
            for (int j = 0; j < col_; ++j) {
                cout <<i<<", "<<j<< endl; 
                char cur =obj.array_[i * col_ + j];
                // Example condition: if the character is 'X', skip to the next row
                if (the_set.find(cur)!= the_set.end()) {
                    cout<<"\n"<<endl;
                    the_set.erase(cur);
                    if(the_set.empty()) {cout<< "YES"<<endl; return ;}
                    i++;
                    j = -1; // Setting j to -1 since after this iteration, j will be incremented by the loop to 0

                    if (i >= row_) { // Check if we're out of bounds after incrementing i
                        break;
                    }
                }
            }
        }
        cout<<"NO"<<endl;
    }

int main() {
    // set<char> meituan = {'m','e','t','u','a','n'};
    int a, b;

    

    while (cin >> a >> b) {
        // Ensure the inputs are within bounds
        if (a * b > MAX_SIZE) {
            cerr << "Array dimensions exceed maximum allowed size." << endl;
            continue;
        }

        mei_array xiaomei(a,b);
        /*
        TO use the naive method you have to put char *array_; into public section.
        */
       
        // write in
        // for (int i = 0; i < a; ++i) {
        //     for (int j = 0; j < b; ++j) {
        //         cin >> xiaomei.array_[i * b + j];
        //     }

        // }

        cin >> xiaomei;

        // Print the 1D char array simulating a 2D array
        cout << xiaomei;


        xiaomei.has_meituan();

        set<char> second_set = {'X','f','j'};
        has_the_set(second_set,xiaomei);

    }
    return 0;
}


// The key here is to set `j` to `-1` because the loop automatically increments it by `1` after each iteration, which would make it `0` for the start of the new row.


/*

4 3
Xbc
dXf
ghX
jXl



OUTPUT:

,X,b,c
,d,X,f
,g,h,X
,j,X,l
0, 0

1, 0
1, 1

2, 0
2, 1
2, 2

3, 0
3, 1


0, 0
0, 1
0, 2
1, 0
1, 1
1, 2
2, 0
2, 1
2, 2
3, 0
3, 1
3, 2
NO



8 3
qbc
dmf
ghe
iql
tua
uan
rta
wwn



*/ 

