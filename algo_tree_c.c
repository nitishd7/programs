/*Tree Implementation*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

bool _is_initialized = false;

/* *************************************************
    Node Creation Template
************************************************* */
tree_node* create_node(char value){
    tree_node *node;
    node = (tree_node *)malloc(sizeof(tree_node));
    node->_value = value;
    node->_children = NULL;
    node->_end_here = false;
    return node;
}

/* *************************************************
    Initialize Root
************************************************* */
void init(tree *main_tree){
    if(DEBUG) printf("Entered init method\n");

    int i;
    tree_node *node = create_node('0');
    main_tree->_root = node;
    main_tree->_height = 0;
    main_tree->_diameter = 0;
    main_tree->_node_count = 1;

    if(DEBUG) printf("Exit init method\n");
}

/* *************************************************
    Search value in a node's children
    Time Complexity: O(1)
    Space Complexity: O(1)
************************************************* */
tree_node* search_node_in_children(tree_node *start_node, char value)
{
    if(DEBUG) printf("Entered search_node_in_children method %c\n", value);

    int i = 0;
    if(start_node){
        if(start_node->_children){
            while(start_node->_children[i]){
                if(start_node->_children[i]->_value == value){
                    return start_node->_children[i];
                }
                i++;
            }
        }
    }
    if(DEBUG) printf("Exit search_node_in_children method \n");
    return NULL;
}

/* *************************************************
    Search value in a tree
    Time Complexity: O(strlen(val))/O(lgN)
    Space Complexity: O(1)
************************************************* */
bool search_node_in_tree(tree *main_tree, char* value)
{
    int i;
    tree_node *tracker_node = main_tree->_root, *temp_node;
    for(i = 0; i < strlen(value); i++){
        if(!(temp_node = search_node_in_children(tracker_node, value[i]))){
            return false;
        }
        tracker_node = temp_node;
    }
    return tracker_node->_end_here;
}

/* *************************************************
    Add a value to tree
    Time Complexity: O(lgN)
    Space Complexity: O(1)
************************************************* */
void add_node(tree *main_tree, char* value)
{
    if(DEBUG) printf("Entered add_node method\n");

    tree_node *tracker_node;
    tree_node *temp_node;
    int i, j, k;

    if(!_is_initialized){
        init(main_tree);
        _is_initialized = true;
    }
    tracker_node = main_tree->_root;

    for(i = 0; i < STRING_MAX_LENGTH && i < strlen(value); i++){
        if(!(temp_node = search_node_in_children(tracker_node, value[i]))){
            if(DEBUG) printf("Entered new node creation in add_node method\n");
            temp_node = create_node(value[i]);
            /* If parent has no children, allocate space for children and default them all to NULL */
            if(!tracker_node->_children){
                tracker_node->_children = (tree_node **)malloc(MAX_CHILDREN * sizeof(tree_node *));
                for(k = 0; k < MAX_CHILDREN; k++){ tracker_node->_children[k] = NULL; }
             }

            /*Assign a child node to the new node */
            j = 0;
            while(tracker_node->_children[j]){j++;}
            tracker_node->_children[j] = temp_node;
            if(DEBUG) printf("Entered new node creation in add_node method \n");
        }
        tracker_node = temp_node;
        tracker_node->_end_here = (i == (strlen(value)-1))? true : tracker_node->_end_here;

        if(DEBUG) printf("Exit add_node method\n");
    }
}

/* *************************************************
    Count number of children for a node
    Time Complexity: O(1)
    Space Complexity: O(1)
************************************************* */
int children_count(tree_node *node){
    int i = 0;
    if(node){
            if(node->_children){
                while(node->_children[i]){
                    i++;
                }
            }
    }
    return i;
}

/* *************************************************
    Remove value from tree
    Time Complexity: O(lgN)
    Space Complexity: O(1)
************************************************* */
bool remove_node(tree *main_tree, char* value)
{
    int i, j, sub_tree_index = -2;
    tree_node *tracker_node = main_tree->_root, *temp_node, *sub_tree_node;

    sub_tree_node = (children_count(tracker_node)) > 1? tracker_node: NULL;
    sub_tree_index = sub_tree_node ? -1: -2;
    for(i = 0; i < strlen(value); i++){
        if(!(temp_node = search_node_in_children(tracker_node, value[i]))){
            return false;
        }
        if(children_count(temp_node) > 1 || ((temp_node->_end_here == true) && (i < strlen(value)-1))) {
          sub_tree_node = temp_node;
          sub_tree_index = i;
        }
        tracker_node = temp_node;
    }
    if(tracker_node->_children){
        tracker_node->_end_here = false;
    }
    else{
        if(sub_tree_node){
                i = 0;
                j = i;
               while(sub_tree_node->_children[i])
               {
                   if(sub_tree_node->_children[i]->_value == value[sub_tree_index + 1]){ j++; }
                   sub_tree_node->_children[i] = sub_tree_node->_children[j];
                   i++; j++;
               }
        }
        else main_tree->_root->_children = NULL;
    }
    return true;
}




