#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum COLOUR {
    BLACK,
    RED
};

struct RBNode{
    int value;

    struct RBNode* parent;
    struct RBNode* leftNode;
    struct RBNode* rightNode;

    // 0 stands for 0, 1 stands for 1
    enum COLOUR colour;    
};

struct RBTree{
    struct RBNode* root;
    struct RBNode* nullSpace;
    int size;
};

struct RBNode* init_node(int value){
    struct RBNode* node;
    node = (struct RBNode*) malloc(sizeof(struct RBNode));

    node->value = value;
    node->parent = NULL;
    node->leftNode = NULL;
    node->rightNode = NULL;
    node->colour = RED;

    return node;
}

struct RBTree* init_tree(){

    struct RBTree* tree;
    tree = (struct RBTree*) malloc(sizeof(struct RBTree));

    struct RBNode* nullspace = init_node(0);
    nullspace->colour = BLACK;

    tree->size = 0;
    tree->nullSpace = nullspace;
    tree->root = tree->nullSpace;

    return tree;
}

struct RBNode* copy_node(struct RBNode* a, struct RBNode* b){

    a = (struct RBNode*) malloc(sizeof(struct RBNode));

    a->colour = b->colour;
    a->leftNode = b->leftNode;
    a->rightNode = b->rightNode;
    a->parent = b->parent;
    a->value = b->value;

    return a;
}


void left_rotation(struct RBTree* tri, struct RBNode* x){
    struct RBNode* y = x->rightNode;
    x->rightNode = y->leftNode;
    if(y->leftNode != tri->nullSpace) y->leftNode->parent = x;
    y->parent = x->parent;

    if(x->parent == tri->nullSpace) tri->root = y;
    else if(x == x->parent->leftNode) x->parent->leftNode = y;
    else x->parent->rightNode = y;

    y->leftNode = x;
    x->parent = y;
}

void right_rotation(struct RBTree* tri, struct RBNode* x){
    struct RBNode* y = x->leftNode;
    x->leftNode = y->rightNode;
    if(y->rightNode != tri->nullSpace) y->rightNode->parent = x;
    y->parent = x->parent;
    
    if(x->parent == tri->nullSpace) tri->root = y;
    else if(x == x->parent->rightNode) x->parent->rightNode = y;
    else x->parent->leftNode = y;

    y->rightNode = x;
    x->parent = y;
}

void recolour(struct RBTree* tree, struct RBNode* z){
    struct RBNode* y = NULL;
    
    while(z->parent->colour == 1){
        if(z->parent == z->parent->parent->leftNode){
            y = z->parent->parent->rightNode;
            if(y->colour == 1){
                z->parent->colour = 0;
                y->colour = 0;
                z->parent->parent->colour = 1;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->rightNode){
                    z = z->parent;
                    left_rotation(tree, z);
                }
                z->parent->colour = 0;
                z->parent->parent->colour = 1;
                printf("right\n");
                right_rotation(tree, z->parent->parent);
            }
        }
        else{
            printf("DEBUG321\n");
            y = z->parent->parent->leftNode;
            if(y->colour == 1){
                z->parent->colour = 0;
                y->colour = 0;
                z->parent->parent->colour = 1;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->leftNode){
                    z = z->parent;
                    right_rotation(tree,z);
                }
                z->parent->colour = 0;
                z->parent->parent->colour = 1;
                left_rotation(tree,z->parent->parent);
            }
        }
    }
    tree->root->colour = 0;
}



void insert(struct RBTree* tri, struct RBNode* z){
    struct RBNode* tmp = tri->root;
    struct RBNode* y = tri->nullSpace;

    while(tmp != tri->nullSpace){
        y = tmp;
        if(z->value < tmp->value) tmp = tmp->leftNode;
        else tmp = tmp->rightNode;
    }

    z->parent = y;

    if(y == tri->nullSpace) tri->root = z;
    else if(z->value < y->value) y->leftNode = z;
    else y->rightNode = z;

    z->leftNode = tri->nullSpace;
    z->rightNode = tri->nullSpace;

    recolour(tri, z);
}



void print_inorder_helper(struct RBTree* tree, struct RBNode* node){
    if(node != tree->nullSpace){
        print_inorder_helper(tree, node->leftNode);
        printf("%d|%d\t", node->value, node->colour);
        print_inorder_helper(tree, node->rightNode);
    }
}

void print_inorder(struct RBTree* tree){
    print_inorder_helper(tree, tree->root);
    printf("\n");
}

