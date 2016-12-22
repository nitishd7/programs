/*Binary Tree*/
#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"
#include "Stack.h"
#include "Queue.h"

binary_tree_node* create_node(char value, binary_tree_node *lnode, binary_tree_node *rnode){

    binary_tree_node *node;
    node = (binary_tree_node *)malloc(sizeof(binary_tree_node));
    node->_left_node = lnode;
    node->_right_node = rnode;
    node->_value = value;
    return node;
}

void inorder_traversal(binary_tree_node *node)
{
    if(node){
        inorder_traversal(node->_left_node);
        printf("%c ", node->_value);
        inorder_traversal(node->_right_node);
    }
}

void preorder_traversal(binary_tree_node *node)
{
    if(node){
        printf("%c ", node->_value);
        preorder_traversal(node->_left_node);
        preorder_traversal(node->_right_node);
    }
}


void postorder_traversal(binary_tree_node *node)
{
    if(node){
        postorder_traversal(node->_left_node);
        postorder_traversal(node->_right_node);
        printf("%c ", node->_value);
    }
}

void levelorder_traversal(binary_tree_node *node)
{
    queue *tree_queue;
    tree_queue = (queue *)malloc(sizeof(queue));
    tree_queue->_data = (void **)malloc(MAX_QUEUE_SIZE *sizeof(binary_tree_node *));
    tree_queue->count=0;
    int i = 0;
    while(i < MAX_QUEUE_SIZE){
        tree_queue->_data[i++] = NULL;
    }
    enqueue(tree_queue, node);
    binary_tree_node *temp_node;
    printf("%c ", node->_value);
    do
    {
        temp_node = dequeue(tree_queue);
     //   printf(" 1 ");
        if(temp_node){
         if(temp_node != NULL){
            if(temp_node->_left_node){
            printf("%c ", temp_node->_left_node->_value);
            enqueue(tree_queue, temp_node->_left_node);
            }
            if(temp_node->_right_node){
            printf("%c ", temp_node->_right_node->_value);
            enqueue(tree_queue, temp_node->_right_node);
            }
        }
        }
    } while(temp_node);
    tree_queue = NULL;
}
