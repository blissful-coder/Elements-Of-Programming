#include <iostream>

using namespace std;

typedef struct node{
    int val;
    struct node* next;
}lnode;

void insert(lnode* &start, int val){
    lnode* temp;
    if(start==nullptr){
        temp = new lnode;
        temp->val = val;
        temp->next = nullptr;
        start = temp;
    }
    else{
        temp = start;
        while(temp->next!=nullptr){
            temp = temp->next;
        }
        temp->next = new lnode;
        temp->next->val = val;
        temp->next->next = nullptr;
    }
}

void show(lnode* start){
    cout<<"\nLL: ";
    lnode* temp=start;
    while(temp!=nullptr){
        cout<<temp->val<<"->";
        temp = temp->next;
    }
}

void swapKth(lnode* &start, int k){
    lnode* tempstart=start;
    lnode* tempstart_prev=start;
    lnode* tempend=start;
    lnode* tempend_prev=start;
    int totallength = 0;
    while(tempstart!=nullptr){
        // cout<<"\n T:"<<tempstart->val;s
        tempstart = tempstart->next;
        totallength++;
    }
    int countf = 1;
    tempstart = start;
    while(tempstart!=nullptr && countf<k){
        // cout<<"\n F:"<<tempstart->val;s
        tempstart_prev = tempstart;
        tempstart = tempstart->next;
        countf++;
    }
    // cout<<"\nFinal Front:"<<tempstart->val;
    int countb = 1;
    while(tempend!=nullptr && countb<totallength-k+1){
        // cout<<"\n B:"<<tempend->val;
        tempend_prev = tempend;
        tempend = tempend->next;
        countb++;
    }
    // cout<<"\nFinal Back:"<<tempend->val;
    lnode* temp = new lnode;
    cout<<"\nItems to swap: ["<<tempstart->val<<"] ["<<tempend->val<<"]";
    
    // If you only want to swap the values
    temp->val = tempend->val;
    tempend->val = tempstart->val;
    tempstart->val = temp->val;

    // FIX ME    
    // temp = tempend;
    // tempstart_prev->next = tempend;
    // tempend_prev->next = temp;

}

int main(){
    lnode* start=nullptr;
    insert(start,6);
    insert(start,46);
    insert(start,36);
    insert(start,26);
    insert(start,16);
    show(start);
    swapKth(start,2);
    show(start);
    return 0;
}