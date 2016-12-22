#include <stdio.h>
#include <stdlib.h>
#include "ds_tree_header_c.h"

/* ********************************************
    Display Tree for traversing through sub nodes.
    Also calculates level.
    Time Complexity : O(n)
    Space Complexity : O(1)
******************************************** */
void display_tree(tree_node *node){
    static int counter = 0;
    static int level = 0;
    int j = 0, i = 0;

    counter++;
    while(j < level) { printf(" "); j++;}
    printf("%c (%d - %d)\n", node->_value, node->_end_here, level);

    if(node){
            if(node->_children){
                while(node->_children[i]){
                    if(!i) level++;
                    display_tree(node->_children[i]);
                    i++;
                }
                level--;
            }
    }
}

/* *******************************************************
    Pre-load words from a text file
******************************************************* */
void load_words(tree *main_tree, int count)
{
    char line[80];
    FILE *fr;
    int i = 0;

    fr = fopen("./content_dictionary_words.txt", "rt");
    while(fgets(line, 80, fr) && i < count){
        printf("Loading %s...", line);
        add_node(main_tree, line);
        i++;
    }
    fclose(fr);
}


/* *******************************************************
    Main function
******************************************************* */
void main(void){

    char ch = 'Y';
    char input_word[STRING_MAX_LENGTH];
    int i, operation_choice = 1, count;
    bool search_result = false;

    tree *main_tree;
    main_tree = (tree*)malloc(sizeof(tree));
    main_tree->_root = NULL;
    do{
        printf("Enter 1 for add, 2 for search, 3 for remove, 4 for print tree, 5 for preload dictionary : ");
        scanf("%d", &operation_choice);

        if(operation_choice <  4){
            printf("Enter string : ");
            scanf("%s", input_word);
        }
        switch(operation_choice){
            case 1:
                add_node(main_tree, input_word);
                break;
            case 2:
                search_result = search_node_in_tree(main_tree, input_word);
                (search_result == true) ? printf("%s found", input_word):printf("%s not found", input_word);
                break;
            case 3:
                search_result = remove_node(main_tree, input_word);
                (search_result == true) ? printf("%s removed", input_word):printf("%s not found", input_word);
                break;
            case 4:
                display_tree(main_tree->_root);
                break;
            case 5:
                printf("Enter count: ");
                scanf("%d", &count);
                load_words(main_tree,count);
                break;
        }

        printf("Do you want to continue?");
        getchar();
        ch = getchar();
    }while(ch == 'Y' || ch=='y');

}
