#include "rbtree.h"


int main(){
    struct RBTree* tri;
    tri = init_tree();

    struct rb_thread* hilo5 = init_rb_thread(5, 5);
    struct RBNode* faiv = init_node_with_thread(hilo5);
    rb_insert(tri, faiv);
    struct rb_thread* hilo4 = init_rb_thread(4, 4);
    struct RBNode* four = init_node_with_thread(hilo4);
    rb_insert(tri, four);
    struct rb_thread* hilo3 = init_rb_thread(3, 100);
    struct RBNode* trii = init_node_with_thread(hilo3);
    rb_insert(tri, trii);
    print_inorder(tri);
    // struct RBNode* four = init_node(4);
    // struct RBNode* two = init_node(2);
    // struct RBNode* uan = init_node(1);
    // struct RBNode* ocho = init_node(8);
    // struct RBNode* nove = init_node(9);
    // struct RBNode* ten = init_node(10);
    // struct RBNode* trii = init_node(3);

    // insert(tri, four);
    // print_inorder(tri);
    // insert(tri, two);
    // print_inorder(tri);
    // insert(tri,uan);
    // print_inorder(tri);
    // insert(tri, ocho);
    // print_inorder(tri);
    // insert(tri, nove);
    // print_inorder(tri);
    // insert(tri, ten);
    // print_inorder(tri);
    // insert(tri, trii);
    // print_inorder(tri);


    // delete(tri, ocho);
    // print_inorder(tri);
    //testing delete
    // print_node(tri, tri->root);
    // print_node(tri, tri->root->rightNode);
    // print_node(tri, tri->root->rightNode->leftNode);
    // print_node(tri, tri->root->rightNode->rightNode);
    // print_node(tri, tri->root->rightNode->leftNode->leftNode);

    //testing minimo
    // struct RBNode* minimo = minimum(tri, tri->root);
    // printf("%d\n", minimo->value);
    // printf("%d\n", tri->root->value);
    // print_inorder(tri);
}