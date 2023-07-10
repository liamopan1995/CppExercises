#include "mybinarytree.h"
#include <iostream>
#include <vector>
using namespace std;

void preorder(const mytreenode* const root);
void postorder(const mytreenode* const root);
void inorder(const mytreenode* const root);
void deletetree( mytreenode*& root);

mytreenode* buildtree(const vector<string> &vec);
void buildtreeREC(mytreenode*&  root, const vector<string>& vec,int& index);
bool contains(mytreenode* root, const string& key);


int main() {
    mytreenode* root = new mytreenode;
    root->value = "Germany";
    root->left = new mytreenode;

    root->left->value ="Austria";
    mytreenode* austria = root->left;
    root->left->left = nullptr;
    root->left->right = nullptr;

    root->right = new mytreenode;
    root->right->value ="Jordan";
    root->right->left = nullptr;
    root->right->right = nullptr;

    mytreenode* jordan = root->right;
    mytreenode* leftson = root->left;

    mytreenode* cuba = new mytreenode;
    cuba->value = "Cuba";
    cuba->right= nullptr;
    cuba->left= nullptr;
    jordan->left = cuba;

    mytreenode* nederland = new mytreenode;
    nederland->value = "Nederland";
    nederland->right= nullptr;
    nederland->left= nullptr;
    jordan->right = nederland;

    mytreenode* mexico = new mytreenode;
    mexico->value = "Mexico";
    mexico->right= nullptr;
    mexico->left= nullptr;
    austria->right = mexico;

    preorder(root);
    cout<< "***************"<<endl;
    postorder(root);
    cout<< "***************"<<endl;
    inorder(root);
    cout<< "***************"<<endl;
    if( contains(root, "Austria")) {cout<< "found the key in tree"<<endl;}
     cout<< "***************"<<endl;
    deletetree(root);

    cout<< "***************"<<endl;
    preorder(root);

    vector<string> list2  = {"One", "TWo", "Three", "Four", "Five", "Six", "Seven"};
    mytreenode* anothertree  = buildtree(list2);

    cout<< "***************"<<endl;
    preorder(anothertree);

}


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

// build  a tree wrapper func
mytreenode* buildtree(const vector<string> &vec){
    int  index = 0;
    mytreenode* root = nullptr;
    buildtreeREC(root,vec,index);
    return root;

}

// recursive one actucally does the work 
// it successfully build tress, but these trees all have  depth of N, 
// which just lost the point of using binary tree
// therefore we need balanced tree method for building a better structed
// BN tree where trees have about logN depth
void buildtreeREC(mytreenode*&  root, const vector<string>& vec,int& index){
    if(index < vec.size()) {
        root = new mytreenode;
        root -> value = vec[index];
        ++index;
        buildtreeREC(root->left,vec,index);       
        buildtreeREC(root->right,vec,index);

    }
    
}



//  balanced  tree 


//

bool contains(mytreenode* root, const string& key) {
    /* Base case: If the tree is empty, your key isn't here. */
    if (root == nullptr) return false;

    /* Recursive case: See how we compare to the root. */
    if (key == root->value) return true;
    else if (key < root->value) return contains(root->left, key);
    else /*  key > root->value */ return contains(root->right, key);
}

