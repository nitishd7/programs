#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

# define nullptr 0

typedef struct node{
	int value;
	int priority;
	node * left;
	node * right;
}node;

node * root = nullptr;

node * create(pair<int,int> val){
    node * nd = new node();
    nd->value = val.first;
    nd->priority = val.second;
    nd->left = nullptr;
    nd->right = nullptr;
    return nd;
}

void display(node * nd){
	if(nd != nullptr){
		display(nd->left);
		cout << nd->value << ", " << nd->priority << endl;
		display(nd->right);
	}
}

void levelorderdisplay(node * nd){
	if(nd != nullptr){
		queue<pair<node *,int> > q;
		pair<node *,int> popnd;
		q.push(make_pair(nd, -1));
		while(!q.empty()){
			popnd =q.front();
			cout << popnd.first->value << ", " << popnd.first->priority << ", " << popnd.second << endl;
			if(popnd.first->left != nullptr) q.push(make_pair(popnd.first->left, popnd.first->value));
			if(popnd.first->right != nullptr) q.push(make_pair(popnd.first->right, popnd.first->value));
			q.pop();
		}
	}
}


node * insertNode(node * nd, pair<int,int> val){
	node * newnd;
	if(nd == nullptr) {
		newnd = create(val);
		if(root == nullptr) root = newnd;
	}
	else{
		if(nd->value > val.first) {
			newnd = insertNode(nd->left, val);
			nd->left = newnd;
			if(newnd->priority < nd->priority){
				node * tmp = newnd->right;
				newnd->right = nd;
				nd->left = tmp;
				if(nd == root) root = newnd; 
			}
			else newnd = nd;
		}
		else{
			newnd = insertNode(nd->right,val);
			nd->right = newnd;
			if(newnd->priority < nd->priority){
				node * tmp = newnd->left;
				newnd->left = nd;
				nd->right = tmp;
				if(nd == root) root = newnd;
			}
			else newnd = nd;
		} 
	}
	return newnd;
}
bool isLeaf(node *nd){
	return (nd->left == nullptr && nd->right == nullptr);
}

node* deleteNode(node *nd, int val){
	if(nd != nullptr){
		if (nd->value < val) nd->right = deleteNode(nd->right, val);
		else if (nd->value > val) nd->left = deleteNode(nd->left, val);
		else{
			if(isLeaf(nd)) return nullptr;
			else {
				nd->priority = INT_MAX;
				if((nd->left != nullptr) && (nd->right == nullptr || nd->left->priority <= nd->right->priority))  {
					node *tmp = nd->left->right;
					node *ret = nd->left;
					nd->left->right = nd;
					nd->left = tmp;
					ret->right = deleteNode(nd, val);
					return ret;
				}
				else if((nd->right != nullptr) && (nd->left == nullptr || nd->left->priority >= nd->right->priority)){
					node *tmp = nd->right->left;
					node *ret = nd->right;
					nd->right->left = nd;
					nd->right = tmp;
					ret->left = deleteNode(nd, val);
					return ret;
				}
				else return nd;
			}
		}
	}
	else return nullptr;
}

int main(){
	pair<int,int> a;
	int tmp;
	char ch;
	while(true){
		cin >> ch;
		switch(ch){
			case 'i':
				cin >> tmp;
				a.first = tmp;
				//cin >> tmp;
				a.second = rand() % 20 + 1;//tmp;
				insertNode(root,a);
				levelorderdisplay(root);
			break;
			case 'd':
				cin >> tmp;
				root = deleteNode(root,tmp);
				levelorderdisplay(root);
		}
		if(ch == 'n') break;
	}
	return 0;
}
