#ifndef _mylbinarytree_h
#define _mylbinarytree_h
#include <string>

struct mytreenode
{
    std::string value;
    mytreenode* left;
    mytreenode* right;
    int bf;

    mytreenode() 
        : left(nullptr), right(nullptr), bf(0) {
        // Default constructor
    }

    mytreenode(const std::string& nodeValue, mytreenode* leftNode, mytreenode* rightNode, int balanceFactor = 0)
        : value(nodeValue), left(leftNode), right(rightNode), bf(balanceFactor) {
        // Constructor with parameters
    }


};

// Usage of the default constructor():
// mytreenode* node = new mytreenode;  // Create a new node using the default constructor

// node->value = "Hello";  // Set the value of the node
#endif
