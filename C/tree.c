#include <stdio.h>
#include <stdlib.h>

#define sz 10

typedef struct node{
    struct node *left;
    struct node *right;
    char data;
}treenode;

typedef struct charnode{
    struct charnode *next;
    char data;
}stringnode;


void printTree(treenode *root){
    if(root!=NULL){
        printf("%c",root->data);
        printTree(root->left);
        printTree(root->right);
    }
}

stringnode* pushFront(stringnode *start, char input){
    stringnode *temp;
    temp = (stringnode*) malloc(sizeof(stringnode));
    temp->data = input;
    temp->next = NULL;

    if(start==NULL){
        start = temp;
    }
    else{
        temp->next = start;
        start = temp;
    }
    return start;
}

stringnode* pushBack(stringnode *start, char input){
    stringnode *temp;
    stringnode *trav=start;
    temp = (stringnode*) malloc(sizeof(stringnode));
    temp->data = input;
    temp->next = NULL;

    if(start==NULL){
        start = temp;
    }
    else{
        while(trav->next!=NULL){
            trav = trav->next;
        }
        trav->next = temp;
    }
    return start;
}

stringnode* popBack(stringnode *start){
    stringnode *temp;
    stringnode *trav=start;
    if(start==NULL){
        return start;
    }
    else{
        while(trav->next!=NULL){
            trav = trav->next;
        }
        free(trav);
        trav=NULL;
    }
    return start;
}

stringnode* appendStringNode(stringnode *first, stringnode *second){
    stringnode *tf=first;

    if(first==NULL && second==NULL){
        return NULL;
    }
    else if(first==NULL){
        return second;
    }
    else if(second==NULL){
        return first;
    }
    else{
        while(tf->next!=NULL){
            tf=tf->next;
        }
        tf->next=second;
    }
    return first;
}

void printString(stringnode *start){
    if(start!=NULL){
        printf("[");
        while(start!=NULL){
            printf("%c",start->data);
            start = start->next;
        }
        printf("]");
    }
    else{
        printf("[EMPTY]");
    }
}

int solve(treenode *root, stringnode *accum, int sum){
    if(root!=NULL){
        printf("\nNode: %c",root->data);
        accum=pushBack(accum,root->data);
        printString(accum);
        if(root->left==NULL && root->right==NULL){
            printf("\nLeaf Node: ");
            printString(accum);
            return (sum*10 + (root->data - '0'));
        }
        else{
            return (    
                        solve(root->left,accum,sum*10 + (root->data - '0')) + 
                        solve(root->right,accum,sum*10 + (root->data - '0')) 
                    );
        }
    }
    else{
        return 0;
    }
}


int main(){
    treenode *root = (treenode*)malloc(sizeof(treenode));
    treenode *A = (treenode*)malloc(sizeof(treenode));
    A->left= NULL;
    A->right= NULL;
    A->data = '2';
    treenode *B = (treenode*)malloc(sizeof(treenode));
    B->left= NULL;
    B->right= NULL;
    B->data = '4';
    treenode *C = (treenode*)malloc(sizeof(treenode));
    C->left= NULL;
    C->right= NULL;
    C->data = '3';
    treenode *D = (treenode*)malloc(sizeof(treenode));
    D->left= NULL;
    D->right= NULL;
    D->data = '8';
    treenode *E = (treenode*)malloc(sizeof(treenode));
    E->left= NULL;
    E->right= NULL;
    E->data = '7';
    treenode *F = (treenode*)malloc(sizeof(treenode));
    F->left= NULL;
    F->right= NULL;
    F->data = '9';
    root->left = C;
    root->right = D;
    root->data = '5';
    C->left = A;
    C->right= B;
    B->left = E;
    B->right= F;


    printTree(root);
    printf("\n--------SOLVED---------\n");
    stringnode *accum1=NULL;
    // stringnode *accum2=NULL;
    // printString(accum1);
    // accum1 = pushBack(accum1,'3');
    // printString(accum1);
    // accum1 = pushBack(accum1,'4');
    // printString(accum1);
    // accum1 = pushBack(accum1,'5');
    // printString(accum1);
    // accum1 = pushBack(accum1,'6');
    // printString(accum1);
    // printString(accum2);
    // accum2 = pushBack(accum2,'8');
    // printString(accum2);
    // accum2 = pushBack(accum2,'7');
    // printString(accum2);
    // accum2 = pushBack(accum2,'2');
    // printString(accum2);
    // accum2 = pushBack(accum2,'3');
    // printString(accum2);
    // stringnode *res=NULL;
    // res = appendStringNode(accum1,accum2);
    // printf("\n");
    // printString(res);
    // res = popBack(res);
    // printString(res);
    
    printf("\n--------Answer---------: %d\n",solve(root,accum1,0));
    printString(accum1);
    // printf("%d",calcNumber(root,0));
    return 0;
}