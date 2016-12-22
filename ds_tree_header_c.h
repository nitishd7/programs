/*General Tree*/

#ifndef TREE_NODE_DECL
#define TREE_NODE_DECL

typedef int bool;
#define true 1
#define false 0

#define STRING_MAX_LENGTH 20
#define MAX_CHILDREN 26
#define DEBUG 0

typedef struct Tree_Node {
    char _value;
    bool _end_here;
    struct Tree_Node **_children;
} tree_node;

typedef struct Tree{
    tree_node *_root;
    int _height;
    int _diameter;
    int _node_count;
} tree;


void add_node(tree *main_tree, char* value);
bool remove_node(tree *main_tree, char* value);
tree_node * search_node_in_children(tree_node *start_node, char value);
bool search_node_in_tree(tree *main_tree, char* value);

#endif // TREE_NODE_DECL

/* ***************************************************
    SCENARIO :
    Assume you have a word
    Anabelle
    root -> search_node(a) [if not exists(a) -> add_node(a)]-> search_node(n) ->....

    Anita
    root -> search_node(a) -> search_node(n) -> search_node(i) [create] -> ...

    Anitang
    now Anita is lost, so you should have a flag in node to say, I also form a word.

 **************************************************** */


