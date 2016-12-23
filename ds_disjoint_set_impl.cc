#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;

#define MAX 10000

class set{
	public:
		int val;
		int rank;
		int parent;
};

vector<set> list(MAX);
int set_size = 1;

//assuming b < MAX
int find_root(int a){
	if(a == list[a].parent) return a;
	return list[a].parent = find_root(list[a].parent);
}

void union_set(int a, int b){
	int aroot = find_root(a);
	int broot = find_root(b);
	if(aroot == broot);
	else{
		if(list[aroot].rank > list[broot].rank) list[broot].parent = aroot;
		else if(list[aroot].rank < list[broot].rank) list[aroot].parent = broot;
		else {
			list[broot].parent = aroot;
			list[aroot].rank++;
		}
	}
}

void insert(int a){
	set inp;
	inp.val = a;
	inp.rank = 0;
	inp.parent = a;
	list[a] = inp;
}

void display(){
	for(int i = 1; i <= set_size; i++){
		cout << list[i].val << ", " << list[i].rank << ", " << list[i].parent << endl;
	}
}

void input(){
	int a,b,c;
	do{
		cin >> a;
		switch(a){
			case 1:
				cin >> b;
				insert(b);
				set_size++;
				break;
			case 2://union
				cin >> b >> c;
				union_set(b,c);
				break;
			case 3://find
				cin >> b;
				cout << find_root(b) << endl;
				break;
			default:
				break;
		}
	//	display();
	//	cout << endl;
	}while(a!= 0);
}

int main(){
	input();
	return 0;
}
