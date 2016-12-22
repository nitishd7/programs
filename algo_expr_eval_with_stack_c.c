#include <stdio.h>
#include <stdlib.h>
#include "ds_binary_tree_header_c.h"
#include "ds_stack_header_c.h"

stack *expr_stack;
binary_tree_node *node[5];
char *symbols;

void execute();
void load_symbols();
void main(void)
{
    symbols = (char *)malloc(10 * sizeof(char));
    load_symbols();
    execute("abc*+");

}

void load_symbols()
{
    symbols[0] = '*';
    symbols[1] = '/';
    symbols[2] = '+';
    symbols[3] = '-';
}

bool is_operator(char value)
{
    int i = 0;
    for(i = 0; i < 4; i++){
        if(symbols[i] == value)
            return true;
    }
    return false;
}

void compute(char *prefix)
{
    int i = 0;
    binary_tree_node *left_node, *right_node;
    left_node = (binary_tree_node *)malloc(sizeof(binary_tree_node));
    right_node = (binary_tree_node *)malloc(sizeof(binary_tree_node));
    while(prefix[i] != '\0'){
        node[i] = create_node(prefix[i], NULL, NULL);
        if(!is_operator(prefix[i])){
            printf("%c is pushed\n", node[i]->_value);
            push(expr_stack,node[i]);
        }
        else{
            if(hasTop(expr_stack)){
                printf("Pop event\n");
                left_node = pop(expr_stack);
            }
            else{
                printf("Invalid input\n");
                break;
            }

            if(hasTop(expr_stack)){
                printf("Pop event\n");
                right_node = pop(expr_stack);
                }
            else {
                printf("Invalid input\n");
                break;
            }
            node[i]->_left_node = left_node;
            node[i]->_right_node = right_node;
            printf("%c is pushed\n", node[i]->_value);
            push(expr_stack, node[i]);
        }

        i++;
    }
}



void display()
{
    binary_tree_node *popped_node;
    while(hasTop(expr_stack)){
            popped_node = pop(expr_stack);
            if(popped_node){
                printf("Popped Value %c\n", popped_node->_value);
                inorder_traversal(popped_node);
                printf("\n");
                preorder_traversal(popped_node);
                printf("\n");
                postorder_traversal(popped_node);
                printf("\n");
                levelorder_traversal(popped_node);
                printf("\n");
            }
    }
}

void execute(char *prefix)
{

    printf("Hello\n");

    expr_stack = (stack *)malloc(sizeof(stack));
    expr_stack->_data = (binary_tree_node *)malloc(sizeof(binary_tree_node));

    compute(prefix);
    display();

}
