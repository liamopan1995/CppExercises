# include <vector>
# include <string>
# include <iostream>
# include "mylinkedlist.h"

using namespace std;


void createlinkedlist (mynode*& start, const vector<string>& inputList);
void printlist (mynode* start);
void appendatbegin (mynode*& start, string val);
void appendatend (mynode*& start, string val); 
mynode* findval(mynode*& start, const string& target);
void appendafter(mynode*& start, const string& pos, const string& val);
void appendbefore(mynode*& start, const string& pos, const string& val);
void deletelist(mynode*& start);
void deleteval(mynode*& start,const string& val);
void reverselist (mynode*& start);

int main () {
    vector<string> strlist = {"Nepal","Brazil", "Japan", "Switzerland" };
    //mynode* firstList = new mynode;
    mynode* firstList = nullptr;
    createlinkedlist(firstList,strlist);
    reverselist(firstList);
    printlist(firstList);

    appendatbegin(firstList,"Germany");// add Germany at begin  : aka:prepend
    appendatend(firstList,"China"); // add China att the end
    appendafter(firstList,"Brazil","Belgium");// add Belgium after Brazil
    appendbefore(firstList,"Brazil","Nigeria"); // add Nigeria before Brazil
    printlist(firstList);

    deleteval(firstList,"Nepal");
    cout<<endl<<"after Nepal was removed :" <<endl;
    printlist(firstList);
    deleteval(firstList,"Germany");
    printlist(firstList);

    mynode* found = findval(firstList, "Japan");
    if (found != nullptr) {cout<<"found in address:"<<found<<endl;}
    else {cout<<"nothing found"<<endl;}

    deletelist(firstList);
    printlist(firstList);

    return 0;
}


void createlinkedlist (mynode*& start, const vector<string>& inputList) {

    if (inputList.empty()) return;
    size_t sz  = inputList.size();
    mynode* end = start;

    for (int i=0; i<sz;++i){
        
        mynode* elem = new mynode;
        elem->value = inputList[i];
        elem->next = nullptr;

        if(start == nullptr) start= elem;
        else  end->next = elem;
        end= elem;
    }
}

void printlist (mynode* start) {
    cout<< "started Print"<<endl<<endl;

    mynode* helper = start;
    while (helper!=nullptr) {
        cout<<helper->value<<endl;
        helper = helper->next;
    } 

    cout<<endl<< "finished Print"<<endl<<endl;
}

void appendatbegin (mynode*& start, string val) {

    mynode* elem = new mynode;
    elem->value =val;
    elem->next = start;
    start = elem;

}

void appendatend (mynode*& start, string val) {

    mynode* elem = new mynode;
    elem->value =val;
    elem->next = nullptr;

    if (start == nullptr) {start = elem;}

    mynode* helper = start;
    while (helper->next!= nullptr) {
        helper = helper->next;
    }
    helper->next = elem;


}

mynode* findval(mynode*& start, const string& target) {
    mynode* helper = start;
    while (helper != nullptr){
        if (helper->value == target) return helper;
        helper = helper->next;
    }
    return nullptr;

}

void appendafter(mynode*& start, const string& pos, const string& val) {
// find the pos
    mynode* found = findval(start, pos);
    if (found!= nullptr) {
        mynode* elem = new mynode;
        elem->value = val;
        elem->next = found->next;
        found->next = elem;
    }
}

void appendbefore(mynode*& start, const string& pos, const string& val){
    mynode* found = nullptr;

    mynode* helper = start;
    while (helper->next != nullptr){
        if (helper->next->value == pos) {
            found =  helper;
            break;
        }
        helper = helper->next;
    }
    //cout<<found->value<<"*"<<endl;

    if (found!= nullptr) {
        mynode* elem = new mynode;
        elem->value = val;
        elem->next = found->next;
        found->next = elem;

    }

}

void deletelist(mynode*& start){
    cout<<endl<< "deleting the whole list"<< endl;
    while (start!=nullptr) {
        
        mynode* cur = start->next;
        delete start ;
        start = cur;

    }
}

void deleteval(mynode*& start,const string& val){
    cout<<endl<< "deleting the val  "<<val<< endl;

    // special case : target happens to be at the begin of the list
    if(start != nullptr && start->value == val) {
        cout<<" found : "<<val<<"*"<<endl;
        mynode* temp = start->next;
        delete start;
        start = temp;
        return;
    }

    // find the coressponding val
    mynode* found = nullptr;
    mynode* helper = start;
    
    while (helper->next != nullptr){
        if (helper->next->value == val) {
            found =  helper;
            break;
        }
        helper = helper->next;
    }
    
    if (found!= nullptr) {
        cout<<" found : "<<found->next->value<<"*"<<endl;
        mynode* temp = found->next->next;
        delete found->next;
        found-> next = temp;
        return;

    }
    cout<<"trying to delete a nonexisting value"<<endl;
}

void reverselist(mynode*& start) {
    mynode* prev = nullptr;
    mynode* curr = start;
    mynode* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    start = prev;
}