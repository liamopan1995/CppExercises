#include "mybinarytree.h"
#include <iostream>
#include <vector>
#include "utilities.h"
using namespace std;


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
    cout<< "using recursive height function height of the tree nameed : unbalancedDwarfs is: "<< heightRec(unbalancedDwarfs)<<endl;
    cout<< "which is equal to the list's lenght: "<< unbalanced.size()<<endl;
    if(isBalanced(unbalancedDwarfs)) cout<<"unbalancedDwarfs is a balanced tree\n";
    if(!isBalanced(unbalancedDwarfs)) cout<<"unbalancedDwarfs is not a balanced tree\n";
    if(isBalanced(dwarfs)) cout<<"dwarfs is a balanced tree\n";
    if(!isBalanced(dwarfs)) cout<<"dwarfs is not a balanced tree\n";

    if(hasBinarySearchProperty(unbalancedDwarfs)) cout<<"unbalancedDwarfs has bst property\n";
    if(!hasBinarySearchProperty(unbalancedDwarfs)) cout<<"unbalancedDwarfs has bst property\n";
    if(hasBinarySearchProperty(dwarfs)) cout<<"dwarfs has bst property\n";
    if(!hasBinarySearchProperty(dwarfs)) cout<<"dwarfs has bst property\n";

    BSTNode* root1 = nullptr;
    if (hasBinarySearchProperty(root1)) cout << "root1 has bst property\n";
    // Expected: "root1 has bst property" (an empty tree vacuously satisfies the binary search property)
    BSTNode* root2 = new mytreenode;
    root2->value = "Monday";
    if (hasBinarySearchProperty(root2)) cout << "root2 has bst property\n";
    // Expected: "root2 has bst property" (a single node tree satisfies the binary search property)

    BSTNode* root3 = new BSTNode{"B", nullptr, nullptr};
    root3->left = new BSTNode{"A", nullptr, nullptr};
    if (hasBinarySearchProperty(root3)) cout << "root3 has bst property\n";
    // Expected: "root3 has bst property" (the binary search tree [5, 10] satisfies the binary search property)

    BSTNode* root4 = new BSTNode{"A", nullptr, nullptr};
    root4->left = new BSTNode{"B", nullptr, nullptr};
    if (hasBinarySearchProperty(root4)) cout << "root4 has bst property\n";
    // Expected: No output (the binary search tree [15, 10] violates the binary search property)
    
    BSTNode* root5 = new BSTNode{"D", nullptr, nullptr};
    root5->left = new BSTNode{"B", nullptr, nullptr};
    root5->right = new BSTNode{"E", nullptr, nullptr};
    root5->left->left = new BSTNode{"A", nullptr, nullptr};
    root5->left->right = new BSTNode{"C", nullptr, nullptr};
    if (hasBinarySearchProperty(root5)) cout << "root5 has bst property\n";
    // Expected: "root5 has bst property" (the binary search tree [2, 5, 8, 10, 15] satisfies the binary search property)

    BSTNode* root6 = new BSTNode{"C", nullptr, nullptr};
    root6->left = new BSTNode{"A", nullptr, nullptr};
    root6->right = new BSTNode{"E", nullptr, nullptr};
    root6->left->left = new BSTNode{"D", nullptr, nullptr};
    root6->left->right = new BSTNode{"B", nullptr, nullptr};
    if (hasBinarySearchProperty(root6)) cout << "root6 has bst property\n";
    // Expected: No output (the binary search tree [12, 5, 8, 10, 15] violates the binary search property)

    BSTNode* root7 = new BSTNode{"D", nullptr, nullptr};
    root7->left = new BSTNode{"B", nullptr, nullptr};
    root7->right = new BSTNode{"F", nullptr, nullptr};
    root7->left->left = new BSTNode{"A", nullptr, nullptr};
    root7->left->right = new BSTNode{"C", nullptr, nullptr};
    root7->right->left = new BSTNode{"E", nullptr, nullptr};
    root7->right->right = new BSTNode{"G", nullptr, nullptr};
    if (hasBinarySearchProperty(root7)) cout << "root7 has bst property\n";
    // Expected: "root7 has bst property" (the binary search tree [20, 30, 40, 50, 70, 80, 90] satisfies the binary search property)


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
