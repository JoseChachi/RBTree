#include "rbtree.h"


int main(){
    struct RBTree tri;
    insert(&tri, 3);
    print_inorder(&tri);
}