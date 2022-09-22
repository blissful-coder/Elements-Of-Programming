#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
} ll_type;

void insert_start_node(int data, ll_type **root);
void view_list(ll_type *root);

ll_type* insert_in_tree(int data, ll_type *root);
void pre_order(ll_type *root);
void post_order(ll_type *root);
void in_order(ll_type *root);

int main(){
    ll_type *root = NULL;
    ll_type *tree_root = NULL;
    printf("\n\nLINKED_LIST EXAMPLE:");
    insert_start_node(10, &root);
    view_list(root);
    insert_start_node(5, &root);
    view_list(root);
    insert_start_node(51, &root);
    view_list(root);

    printf("\n\nTREE EXAMPLE:");
    tree_root = insert_in_tree(13, tree_root);
    tree_root = insert_in_tree(10, tree_root);
    tree_root = insert_in_tree(12, tree_root);
    tree_root = insert_in_tree(6, tree_root);
    tree_root = insert_in_tree(8, tree_root);
    tree_root = insert_in_tree(11, tree_root);
    tree_root = insert_in_tree(15, tree_root);
    tree_root = insert_in_tree(14, tree_root);
    tree_root = insert_in_tree(17, tree_root);
    printf("\nPre Order: ");
    pre_order(tree_root);
    printf("\nPost Order: ");
    post_order(tree_root);
    printf("\nIn Order: ");
    in_order(tree_root);
    return 0;
}

void insert_start_node(int val, ll_type **root){
    ll_type* temp = NULL;
    temp = (ll_type*)malloc(sizeof(ll_type));

    if(*root==NULL){
        temp->data = val;
        temp->next = NULL;
        temp->prev = NULL;
        *root = temp;
    }
    else{
        temp->data = val;
        temp->next = *root;
        (*root)->prev = temp;
        *root = temp;
    }
}

void view_list(ll_type *root){
    // printf("%d ", root);
    printf("\nLIST:\n");
    while(root!=NULL){
        printf("%d ", root->data);
        root = root->next;
    }
}

ll_type* insert_in_tree(int val, ll_type *root){
    ll_type* temp = NULL;
    temp = (ll_type*)malloc(sizeof(ll_type));

    if(root==NULL){
        temp->data = val;
        temp->next = NULL;
        temp->prev = NULL;
        root = temp;
    }
    else{
        if(val>=root->data){
            root->next = insert_in_tree(val, root->next);
        }
        else{
            root->prev = insert_in_tree(val, root->prev);
        }
    }
    return root;
}

void pre_order(ll_type *root){
   
    if(root!=NULL){
        printf("%d ", root->data);
        pre_order(root->prev);
        pre_order(root->next);
    }
}
void post_order(ll_type *root){

    if(root!=NULL){
        post_order(root->prev);
        post_order(root->next);
        printf("%d ", root->data);
    }
}
void in_order(ll_type *root){

    if(root!=NULL){
        in_order(root->prev);
        printf("%d ", root->data);
        in_order(root->next);
    }
}