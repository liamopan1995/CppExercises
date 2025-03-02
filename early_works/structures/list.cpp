#include <list>
#include <iostream>

int main() {
    std::list<int> myList;

    // Inserting elements
    myList.push_back(1);
    myList.push_front(2);
    myList.push_back(3);

    // Accessing elements
    int frontElement = myList.front();
    int backElement = myList.back();

    std::cout << "Front element: " << frontElement << std::endl;
    std::cout << "Back element: " << backElement << std::endl;

    // Removing elements
    // myList.pop_front();
    // myList.pop_back();

    // Iterating over elements
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        // Access or modify the element using '*it'
        std::cout<< *it <<std::endl;
    }

    // Iterating over elements in the reverse order
    for (auto rit = myList.rbegin(); rit != myList.rend(); ++rit) {
        // Access or modify the element using '*it'
        std::cout<< *rit <<std::endl;
    }

    return 0;
}

