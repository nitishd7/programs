#ifndef BINARY_TREE_DECL
#define BINARY_TREE_DECL

typedef struct Binary_Tree_Node{
    char _value;
    struct Binary_Tree_Node *_left_node;
    struct Binary_Tree_Node *_right_node;
} binary_tree_node;

typedef struct Binary_Tree{
    struct Binary_Tree_Node *_root;
    int _height;
} binary_tree;

binary_tree_node* create_node(char value, binary_tree_node *lnode, binary_tree_node *rnode);
void inorder_traversal(binary_tree_node *node);
void preorder_traversal(binary_tree_node *node);
void postorder_traversal(binary_tree_node *node);
void levelorder_traversal(binary_tree_node *node);
int evaluate_tree(binary_tree *tree);
binary_tree_node* create_mirrored_tree_wo_recursion(binary_tree_node *node);


#endif // BINARY_TREE_DECL

/* ************************************
Used for Expression trees
Input : abc*+
Output :
        +
    a           *
            b       c
************************************ */

