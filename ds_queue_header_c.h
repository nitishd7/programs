#ifndef QUEUE_DECL
#define QUEUE_DECL

#define MAX_QUEUE_SIZE 20

#ifndef BOOL
#define BOOL

typedef int bool;
#define true 1
#define false 0
#endif // BOOL

typedef struct Queue{
    int count;
    void **_data;
} queue;

void enqueue(queue *main_queue, void* value);
void* dequeue(queue *main_queue);
void print_queue(queue *main_queue);

#endif
