#include<iostream>
#include<cstdlib>
using namespace std;

#define nullptr 0

struct node{
	node * left;
	node * right;
	int element;
};

node * root;

node * insert_node(node *nd, int value){
	if(nd == nullptr){
		nd  = new node;
		nd->left = nullptr;
		nd->right = nullptr;
		nd->element = value;
	}
	else{
		if(nd->element < value) nd->right = insert_node(nd->right, value);
		else nd->left = insert_node(nd->left, value);
	}
	return nd;
}

void create_binary_tree(){
	char ch;
	int value;
	cout << "Construct tree" << endl;
	do{
		cout << "Enter number" << endl;
		cin >> value;
		root = insert_node(root, value);
		cout << "Do you want to continue" << endl;
		cin >> ch;
	}while(ch == 'Y' || ch == 'y');
}

void inorder_traversal(node *nd){
	if(nd != nullptr){
		inorder_traversal(nd->left);
		cout << nd->element << " ";
		inorder_traversal(nd->right);
	}
}

void preorder_traversal(node *nd){
	if(nd != nullptr){
		cout << nd->element << " ";
		preorder_traversal(nd->left);
		preorder_traversal(nd->right);
	}
}

void postorder_traversal(node *nd){
	if(nd != nullptr){
		postorder_traversal(nd->left);
		postorder_traversal(nd->right);
		cout << nd->element << " ";
	}
}


int main(){
	int opcode;
	create_binary_tree();
	do{
		cout << "Enter opcode for the operation to be performed" << endl;
		cout << "0: exit" << endl;
		cout << "1: inorder traversal" << endl;
		cout << "2: preorder traversal" << endl;
		cout << "3: postorder traversal" << endl;
		cout << "4: print tree" << endl;
		cout << "5: mirror tree" << endl;
		cout << "6: print height of the tree" << endl;
		cout << "7: print longest diameter of the tree" << endl;
		cout << "8: level order traversal" << endl;
		cin >> opcode;
		switch(opcode){
			case 1: 
				inorder_traversal(root);
				break;
			case 2:
				preorder_traversal(root);
				break;
			case 3: 
				postorder_traversal(root);
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			default:
				break;
		}
		cout << endl;
	}while(opcode != 0);
	return 0;
}
