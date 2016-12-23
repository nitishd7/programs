#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; 
#define nullptr 0

node * root = nullptr;

node * create(int val){
    node * nd = new node();
    nd->val = val;
    nd->left = nullptr;
    nd->right = nullptr;
    nd->ht = 0;
    return nd;
}

void leftleftRotation(node * nd){
    if(nd != nullptr){
        int tmp;
        node * tmpnode;
        tmp = nd->val;
        if(nd->left != nullptr) nd->val = nd->left->val;
        if(nd->left != nullptr) nd->left->val = tmp;
        
        tmpnode = nd->right;
        nd->right = nd->left;
        if(nd->right != nullptr) nd->left = nd->right->left;
        if(nd->right != nullptr) nd->right->left = nd->right->right;
        if(nd->right != nullptr) nd->right->right = tmpnode;
        
        nd->right->ht = max((nd->right->left!= nullptr? nd->right->left->ht:-1), (nd->right->right!= nullptr? nd->right->right->ht:-1)) + 1;
        nd->ht = max((nd->left!= nullptr? nd->left->ht:-1), (nd->right!= nullptr? nd->right->ht:-1)) + 1;
    }
}

void leftrightRotation(node * nd){
    if(nd != nullptr){
        int tmp;
        node *tmpnode;
        tmp = nd->val;
        if(nd->left != nullptr && nd->left->right != nullptr) nd->val = nd->left->right->val;
        if(nd->left != nullptr && nd->left->right != nullptr) nd->left->right->val = tmp;

        tmpnode = nd->right;
        if(nd->left != nullptr) nd->right = nd->left->right;
        if(nd->left != nullptr && nd->right != nullptr) nd->left->right = nd->right->left;
        if(nd->right != nullptr) nd->right->left = nd->right->right;
        if(nd->right != nullptr) nd->right->right = tmpnode;

		nd->left->ht = max((nd->left->left!= nullptr? nd->left->left->ht:-1), (nd->left->right!= nullptr? nd->left->right->ht:-1)) + 1;
        nd->ht = max((nd->left!= nullptr? nd->left->ht:-1), (nd->right!= nullptr? nd->right->ht:-1)) + 1;
    }
}

void rightleftRotation(node * nd){
    if(nd != nullptr){
        int tmp;
        node *tmpnode;
        tmp = nd->val;
        if(nd->right != nullptr && nd->right->left != nullptr) nd->val = nd->right->left->val;
        if(nd->right != nullptr && nd->right->left != nullptr) nd->right->left->val = tmp;

        tmpnode = nd->left;
        if(nd->right != nullptr) nd->left = nd->right->left;
        if(nd->right != nullptr && nd->left != nullptr) nd->right->left = nd->left->right;
        if(nd->left != nullptr) nd->left->right = nd->left->left;
        if(nd->left != nullptr) nd->left->left = tmpnode;

		nd->right->ht = max((nd->right->left!= nullptr? nd->right->left->ht:-1), (nd->right->right!= nullptr? nd->right->right->ht:-1)) + 1;
        nd->ht = max((nd->left!= nullptr? nd->left->ht:-1), (nd->right!= nullptr? nd->right->ht:-1)) + 1;
    }
}

void rightrightRotation(node * nd){
    if(nd != nullptr){
        int tmp;
        node * tmpnode;
        tmp = nd->val;
        if(nd->right != nullptr) nd->val = nd->right->val;
        if(nd->right != nullptr) nd->right->val = tmp;
        
        tmpnode = nd->left;
        nd->left = nd->right;
        if(nd->left != nullptr) nd->right = nd->left->right;
        if(nd->left != nullptr) nd->left->right = nd->left->left;
        if(nd->left != nullptr) nd->left->left = tmpnode;
        
        nd->left->ht = max((nd->left->left!= nullptr? nd->left->left->ht:-1), (nd->left->right!= nullptr? nd->left->right->ht:-1)) + 1;
        nd->ht = max((nd->left!= nullptr? nd->left->ht:-1), (nd->right!= nullptr? nd->right->ht:-1)) + 1;
    }
}

void rotateTree(node * nd){
	cout << "Rotate Tree = " << nd->val << endl; 
    int lht, rht, plht, prht;
    lht = (nd->left != nullptr)?nd->left->ht:-1;
    rht = (nd->right != nullptr)?nd->right->ht:-1;
    node * parent = (lht > rht)? nd->left: nd->right;
    if(parent != nullptr) {
        plht = (parent->left != nullptr)?parent->left->ht:-1;
        prht = (parent->right != nullptr)?parent->right->ht:-1;
        node * current = (plht > prht)? parent->left: parent->right;
    }
    if(lht >= rht && plht >= prht) leftleftRotation(nd);
    else if(lht >= rht && plht <= prht) leftrightRotation(nd);
    else if(lht <= rht && plht >= prht) rightleftRotation(nd);
    else rightrightRotation(nd);
}


void balanceTree(node * nd){
    rotateTree(nd);
}

void insertNode(node * nd, int val){
    int lht, rht;
    if(nd != nullptr){
        if(nd->val > val) {
            if(nd->left != nullptr) insertNode(nd->left, val);
            else nd->left = create(val);
        }
        else {
            if(nd->right != nullptr) insertNode(nd->right, val);
            else nd->right = create(val);
        }
        nd->ht = max((nd->left!= nullptr? nd->left->ht:-1), (nd->right!= nullptr? nd->right->ht:-1)) + 1;
        lht = (nd->left != nullptr)?nd->left->ht:-1;
        rht = (nd->right != nullptr)?nd->right->ht:-1;
        if(abs(lht - rht) > 1) balanceTree(nd);
    }
    else {
    	nd = create(val); 
    	root = nd;
	} 
    //return nd;
}
//delete logic
void deleteNode(node *nd, int val);
bool isLeaf(node *nd){
	bool flag = (nd->left == nullptr && nd->right == nullptr);
	cout << "flag = " << flag << endl;
	return (nd->left == nullptr && nd->right == nullptr);
}

void deleteWithMaxInLeftTree(node *nd, node *changend){
	int lht, rht;
	if(nd != nullptr){
		if(isLeaf(nd)){
			changend->val = nd->val;
			changend->left = nullptr;
			nd = changend;
		}
		else{
			if(nd->right == nullptr && nd->left != nullptr){
				changend->val = nd->val;
				changend->left = nd->left;
			}
			else{
				if(nd->right != nullptr && nd->right->right != nullptr) deleteWithMaxInLeftTree(nd->right, changend);
				else if(nd->right != nullptr && nd->right->right == nullptr) {
					changend->val = nd->right->val;
					if(isLeaf(nd->right)) nd->right = nullptr;
					else deleteNode(nd, nd->right->val);
				}
			}
		}
		nd->ht = max((nd->left!= nullptr? nd->left->ht:-1), (nd->right!= nullptr? nd->right->ht:-1)) + 1;
        lht = (nd->left != nullptr)?nd->left->ht:-1;
        rht = (nd->right != nullptr)?nd->right->ht:-1;
        if(abs(lht - rht) > 1) balanceTree(nd);
	}
}

void deleteWithMinInRightTree(node *nd, node *changend){
	int lht, rht;
	if(nd != nullptr){
		if(isLeaf(nd)){
			changend->val = nd->val;
			changend->left = nullptr;
			nd = changend;
		}
		else{
			if(nd->left == nullptr && nd->right != nullptr){
				changend->val = nd->val;
				changend->right = nd->right;
			}
			else{
				if(nd->left != nullptr && nd->left->left != nullptr) deleteWithMinInRightTree(nd->left, changend);
				else if(nd->left != nullptr && nd->left->left == nullptr) {
					changend->val = nd->left->val;
					if(isLeaf(nd->left)) nd->left = nullptr;
					else deleteNode(nd, nd->left->val);
				}
			}
		}
		nd->ht = max((nd->left!= nullptr? nd->left->ht:-1), (nd->right!= nullptr? nd->right->ht:-1)) + 1;
        lht = (nd->left != nullptr)?nd->left->ht:-1;
        rht = (nd->right != nullptr)?nd->right->ht:-1;
        if(abs(lht - rht) > 1) balanceTree(nd);
	}
}

void deleteNode(node *nd, int val){
	int lht, rht;
	if(nd != nullptr){
		if(nd == root && nd->val == val){
			if(nd->left == nullptr && nd->right == nullptr) root = nd->right;
			else if(nd->left != nullptr && nd->right == nullptr) root = nd->left;
			else if(nd->left == nullptr && nd->right != nullptr) root = nd->right;
			else deleteWithMaxInLeftTree(nd->left, nd);
		}
		else{
			if(nd->left != nullptr && nd->left->val == val){
				if(isLeaf(nd->left)) nd->left = nullptr;
				else if(nd->left->left != nullptr) deleteWithMaxInLeftTree(nd->left->left, nd->left);
				else deleteWithMinInRightTree(nd->left->right, nd->left);
			}
			else if(nd->right != nullptr && nd->right->val == val){
				if(isLeaf(nd->right)) nd->right = nullptr;
				else if(nd->right->left != nullptr) deleteWithMaxInLeftTree(nd->right->left, nd->right);
				else deleteWithMinInRightTree(nd->right->right, nd->right);
			}
			else if(nd->val > val) deleteNode(nd->left, val);
			else deleteNode(nd->right, val);
		}
		nd->ht = max((nd->left!= nullptr? nd->left->ht:-1), (nd->right!= nullptr? nd->right->ht:-1)) + 1;
        lht = (nd->left != nullptr)?nd->left->ht:-1;
        rht = (nd->right != nullptr)?nd->right->ht:-1;
        if(abs(lht - rht) > 1) balanceTree(nd);
	}
}

void display(node * nd){
	if(nd != nullptr){
		if(nd->left != nullptr) display(nd->left);
		cout << nd-> val << ", " << nd->ht << endl;
		if(nd->right != nullptr) display(nd->right);
	}
}

int main(){
	int a;
	char ch;
	while(true){
		cin >> ch;
		switch(ch){
			case 'i':
				cin >> a;
				insertNode(root,a);
				display(root);
			break;
			case 'd':
				cin >> a;
				deleteNode(root,a);
				display(root);
			break;
		}
		if(ch == 'n') break;
	}
	return 0;
}
