// RBTree


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
    int value;

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


struct rb_thread* init_rb_thread(int thread_id, int priority);
struct RBNode* init_node(int value);
struct RBTree* init_tree();

struct RBNode* copy_node(struct RBNode* a, struct RBNode* b);

void left_rotation(struct RBTree* tri, struct RBNode* x);
void right_rotation(struct RBTree* tri, struct RBNode* x);

void recolour(struct RBTree* tree, struct RBNode* z);
void rb_insert(struct RBTree* tri, struct RBNode* z);

struct RBNode* minimum(struct RBTree* tri, struct RBNode* node);
struct RBNode* maximum(struct RBTree* tri, struct RBNode* node);

void transplant(struct RBTree* tri, struct RBNode* u, struct RBNode* v);
void rb_delete_helper(struct RBTree* tri, struct RBNode* x);
void rb_delete(struct RBTree* tri, struct RBNode* z);

void print_inorder_helper(struct RBTree* tri, struct RBNode* node);
void print_inorder(struct RBTree* tri);

void print_tree_helper(struct RBTree* tri, struct RBNode* node, int depth);
void print_tree(struct RBTree* tri);

void print_node(struct RBTree* tri, struct RBNode* node);

