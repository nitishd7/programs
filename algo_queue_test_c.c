#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"


queue *main_queue;

void create_queue(){
    main_queue = (queue *)malloc(sizeof(queue));
    main_queue->_data = (void **)malloc(MAX_QUEUE_SIZE * sizeof(char *));
    int i = 0;
    while(i < MAX_QUEUE_SIZE){
        main_queue->_data[i++] = NULL;
    }
    char a = 'a', b1 = 'b', c = 'c', d = 'd';
    enqueue(main_queue, &a);
    print_queue(main_queue);
    enqueue(main_queue, &b1);
    print_queue(main_queue);
    char *b = dequeue(main_queue);
    if(b) printf("Dequeued %c \n", *b);
    print_queue(main_queue);
    enqueue(main_queue, &c);
    enqueue(main_queue, &d);
    print_queue(main_queue);
    b = dequeue(main_queue);
    if(b) printf("Dequeued %c \n", *b);
    print_queue(main_queue);
    b = dequeue(main_queue);
    if(b) printf("Dequeued %c \n", *b);
    print_queue(main_queue);
    b = dequeue(main_queue);
    if(b) printf("Dequeued %c \n", *b);
    b = dequeue(main_queue);
    if(b) printf("Dequeued %c \n", *b);
    b = dequeue(main_queue);
    if(b) printf("Dequeued %c \n", *b);

}

void main(void)
{
    create_queue();
}
