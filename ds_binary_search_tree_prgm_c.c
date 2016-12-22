#include<stdio.h>
#include<stdlib.h>
#include "ds_binary_search_tree_header_c.h"

void print_tree(binary_search_tree_node *main_node)
{

    if(main_node != NULL){
        printf("%d\n", *(int *)main_node->value);
        print_tree(main_node->left_node);
        print_tree(main_node->right_node);
    }
}

void main()
{
    binary_search_tree_node *root = NULL;

    int *val, i = 0;
    val = (int *)malloc(100 * sizeof(int));
    char ch= 'Y';
    do{
        printf("Enter number to add: ");
        scanf("%d", &val[i]);

        root = add_binary_search_node(root, &val[i]);
        print_tree(root);
        printf("Do you want to continue ?: ");
        getchar();
        scanf("%c", &ch);
        i++;
    }while(ch == 'Y' && i < 100);
}
