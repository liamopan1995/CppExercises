#include "mybinarytree.h"
#include <iostream>
#include <vector>
#include "utilities.h"
using namespace std;

// typedef  mytreenode BSTNode;

// void preorder(const mytreenode* const root);
// void postorder(const mytreenode* const root);
// void inorder(const mytreenode* const root);
// void deletetree( mytreenode*& root);
// void insertNode(mytreenode*&  root, const string& key);
// mytreenode* buildtree(const vector<string> &vec);
// mytreenode* contains(mytreenode* root, const string& key);
// string finndRightMostNode(mytreenode*& root) ;
// void deleteNode(mytreenode*&  root, const string& key);

// //  experiment of a hypothesis
// mytreenode** finndRightMostNodeAddress(mytreenode*& root);
// void deleteNodeHypothesis(mytreenode*&  root, const string& key);




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
    // TESTING FUNCTION heifht(BSTNode*):
    cout<< "height of the tree nameed root is: "<< height(root)<<endl;

    mytreenode* found = contains(root, "Austria");
    if( found ) {
        cout<< "found the key in tree\n";
        if (found != NULL) {
        cout<< "at: "<<found<<endl;
        cout<< found->value<<endl;
            }
        }
    cout<< "***************"<<endl;
    deletetree(root);

    cout<< "attempting to print the deleted tree: ***************"<<endl;
    preorder(root);


    // Testing the build tree function
    vector<string> list2  = {"Grumpy", "Sleepy", "Doc", "Bashful", "Dopey", "Happy", "Sneezy"};
    mytreenode* dwarfs  = buildtree(list2);
    cout<< "result of pre order travesal is:***************"<<endl;
    preorder(dwarfs);
    cout<< "result of in order travesal is:***************"<<endl;
    inorder(dwarfs);
    cout<< "result of post order travesal is:***************"<<endl;
    postorder(dwarfs);

        
    // START OF Testing of function height()
    // A list in which dwarf's names are stored in alphabetical order: unbalanced
    // inserting names in alphabetical order will result a unbalaced tree which more like a linked list 
    // this unbalanced tree therefore is expected to has a height of unbalanced.size();
    vector<string> unbalanced  = {"Bashful","Doc","Dopey","Grumpy","Happy","Sleepy","Sneezy"};
    mytreenode* unbalancedDwarfs  = buildtree(unbalanced);
    cout<< "height of the tree nameed : unbalancedDwarfs is: "<< height(unbalancedDwarfs)<<endl;
    cout<< "which is equal to the list's lenght: "<< unbalanced.size()<<endl;
    // END  OF Testing of height()

    cout<< ":***************"<<endl;
    found = contains(dwarfs, "Sneezy");
    if( found ) {
        cout<< "found the key in tree\n";
        if (found != NULL) {
        cout<< "at: "<<found<<endl;
        cout<< found->value<<endl;
            }
        }
    else cout<< "nothing found\n";

    cout<< "                After deleting Sneezy"<<endl;
    deleteNode(dwarfs, "Sneezy");
    //deleteNodeHypothesis(dwarfs, "Sneezy"); // TESTING OF THE HYPOTHESIS OF POINTER'S POINTER
    // It turnt out the hypothesis is true
    cout<< "result of pre order travesal is:***************"<<endl;
    preorder(dwarfs);
    cout<< "result of in order travesal is:***************"<<endl;
    inorder(dwarfs);
    cout<< "result of post order travesal is:***************"<<endl;
    postorder(dwarfs);

    cout<< "                After deleting Sleepy"<<endl;
    deleteNode(dwarfs, "Sleepy");
    cout<< "result of pre order travesal is:***************"<<endl;
    preorder(dwarfs);
    cout<< "result of in order travesal is:***************"<<endl;
    inorder(dwarfs);
    cout<< "result of post order travesal is:***************"<<endl;
    postorder(dwarfs);


    cout<< "                After deleting Grumpy"<<endl;
    deleteNode(dwarfs, "Grumpy");
    cout<< "result of pre order travesal is:***************"<<endl;
    preorder(dwarfs);
    cout<< "result of in order travesal is:***************"<<endl;
    inorder(dwarfs);
    cout<< "result of post order travesal is:***************"<<endl;
    postorder(dwarfs);

        cout<< "                After deleting Tarzan  (trying deleting non existing node)"<<endl;
    deleteNode(dwarfs, "Tarzan");
    cout<< "result of pre order travesal is:***************"<<endl;
    preorder(dwarfs);
    cout<< "result of in order travesal is:***************"<<endl;
    inorder(dwarfs);
    cout<< "result of post order travesal is:***************"<<endl;
    postorder(dwarfs);

    // visualizeTree(dwarfs);


}


// void preorder(const mytreenode* const root){
//     if(root == nullptr) return;
//     cout<<root->value<<endl;
//     preorder(root->left);       
//     preorder(root->right);    
// }

// void postorder(const mytreenode* const root){
//     if(root != nullptr) {
//         postorder(root->left);       
//         postorder(root->right);
//         cout<<root->value<<endl;
//     }
    
// }

// void inorder(const mytreenode* const root){
//     if(root == nullptr) return;
//     inorder(root->left);
//     cout<<root->value<<endl;       
//     inorder(root->right);
   
// }

// // in order can be used for building a tree(hypothesis)  . and for printing contents
// // post order can be used for deleting a tree

// //
// void deletetree( mytreenode*& root){
//     if(root != nullptr) {
//         deletetree(root->left);       
//         deletetree(root->right);
//         cout<<"deleting   "<<root->value<<endl;
//         delete root;
//         root = nullptr;
//     }
    
// }

// // build  a tree func
// mytreenode* buildtree(const vector<string> &vec){
//     mytreenode* root = nullptr;
//     for (auto val = vec.begin();val!=vec.end() ;++val) { 
//         insertNode(root,*val);
//     }
//     return root;
// }

// // insert a node into a tree
// void insertNode(mytreenode*&  root, const string& key){
//     if (root ==  NULL) {
//         root = new mytreenode;
//         root->value = key;
//         root->left = root->right = NULL;
//         return;
//     }
//     if (key != root->value) {
//         if (key > root->value ) insertNode(root->right,key);
//         else insertNode(root->left,key);

//     }
// }





// mytreenode* contains(mytreenode* root, const string& key) {
//     /* Base case: If the tree is empty, your key isn't here. */
//     if (root == NULL) return NULL;

//     /* Recursive case: See how we compare to the root. */
//     if (key == root->value) {
//         return root;
//     }
//     else {
//         if (key < root->value) return contains(root->left, key);
//         else /*  key > root->value */ return contains(root->right, key);
//     }
// }


// // find the right most node of a sub tree and return the value inside of it
// string finndRightMostNode(mytreenode*& root) {
//     while(root->right != NULL){
//         if(root->right->right != NULL) root = root->right;
//         else {
//             string nodevalue = root->right->value;
//             delete root->right;
//             root->right = NULL;
//             return nodevalue;
//         }
//     }
//     return "";

// }

// // Originally implemented deleteNode 

// void deleteNode(mytreenode*&  root, const string& key){
//     if (root == NULL) return;
    
//     if (root->value == key) {
//         // The node to delete is a child node:
//         if(root->left ==NULL && root->right ==NULL) {
//             delete root;
//             root = NULL;
//             return;
//         }
//         // The node to delete is a parent node with only one child node ,
//         // Case 1:
//         if(root->left ==NULL) {
//             root->value = root->right->value;
//             delete root->right;
//             root->right = NULL;
            
//         }
//         // Case 2:
//         if(root->right ==NULL) {
//             root->value = root->left->value;
//             delete root->left;
//             root->left = NULL;
            
//         }
//         // The node to delete is a parent node ,which has two child nodes
//         else {
//             // Find the most right most node in the left subtree
//             // reserve its value and free it
//             string leftmostnodeval = finndRightMostNode(root->left);
//             root->value = leftmostnodeval;
//         }
//         return;
        
//     }
//     if (key > root->value) deleteNode(root->right,key);
//     if (key < root->value) deleteNode(root->left,key);


// }


// // A test of the hypothesis of using mytreenode**

// mytreenode** finndRightMostNodeAddress(mytreenode*& root) {
//     while(root->right != NULL){
//         if(root->right->right != NULL) root = root->right;
//         else {
//             return &root->right;
//         }
//     }
//     return NULL;

// }

// // mytreenode**  v.s. mytreenode*&
// // In summary, mytreenode*& is a reference to a pointer, 
// // allowing direct modification of the pointer itself, 
// // while mytreenode** is a pointer to a pointer, providing 
// // an indirect way to access and modify the original pointer.

// // a better way to realize this function : findRight...


// // mytreenode** findRightMostNodeAddress(mytreenode*& root) {
// //     if (root->right == NULL) {
// //         return &root;
// //     }
// //     return findRightMostNodeAddress(root->right);
// // }

// // following is even more better as it avoids pointer's pointer

// // mytreenode*& findRightMostNodeAddress(mytreenode*& root) {
// //     if (root->right == NULL) {
// //         return root;
// //     }
// //     return findRightMostNodeAddress(root->right);
// // }

// // and in the deleteNode function rewrite the following part as so:

// // mytreenode*& rightmostnode = findRightMostNodeAddress(root->left);
// // root->value = rightmostnode->value;
// // delete rightmostnode;
// // rightmostnode = NULL;

// //



// // deleteNode using the func finndRightMostNodeAddress


// void deleteNodeHypothesis(mytreenode*&  root, const string& key){
//     if (root == NULL) return;
    
//     if (root->value == key) {
//         // The node to delete is a child node:
//         if(root->left ==NULL && root->right ==NULL) {
//             delete root;
//             root = NULL;
//             return;
//         }
//         // The node to delete is a parent node with only one child node ,
//         // Case 1:
//         if(root->left ==NULL) {
//             root->value = root->right->value;
//             delete root->right;
//             root->right = NULL;
            
//         }
//         // Case 2:
//         if(root->right ==NULL) {
//             root->value = root->left->value;
//             delete root->left;
//             root->left = NULL;
            
//         }
//         // The node to delete is a parent node ,which has two child nodes
//         else {
//             // Find the most right most node in the left subtree
//             // reserve its value and free it
//             mytreenode** rightmostnode = finndRightMostNodeAddress(root->left);
//             root->value = (*rightmostnode)->value;
// // NOTE:
// //rightmostnode is a pointer to a pointer to a mytreenode.
// // *rightmostnode dereferences the pointer, giving you a pointer to a mytreenode. 
// // accessing members of a object by a pointer using ->
// // (*rightmostnode)->value accesses the value member of the mytreenode object being pointed to.
            
//             delete (*rightmostnode);
//             (*rightmostnode) = NULL;
//         }
//         return;
        
//     }
//     if (key > root->value) deleteNode(root->right,key);
//     if (key < root->value) deleteNode(root->left,key);


// }




// // Implementing balanced tree