#include <iostream>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_DIM 2
#define nullptr 0

class node{
	public:
		int points[MAX_DIM];
		int dim;
		node * left;
		node * right;
};

node *root = nullptr;
int ndims = 0;

node *create_node(int point[]){
	node *n = new node();
	n->dim = ndims;
	for(int i = 0; i < ndims; i++){
		n->points[i] = point[i];
	}
	n->left = nullptr;
	n->right = nullptr;
}

node* insert(node *n, int i, int point[]){
	if(n == nullptr) return create_node(point);
	else{
		if(n->points[i%ndims] > point[i%ndims]) n->left = insert(n->left, i+1, point);
		else n->right = insert(n->right, i+1, point);
		return n;
	}
}

void level_order_display(){
	queue<pair<int,node *> > *q = new queue<pair<int,node *> >();
	q->push(pair<int, node*>(0,root));
	while(!q->empty()) {
		pair<int,node *> n = q->front();
		q->pop();
		cout << n.first << ": ";
		for(int i = 0; i < ndims; i++) cout << n.second->points[i] << " ";
		cout <<  endl;
		if(n.second->left != nullptr) q->push(pair<int, node*>(n.first+1,n.second->left));
		if(n.second->right != nullptr) q->push(pair<int, node*>(n.first+1, n.second->right));
	}
}

void construct_tree(){
	int numberOfPoints = 0;
	cin >> numberOfPoints;
	cin >> ndims;
	int point[ndims] = {0};
	for(int i = 0; i < numberOfPoints; i++){
		for(int j = 0; j < ndims; j++)
			cin >> point[j];
		root = insert(root, 0, point);
	//	level_order_display();
	//	cout << "------------------" << endl;
	}
}

node* find_min_dim(node *n, int i, int dim){
	if(n != nullptr){
		for(int j = 0; j < ndims; j++) cout << n->points[j] << " ";
		cout << endl;
		if(i%ndims == dim) return (n->left != nullptr)?find_min_dim(n->left, i + 1, dim): n;
		else{
			node *leftmin = (n->left != nullptr)?find_min_dim(n->left, i + 1, dim):n;
			node *rightmin = (n->right != nullptr)?find_min_dim(n->right, i + 1, dim):n;
			if(leftmin->points[dim] < rightmin->points[dim]) return leftmin;
			else return rightmin;
		}
	}
	return n;
}

//incomplete
node * find_neighbor(node *n, int i, node *cur, int point[]){
	static double cm = -1;
	if(n != nullptr){
		long long int sum = 0;
		for(int j = 0; j < ndims; j++){
			sum += ((n->points[j] - point[j]) * (n->points[j] - point[j]));
		}
		cout << cm << ", " << sqrt(sum) << ", ";
		for(int j = 0; j < ndims; j++) cout << n->points[j] << " ";
		cout << ", " << n->points[i%ndims] << ", " << point[i%ndims];
		cout << endl;
		if(cm == -1) cm = (sqrt(sum));
		if( cm > (sqrt(sum))) {
			cm = (sqrt(sum));
			cur = find_neighbor(n, i+1, n, point);
		}
		else{
			int flag = 0;
			for(int j = 0; j < ndims; j++){
				if(abs(n->points[j] - point[j]) > (int)floor(cm)) {
					flag = 1;
					break;
				}
			}
			if(flag == 1);
			/*{
				if(n->points[i%ndims] <= point[i%ndims] && n->right != nullptr) find_neighbor(n->right, i + 1, cur, cm, point);
				if(n->points[i%ndims] >= point[i%ndims] && n->left != nullptr) find_neighbor(n->left, i + 1, cur, cm, point); 
			}*/
			else{
				if(n->left != nullptr) cur = find_neighbor(n->left, i + 1, cur, point);
				if(n->right != nullptr) cur = find_neighbor(n->right, i + 1, cur, point);
			}
		}
		return cur;
	}
}

int main()
{
	int i;
	construct_tree();
	level_order_display();
	cin >> i;
	int point[ndims] = {0};
	node *n = nullptr;
	while(i!=5){
		switch(i){
			case 0: 
				int dim;
				cin >> dim;
				n = find_min_dim(root, 0, dim);
				if(n != nullptr){
					cout << "Min in dim = " << dim << endl; 
					for(int i = 0; i < ndims; i++) cout << n->points[i] << " ";
					cout << endl;
				}
				break;
			case 1:
				for(int j = 0; j < ndims; j++) cin >> point[j];
				node * cur;
				cur = find_neighbor(root, 0, nullptr, point);
				if(cur != nullptr){
					for(int j = 0; j < ndims; j++) cout << cur->points[j] << " ";
					cout << endl;
				}
				break;
			default: break;
		}
		cin >> i;
	}
	return 0;
}

/* Testing Input 
****************************************
Input 1:
6 2
2 3
5 4
9 6
4 7
8 1
7 2
0: 2 3
1: 5 4
2: 8 1
2: 9 6
3: 7 2
3: 4 7
0
1
2 3
5 4
8 1
7 2
Min in dim = 1
8 1
5

**************************************** */
