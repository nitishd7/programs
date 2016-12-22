#ifndef STACK_DECL
#define STACK_DECL

#define MAX_STACK_SIZE 20

#ifndef BOOL
#define BOOL
typedef int bool;
#define true 1
#define false 0
#endif // BOOL

typedef struct Stack{
    int count;
    void *_data;
} stack;

void push(stack *main_stack, void* value);
void* pop(stack *main_stack);
bool hasTop(stack *main_stack);

#endif // STACK_DECL
