#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct RBNode{
    int value;

    struct RBNode* parent;
    struct RBNode* leftNode;
    struct RBNode* rightNode;

    // 0 stands for black, 1 stands for red
    bool colour;    
};

struct RBTree{
    struct RBNode* root;
    int size;
};

void init_node(struct RBNode* node, int value){
    struct RBNode* newNode;
    node = (struct RBNode*) malloc(sizeof(struct RBNode));
    node->value = value;
    node->parent = NULL;
    node->leftNode = NULL;
    node->rightNode = NULL;
    node->colour = 1;
    printf("Reserved?\n");
}

void insert_helper(struct RBNode* node, int value){
    if(node == NULL){
        return;
    }
    else if(value < node->value){
        if(node->leftNode == NULL){
            struct RBNode inserted;
            init_node(&inserted, value);
            node->leftNode = &inserted;
            inserted.parent = node;
        }
        else{
            insert_helper(node->leftNode, value);
        }
    }
    else if(value > node->value){
        if(node->rightNode == NULL){
            struct RBNode inserted;
            init_node(&inserted, value);
            node->rightNode = &inserted;
            inserted.parent = node;
        }
        else{
            insert_helper(node->rightNode, value);
        }
    }
    else{
        printf("Same value\n");
    }
}

void insert(struct RBTree* tree, int value){

    if(tree->root == NULL){
        struct RBNode* node;
        init_node(node, value);
        //node->colour = 0;
        tree->root = node;
        printf("2222\n");
    }
    else{
        insert_helper(tree->root, value);
    }
}

void print_inorder_helper(struct RBNode* node){
    printf("fua chaval\n");
    if(node != NULL){
        print_inorder_helper(node->leftNode);
        printf("%d\t", node->value);
        print_inorder_helper(node->rightNode);
    }
}

void print_inorder(struct RBTree* tree){
    print_inorder_helper(tree->root);
}

