#include "list.c"

struct tmp_thread{
  int tmp_thread_id;
  int priority;
  struct RBNode* node;
};

struct tmp_thread* init_tmp_thread(int tmp_thread_id, int priority){
  struct tmp_thread* thread = (struct tmp_thread*) malloc(sizeof(struct tmp_thread));

  struct RBNode* node = init_node(priority);
  thread->tmp_thread_id = tmp_thread_id;
  thread->priority = priority;
  thread->node = node;
  return thread;
}

void test_rb_tree(void) {

    struct RBTree* tri;
    tri = init_tree();
    for(int i = 1; i <= 15; i++){
        struct tmp_thread* hilito = init_tmp_thread(i, i);
        rb_insert(tri, hilito->node);
    }

    print_inorder(tri);
    print_tree(tri);

    return;
}

int main(){
    test_rb_tree();
}