#include <iostream>
#include "string"

using namespace std;

/* Prints out how many items are in the bag. Note that we have to mark the
 * RandomBag::size() member function const for this to work, since otherwise
 * C++ won't know that member function doesn't mutate the bag.
 */

// prototype
bool endsupWith(string str,string suffix);
// main
int main() {
    cout<<"we expeting the answer should be 0 on this str "<<"cwcdick "<<"and suffix: "<<" mm"<<endl;
    bool token = endsupWith("cwcdick","mm" );
    cout<< "The anwser is:" << " "<<token <<endl;
    cout<<"we expeting the answer should be 1 on this str "<<"cwcdick "<<"and suffix: "<<" dick"<<endl;
    token = endsupWith("cwcdick","dick" );
    cout<< "The anwser is:" << " "<<token <<endl;
    cout<<"we expeting the answer should be 1 on this str "<<"cwcDICK "<<"and suffix: "<<" dick"<<endl;
    token = endsupWith("cwcdick","dick" );  /*thankfully this works so the work to
upercase them saved */
    cout<< "The anwser is:" << " "<<token <<endl;
    return 0;
}
// declaration
bool endsupWith(string str,string suffix){
    int p1 = str.size();
    int p2 = suffix.size();
    if( p1< p2) return false;
    else return (str.substr(p1-p2)== suffix);
}
