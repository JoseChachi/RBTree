#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum COLOUR {
    BLACK = 0,
    RED = 1
};

struct rb_thread{
    int priority;

    int thread_id;

    int secret_code;
};

struct RBNode{
    struct rb_thread* value;

    struct RBNode* parent;
    struct RBNode* leftNode;
    struct RBNode* rightNode;

    // 0 stands for BLACK, 1 stands for RED
    enum COLOUR colour;    
};

struct RBTree{
    struct RBNode* root;
    struct RBNode* nullSpace;
    int size;
};

// struct RBNode* init_node(int value){
//     struct RBNode* node;
//     node = (struct RBNode*) malloc(sizeof(struct RBNode));

//     node->value = value;
//     node->parent = NULL;
//     node->leftNode = NULL;
//     node->rightNode = NULL;
//     node->colour = RED;

//     return node;
// }

struct rb_thread* init_rb_thread(int thread_id, int priority){
    struct rb_thread* newThread;
    
    newThread = (struct rb_thread*) malloc(sizeof(struct rb_thread));

    newThread->thread_id = thread_id;
    newThread->priority = priority;

    newThread->secret_code = 123456;

    return newThread;
}


struct RBNode* init_node_with_thread(struct rb_thread* hilo){
    struct RBNode* node;
    node = (struct RBNode*) malloc(sizeof(struct RBNode));

    node->value = hilo;
    node->parent = NULL;
    node->leftNode = NULL;
    node->rightNode = NULL;
    node->colour = RED;

    return node;
}

struct RBTree* init_tree(){

    struct RBTree* tree;
    tree = (struct RBTree*) malloc(sizeof(struct RBTree));

    struct rb_thread* threadNull = init_rb_thread(0,0);
    struct RBNode* nullspace = init_node_with_thread(threadNull);
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
    
    while(z->parent->colour == RED){
        if(z->parent == z->parent->parent->leftNode){
            y = z->parent->parent->rightNode;
            if(y->colour == RED){
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->rightNode){
                    z = z->parent;
                    left_rotation(tree, z);
                }
                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                right_rotation(tree, z->parent->parent);
            }
        }
        else{
            y = z->parent->parent->leftNode;
            if(y->colour == RED){
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->leftNode){
                    z = z->parent;
                    right_rotation(tree,z);
                }
                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                left_rotation(tree,z->parent->parent);
            }
        }
    }
    tree->root->colour = BLACK;
}

void rb_insert(struct RBTree* tri, struct RBNode* z){
    struct RBNode* tmp = tri->root;
    struct RBNode* y = tri->nullSpace;
    tri->size += 1;
    while(tmp != tri->nullSpace){
        y = tmp;
        if(z->value->priority < tmp->value->priority) tmp = tmp->leftNode;
        else tmp = tmp->rightNode;
    }

    z->parent = y;

    if(y == tri->nullSpace) tri->root = z;
    else if(z->value->priority < y->value->priority) y->leftNode = z;
    else y->rightNode = z;

    z->leftNode = tri->nullSpace;
    z->rightNode = tri->nullSpace;

    recolour(tri, z);
}

struct RBNode* minimum(struct RBTree* tri, struct RBNode* node){
    if(node->leftNode != tri->nullSpace){
        return minimum(tri, node->leftNode);
    }
    return node;
}

struct RBNode* maximum(struct RBTree* tri, struct RBNode* node){
    if(node->rightNode != tri->nullSpace){
        return maximum(tri, node->rightNode);
    }
    return node;
}

void transplant(struct RBTree* tri, struct RBNode* u, struct RBNode* v){

    if (u->parent == tri->nullSpace) tri->root = v;
    else if (u == u->parent->leftNode) u->parent->leftNode = v;
    else u->parent->rightNode = v;

    v->parent = u->parent;
}

void rb_delete_helper(struct RBTree* tri, struct RBNode* x){
    struct RBNode* w;
    while(x != tri->root && x->colour == BLACK){
        if(x == x->parent->leftNode){
            w = x->parent->rightNode;
            if (w->colour == RED){
                w->colour = BLACK;
                x->parent->colour = RED;
                left_rotation(tri, x->parent);
                w = x->parent->rightNode;
            }
            if (w->leftNode->colour == BLACK && w->rightNode->colour == BLACK){
                w->colour = RED;
                x = x->parent;
            }
            else{
                if (w->rightNode->colour == BLACK){
                    w->leftNode->colour = BLACK;
                    w->colour = RED;
                    right_rotation(tri, w);
                    w = x->parent->rightNode;
                }
                w->colour = x->parent->colour;
                x->parent->colour = BLACK;
                w->rightNode->colour = BLACK;
                left_rotation(tri, x->parent);
                x = tri->root;
            }
        }
        else{
            w = x->parent->leftNode;
            if (w->colour == RED){
                w->colour = BLACK;
                x->parent->colour = RED;
                right_rotation(tri, x->parent);
                w = x->parent->leftNode;
            }
            if (w->rightNode->colour == BLACK && w->leftNode->colour == BLACK){
                w->colour = RED;
                x = x->parent;
            }
            else{
                if (w->leftNode->colour == BLACK){
                    w->rightNode->colour = BLACK;
                    w->colour = RED;
                    left_rotation(tri, w);
                    w = x->parent->leftNode;
                }
                w->colour = x->parent->colour;
                x->parent->colour = BLACK;
                w->leftNode->colour = BLACK;
                right_rotation(tri, x->parent);
                x = tri->root;
            }
        }
    }
    x->colour = BLACK;
}

void rb_delete(struct RBTree* tri, struct RBNode* z){
    struct RBNode* y = z;
    struct RBNode* x;
    enum COLOUR originalColour = y->colour;

    tri->size -= 1;

    if(z->leftNode == tri->nullSpace){
        x = z->rightNode;
        transplant(tri, z, z->rightNode);
    }
    else if (z->rightNode == tri->nullSpace){
        x = z->leftNode;
        transplant(tri, z, z->leftNode);
    }
    else {
        y = minimum(tri, z->rightNode);
        originalColour = y->colour;
        x = y->rightNode;
        if (y != z->rightNode){
            transplant(tri, y, y->rightNode);
            y->rightNode = z->rightNode;
            y->rightNode->parent = y;
        }
        else x->parent = y;
        transplant(tri, z, y);
        y->leftNode = z->leftNode;
        y->leftNode->parent = y;
        y->colour = z->colour;
    }
    if(originalColour == BLACK){
        rb_delete_helper(tri, x);
    }
}


void print_inorder_helper(struct RBTree* tri, struct RBNode* node){
    if(node != tri->nullSpace){
        print_inorder_helper(tri, node->leftNode);
        if(node->colour) printf("%d|R\t", node->value->priority);
        else printf("%d|B\t", node->value->priority);
        print_inorder_helper(tri, node->rightNode);
    }
}

void print_inorder(struct RBTree* tri){
    print_inorder_helper(tri, tri->root);
    printf("\n");
}

void print_node(struct RBTree* tri, struct RBNode* node){
    if(node != tri->nullSpace){
        if(node->colour) printf("---Printing info of node %d|R---\n", node->value->priority);
        else printf("---Print info of node %d|B---\n", node->value->priority);
        if(node->leftNode != tri->nullSpace) printf("My left is %d\n", node->leftNode->value->priority);
        else printf("I have no left\n");
        if(node->rightNode != tri->nullSpace) printf("My right is %d\n", node->rightNode->value->priority);
        else printf("I have no right\n");
        if(node->parent != tri->nullSpace) printf("My parent is %d\n", node->parent->value->priority);
        else printf("I have no parent\n");
        
    }
    else{
        printf("Null node");
    }
}

