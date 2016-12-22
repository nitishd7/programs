#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

int first_index = 0;
int last_index = -1;

bool is_empty(queue *main_queue, int index)
{
    return (main_queue->_data[index] != NULL) ? false: true;
}
void enqueue(queue *main_queue, void* value)
{
  //  printf("eq");
    if(is_empty(main_queue, (last_index+1)% MAX_QUEUE_SIZE)){
        main_queue->count++;
        last_index = (last_index+1)% MAX_QUEUE_SIZE;
        main_queue->_data[last_index] = value;
    }
    else{
        printf("Queue is full");
    }
}

void* dequeue(queue *main_queue)
{
   // printf(" Count : %d", main_queue->count);
    if(main_queue->count){
        main_queue->count--;
        void *temp_ref = main_queue->_data[first_index];
        main_queue->_data[first_index] = NULL;
        first_index = (first_index + 1)% MAX_QUEUE_SIZE;
        return temp_ref;
    }
    return NULL;
}

void print_queue(queue *main_queue)
{
    int i = first_index;
    while(i% MAX_QUEUE_SIZE != last_index)
    {
       // printf("pq");
        printf("%c ", *(((char **)(main_queue->_data))[i]));
        i++;
    }
    if(last_index != -1)
        printf("%c \n", *(((char **)(main_queue->_data))[last_index]));
}
