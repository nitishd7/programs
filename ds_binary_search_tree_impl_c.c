#include <stdio.h>
#include <stdlib.h>
#include "ds_binary_search_tree_header_c.h"

binary_search_tree_node* add_binary_search_node(binary_search_tree_node *main_node, void *new_value)
{
    binary_search_tree_node *traverser_node = main_node, *temp_node = NULL, *new_node = NULL;

    new_node = (binary_search_tree_node *)malloc(sizeof(binary_search_tree_node));
    new_node->value = new_value;
    new_node->left_node = NULL;
    new_node->right_node = NULL;

    if(traverser_node != NULL){
        while((temp_node = (*(int *)traverser_node->value > *(int *)new_value)?traverser_node->left_node:traverser_node->right_node)!= NULL){
            traverser_node = temp_node;
        }
        if(*(int *)traverser_node->value < *(int *)new_value){ traverser_node->right_node = new_node; }
        else{ traverser_node->left_node = new_node; }
    }
    else main_node = new_node;
    return main_node;
}

bool delete_binary_search_node(binary_search_tree_node *main_node, void *del_value)
{
    binary_search_tree_node *found_node = search_binary_search_node(main_node, del_value), *temp_node;
    if(found_node != NULL){
        if(found_node->left_node != NULL){
            temp_node = found_node;
            while(temp_node->left_node->left_node != NULL){
                temp_node = temp_node->left_node;
            }
        }
        else{

        }
    }
    else return false;
}

binary_search_tree_node* search_binary_search_node(binary_search_tree_node *main_node, void *search_value)
{
    binary_search_tree_node *traverser_node = main_node, *temp_node = NULL;
    if(traverser_node!= NULL){
        while((*(int *)traverser_node->value != *(int *)search_value) && (temp_node = (*(int *)traverser_node->value > *(int *)search_value)?traverser_node->left_node:traverser_node->right_node)!= NULL){
            traverser_node = temp_node;
        }
        if(temp_node != NULL) return traverser_node;
        else return NULL;
    }
    return NULL;
}

int get_height_binary_search(binary_search_tree_node *main_node)
{

}

int count_of_nodes_binary_search(binary_search_tree_node *main_node)
{

}
