#include <stdio.h>
#include "ds_stack_header_c.h"

int _top = -1;

void push(stack *main_stack, void* value)
{
    if(main_stack){
        printf("Init crossed\n");
        if(_top < MAX_STACK_SIZE-1){
            main_stack[++_top]._data = value;
        }
        else{
            printf("Stack overflow\n");
        }
        printf("Push finished\n");
    }
}

void* pop(stack *main_stack)
{
    if(main_stack){
        return main_stack[_top--]._data;
    }
    else
        return NULL;
}

bool hasTop(stack *main_stack)
{
    if(main_stack)
    {
        return (_top > -1) ? true : false;
    }
    return false;
}
