#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
#define nullptr 0

class node{
	public:
		int color;
		node *parent;
		node *left;
		node *right;
		int data;
};

node *root = nullptr;

node *create_node(node *nd, int val){
	node *new_nd = new node();
	new_nd->color = 0; //RED
	new_nd->data = val;
	new_nd->left = nullptr;
	new_nd->right = nullptr;
	new_nd->parent = nd;
	return new_nd;
}

node *left_rotate(node *p, node *n){
	n->parent = p->parent;
	if(p->parent != nullptr && p->parent->left == p) p->parent->left = n;
	if(p->parent != nullptr && p->parent->right == p) p->parent->right = n;
	p->parent = n;
	p->left = n->right;
	n->right = p;
	n->left->color = 0;
	n->right->color = 0;
	n->color = 1;
	return n;
}

node *right_rotate(node *p, node *n){
	cout << "Right Rotate" << endl;
	n->parent = p->parent;
	if(p->parent != nullptr && p->parent->left == p) p->parent->left = n;
	if(p->parent != nullptr && p->parent->right == p) p->parent->right = n;
	p->parent = n;
	p->right = n->left;
	n->left = p;
	n->left->color = 0;
	n->right->color = 0;
	n->color = 1;
	return n;
}

bool is_rotation_needed(node *p, node *n){
	if(p != nullptr && n != nullptr){
		if(p->color == 0 && n->color == 0){
			if(p->parent != nullptr){
				if(p->parent->left == p){
					if(p->parent->right != nullptr && p->parent->right->color == 0){
						//Push blackness down
						p->parent->color = 0;
						if(p->parent->left != nullptr) p->parent->left->color = 1;
						if(p->parent->right != nullptr) p->parent->right->color = 1;
						return false;
					}
					else{
						return true;
					}
				}
				else{
					if(p->parent->left != nullptr && p->parent->left->color == 0){
						//Push blackness down
						p->parent->color = 0;
						if(p->parent->left != nullptr) p->parent->left->color = 1;
						if(p->parent->right != nullptr) p->parent->right->color = 1;
						return false;
					}
					else{
						return true;
					}
				}
			}
			else{
				p->color = 1;
				return false;
			}
		}
		else return false;
	}
	return false;
}

node* complete_insert(node *par, node *nd){
	if(par != nullptr && nd != nullptr){
		node * ppar = par->parent;
		if(ppar != nullptr) {
			cout << "rotate_needed = " << is_rotation_needed(par, nd) << endl;
			if(par->left == nd && is_rotation_needed(par, nd)){
				if(ppar->left == par) par = left_rotate(ppar, par);
				else{
					nd = right_rotate(par, nd);
					par = left_rotate(ppar, nd);
				}	
			}
			else if(par->right == nd && is_rotation_needed(par, nd)){
				if(ppar->right == par) par = right_rotate(ppar, par);
				else{
					nd = left_rotate(par, nd);
					par = right_rotate(ppar, nd);
				}
			}
			else;
			return complete_insert(par->parent,par);
		}
		else return complete_insert(ppar, par);
	}
	return nd;
}

void insert(int val){
	node *nd = root;
	node * p = nullptr;
	while(nd != nullptr){
		p = nd;
		if(nd->data > val) nd = nd->left;
		else nd = nd->right;
	}
	if(p != nullptr){
		node * tmp = create_node(p,val);
		if(p->data > val) p->left = tmp;
		else p->right = tmp;
		root = complete_insert(p, tmp);
		root->color = 1;
	}
	else{
		root= create_node(p, val);
		root->color = 1;
		}	
}
void display(node * nd){
	if(nd != nullptr){
		display(nd->left);
		cout << nd->data << endl;
		display(nd->right);
	}
}

void levelorderdisplay(node * nd){
	if(nd != nullptr){
		queue<node*> q;
		node * popnd;
		q.push(nd);
		while(!q.empty()){
			popnd =q.front();
			cout << popnd->data << ", " << popnd->color <<  endl;
			if(popnd->left != nullptr) q.push(popnd->left);
			if(popnd->right != nullptr) q.push(popnd->right);
			q.pop();
		}
	}
}

void input(){
	int a;
	do{
		cin >> a;
		switch(a){
			case 1:
				int val;
				cin >> val;
				insert(val);
				break;
			default:
				break;
			}
		levelorderdisplay(root);
	}while(a!= 0);
}

int main(){
	input();
	
	return 0;
}
