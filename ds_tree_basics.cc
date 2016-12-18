#include<iostream>
#include<cstdlib>
#include<queue>
#include<cmath>
#include<utility>
using namespace std;

#define nullptr 0

struct node{
	node * left;
	node * right;
	int element;
};

node * root;
int tree_height=-1;
int nelements = 0;

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
		nelements++;
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

int height(node *nd);

void levelorder_traversal(node *nd){
	if(nd != nullptr){
		int lvl = (tree_height>-1 && root != nullptr)?tree_height:height(root);
		queue<pair<node *, pair<int, long long int> > > q;
		q.push(make_pair<node *, pair<int, long long int> >(nd, make_pair<int, int>(0, pow(2,lvl + 1))));
		int current_cursor = 0, current_level = 0;
		while(!q.empty()){
			pair<node *, pair<int, long long int> > pnd = q.front();
			q.pop();
			if(pnd.second.first != current_level) {
				current_cursor = 0;
				current_level = pnd.second.first;
				cout << endl;
			}
			for(int i = 0; i < (pnd.second.second - current_cursor); i++){
				cout << " ";
			}
			current_cursor += (pnd.second.second - current_cursor) + 1;
			cout << pnd.first->element;
			
			if(pnd.first->left != nullptr) q.push(make_pair<node *, pair<int, long long int> >(pnd.first->left, make_pair<int, long long int>(pnd.second.first + 1, pnd.second.second-pow(2, lvl - pnd.second.first ))));
			if(pnd.first->right != nullptr) q.push(make_pair<node *, pair<int, long long int> >(pnd.first->right, make_pair<int, long long int>(pnd.second.first + 1, pnd.second.second + pow(2, lvl - pnd.second.first)))); 
		}		
	}
}

int height(node *nd){
	if(nd != nullptr){
		return max(height(nd->left), height(nd->right)) + 1;
	}
	else return -1;
}

void mirror_tree(node *nd){
	if(nd != nullptr){
		mirror_tree(nd->left);
		mirror_tree(nd->right);
		node *tmpnd = nd->left;
		nd->left = nd->right;
		nd->right = tmpnd;
		cout << nd->element << ", ";		
	}
}

node * search(node *nd, int value){
	if(nd != nullptr){
		if(nd->element == value) return nd;
		else if(nd->element > value) return search(nd->left, value);
		else return search(nd->right, value);
	}
	return nullptr;
}

void auto_fill(node *nd){
	root = nullptr;
	int nvalues = rand()%18 + 1;
	for(int i = 0; i < nvalues; i++){
		int _val = rand()%30 + 1;
		root = insert_node(root, _val);
		cout << _val << " ";
	}
	nelements = nvalues;
}

pair<node *, int> longest_diameter(node *nd){
	static int max_diameter = -1;
	static node * d_node; 
	if(nd != nullptr){	
		int l_ht = longest_diameter(nd->left).second;
		int r_ht = longest_diameter(nd->right).second;
		if(l_ht + r_ht + 1 > max_diameter){
			max_diameter = l_ht + r_ht + 1;
			d_node = nd;
		}
		return make_pair<node *, int>(nd, (max(l_ht, r_ht) + 1));
	}
	return make_pair<node *, int>(nullptr,0);
}

int main(){
	int opcode;
	pair<node *, int> long_d;
	int search_value;
	create_binary_tree();
	do{
		cout << "Enter opcode for the operation to be performed" << endl;
		cout << "0: exit" << endl;
		cout << "1: inorder traversal" << endl;
		cout << "2: preorder traversal" << endl;
		cout << "3: postorder traversal" << endl;
		cout << "4: levelorder traversal" << endl;
		cout << "5: mirror tree" << endl;
		cout << "6: print height of the tree" << endl;
		cout << "7: print longest diameter of the tree" << endl;
		cout << "8: search for an element" << endl;
		cout << "9: autofill the tree" << endl;
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
				levelorder_traversal(root);
				break;
			case 5:
				mirror_tree(root);
				break;
			case 6:
				tree_height = (tree_height>-1 && root != nullptr)?tree_height:height(root);
				cout << tree_height;
				break;
			case 7:
				long_d = longest_diameter(root);
				if(long_d.first != nullptr) cout << long_d.first->element << ", " << long_d.second;
				break;
			case 8:
				cout << "Enter number to search : ";
				cin >> search_value;
				if(search(root, search_value) != nullptr) cout << "match found";
				else cout << "no match found";
				break;
			case 9:
				auto_fill(root);
				break;
			default:
				break;
		}
		cout << endl;
	}while(opcode != 0);
	return 0;
}
