#include "list.c"

//global time for kernel
int ACTUAL_TIME = 0;


struct thread* init_thread(int thread_id, int priority){

    struct thread* thread = (struct thread*) malloc(sizeof(struct thread));

    thread->thread_id = thread_id;
    thread->priority = priority;
    

    thread->virtual_time = 0;
    thread->virtual_time = thread->virtual_time + (ACTUAL_TIME/thread->priority);


    struct RBNode* node = init_node(thread->virtual_time);
    node->thread = thread;
    thread->node = node;


    return thread;
}

void update_virtual_time(struct thread* thread){
    thread->virtual_time = thread->virtual_time + (ACTUAL_TIME/thread->priority);
    thread->node->value = thread->virtual_time;
}

void test_rb_tree(void) {
    int stop = 1;
    struct RBTree* tri;
    tri = init_tree();
    ACTUAL_TIME += 300;
    printf("Actual time increased to %d\n", ACTUAL_TIME);
    // Actual time is 300, at that time 8 threads are inserted.
    // Each thread has its id and priority from 1 to 8, respectively,
    for(int i = 1; i <= 8; i++){
        struct thread* hilito = init_thread(i, i);
        printf("Thread with id %d inserted in scheduler\n",hilito->thread_id);
        rb_insert(tri, hilito->node);
    }
    print_inorder(tri);
    print_tree(tri);

    while(stop) scanf("%d", &stop);
    for(int j=1; j<=10; j++) printf("\n");
    stop = 1;

    // Get first thread, should be with highest priority (8)
    struct RBNode* node1 = schedule(tri);
    struct thread* thread1 = node1->thread;
    printf("Thread picked as ready with id %d\n",node1->thread->thread_id);
    // The thread 5 would like to enter again.
    ACTUAL_TIME += 100;
    printf("Actual time increased to %d\n", ACTUAL_TIME);
    update_virtual_time(thread1);
    printf("Thread with id %d inserted in scheduler\n",thread1->thread_id);
    rb_insert(tri, thread1->node);
    // How is tree
    print_inorder(tri);
    print_tree(tri);

    while(stop) scanf("%d", &stop);
    for(int j=1; j<=10; j++) printf("\n");
    stop = 1;

    // Get second thread, should be with second highest priority (7)
    node1 = schedule(tri);
    thread1 = node1->thread;
    printf("Thread picked as ready with id %d\n",node1->thread->thread_id);
    // The thread 4 would like to enter again.
    ACTUAL_TIME += 1000;
    printf("Actual time increased to %d\n", ACTUAL_TIME);
    update_virtual_time(thread1);
    printf("Thread with id %d inserted in scheduler\n",thread1->thread_id);
    rb_insert(tri, thread1->node);
    // How is tree
    print_inorder(tri);
    print_tree(tri);


    return;
}

int main(){
    test_rb_tree();
}