#ifndef UTILITIES_H
#define UTILITIES_H

#include "mybinarytree.h"
#include <queue>
#include <iostream>
#include <vector>

using namespace std;
typedef   mytreenode BSTNode;

void preorder(const mytreenode* const root);
void postorder(const mytreenode* const root);
void inorder(const mytreenode* const root);
void deletetree( mytreenode*& root);
void insertNode(mytreenode*&  root, const string& key);
mytreenode* buildtree(const vector<string> &vec);
mytreenode* contains(mytreenode* root, const string& key);
string finndRightMostNode(mytreenode*& root) ;
void deleteNode(mytreenode*&  root, const string& key);

//  experiment of a hypothesis
mytreenode** finndRightMostNodeAddress(mytreenode*& root);
void deleteNodeHypothesis(mytreenode*&  root, const string& key);

// Exercise 6: take a binary tree and return its height
int height(BSTNode *tree);
// int heightRec (BSTNode *tree); implement the recursive approach


void preorder(const mytreenode* const root){
    if(root == nullptr) return;
    cout<<root->value<<endl;
    preorder(root->left);       
    preorder(root->right);    
}

void postorder(const mytreenode* const root){
    if(root != nullptr) {
        postorder(root->left);       
        postorder(root->right);
        cout<<root->value<<endl;
    }
    
}

void inorder(const mytreenode* const root){
    if(root == nullptr) return;
    inorder(root->left);
    cout<<root->value<<endl;       
    inorder(root->right);
   
}

// in order can be used for building a tree(hypothesis)  . and for printing contents
// post order can be used for deleting a tree

//
void deletetree( mytreenode*& root){
    if(root != nullptr) {
        deletetree(root->left);       
        deletetree(root->right);
        cout<<"deleting   "<<root->value<<endl;
        delete root;
        root = nullptr;
    }
    
}

// build  a tree func
mytreenode* buildtree(const vector<string> &vec){
    mytreenode* root = nullptr;
    for (auto val = vec.begin();val!=vec.end() ;++val) { 
        insertNode(root,*val);
    }
    return root;
}

// insert a node into a tree
void insertNode(mytreenode*&  root, const string& key){
    if (root ==  NULL) {
        root = new mytreenode;
        root->value = key;
        root->left = root->right = NULL;
        return;
    }
    if (key != root->value) {
        if (key > root->value ) insertNode(root->right,key);
        else insertNode(root->left,key);

    }
}





mytreenode* contains(mytreenode* root, const string& key) {
    /* Base case: If the tree is empty, your key isn't here. */
    if (root == NULL) return NULL;

    /* Recursive case: See how we compare to the root. */
    if (key == root->value) {
        return root;
    }
    else {
        if (key < root->value) return contains(root->left, key);
        else /*  key > root->value */ return contains(root->right, key);
    }
}


// find the right most node of a sub tree and return the value inside of it
string finndRightMostNode(mytreenode*& root) {
    while(root->right != NULL){
        if(root->right->right != NULL) root = root->right;
        else {
            string nodevalue = root->right->value;
            delete root->right;
            root->right = NULL;
            return nodevalue;
        }
    }
    return "";

}

// Originally implemented deleteNode 

void deleteNode(mytreenode*&  root, const string& key){
    if (root == NULL) return;
    
    if (root->value == key) {
        // The node to delete is a child node:
        if(root->left ==NULL && root->right ==NULL) {
            delete root;
            root = NULL;
            return;
        }
        // The node to delete is a parent node with only one child node ,
        // Case 1:
        if(root->left ==NULL) {
            root->value = root->right->value;
            delete root->right;
            root->right = NULL;
            
        }
        // Case 2:
        if(root->right ==NULL) {
            root->value = root->left->value;
            delete root->left;
            root->left = NULL;
            
        }
        // The node to delete is a parent node ,which has two child nodes
        else {
            // Find the most right most node in the left subtree
            // reserve its value and free it
            string leftmostnodeval = finndRightMostNode(root->left);
            root->value = leftmostnodeval;
        }
        return;
        
    }
    if (key > root->value) deleteNode(root->right,key);
    if (key < root->value) deleteNode(root->left,key);


}


// A test of the hypothesis of using mytreenode**

mytreenode** finndRightMostNodeAddress(mytreenode*& root) {
    while(root->right != NULL){
        if(root->right->right != NULL) root = root->right;
        else {
            return &root->right;
        }
    }
    return NULL;

}

// mytreenode**  v.s. mytreenode*&
// In summary, mytreenode*& is a reference to a pointer, 
// allowing direct modification of the pointer itself, 
// while mytreenode** is a pointer to a pointer, providing 
// an indirect way to access and modify the original pointer.

// a better way to realize this function : findRight...


// mytreenode** findRightMostNodeAddress(mytreenode*& root) {
//     if (root->right == NULL) {
//         return &root;
//     }
//     return findRightMostNodeAddress(root->right);
// }

// following is even more better as it avoids pointer's pointer

// mytreenode*& findRightMostNodeAddress(mytreenode*& root) {
//     if (root->right == NULL) {
//         return root;
//     }
//     return findRightMostNodeAddress(root->right);
// }

// and in the deleteNode function rewrite the following part as so:

// mytreenode*& rightmostnode = findRightMostNodeAddress(root->left);
// root->value = rightmostnode->value;
// delete rightmostnode;
// rightmostnode = NULL;

//



// deleteNode using the func finndRightMostNodeAddress


void deleteNodeHypothesis(mytreenode*&  root, const string& key){
    if (root == NULL) return;
    
    if (root->value == key) {
        // The node to delete is a child node:
        if(root->left ==NULL && root->right ==NULL) {
            delete root;
            root = NULL;
            return;
        }
        // The node to delete is a parent node with only one child node ,
        // Case 1:
        if(root->left ==NULL) {
            root->value = root->right->value;
            delete root->right;
            root->right = NULL;
            
        }
        // Case 2:
        if(root->right ==NULL) {
            root->value = root->left->value;
            delete root->left;
            root->left = NULL;
            
        }
        // The node to delete is a parent node ,which has two child nodes
        else {
            // Find the most right most node in the left subtree
            // reserve its value and free it
            mytreenode** rightmostnode = finndRightMostNodeAddress(root->left);
            root->value = (*rightmostnode)->value;
// NOTE:
//rightmostnode is a pointer to a pointer to a mytreenode.
// *rightmostnode dereferences the pointer, giving you a pointer to a mytreenode. 
// accessing members of a object by a pointer using ->
// (*rightmostnode)->value accesses the value member of the mytreenode object being pointed to.
            
            delete (*rightmostnode);
            (*rightmostnode) = NULL;
        }
        return;
        
    }
    if (key > root->value) deleteNode(root->right,key);
    if (key < root->value) deleteNode(root->left,key);


}




// Implementing balanced tree




int height(BSTNode *tree){

    if (tree == NULL) return 0;
    std::queue<BSTNode*> nodeList;
    nodeList.push(tree);
    int height = 0;

    while(!nodeList.empty()) {

        int nodeCount = nodeList.size();
        while(nodeCount != 0) {
            BSTNode* node = nodeList.front();
            nodeList.pop();
            if(node->left != NULL) nodeList.push(node->left);
            if(node->right != NULL) nodeList.push(node->right);
            nodeCount--;
        }
        height++;
        
    }
    return height;

}


#endif