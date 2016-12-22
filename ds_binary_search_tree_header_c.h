#ifndef BINARY_SEARCH_TREE_DECL
#define BINARY_SEARCH_TREE_DECL

typedef int bool;
#define true 1
#define false 0

typedef struct Binary_Search_Tree_Node{
    void *value;
    struct Binary_Search_Tree_Node *left_node;
    struct Binary_Search_Tree_Node *right_node;
} binary_search_tree_node;

binary_search_tree_node* add_binary_search_node(binary_search_tree_node *main_node, void *new_value);
bool delete_binary_search_node(binary_search_tree_node *main_node, void *del_value);
binary_search_tree_node* search_binary_search_node(binary_search_tree_node *main_node, void *search_value);
int get_height_binary_search(binary_search_tree_node *main_node);
int count_of_nodes_binary_search(binary_search_tree_node *main_node);
void print_tree(binary_search_tree_node *main_node);

#endif // BINARY_SEARCH_TREE_DECL
