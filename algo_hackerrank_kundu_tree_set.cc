#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 100002
#define MODN 1000000007

class set{
	public:
		int val;
		int rank;
		int parent;
        int size;
};

vector<set> list(MAX);
int set_size = 1;

int find_root(int a){
	if(a == list[a].parent) return a;
	return list[a].parent = find_root(list[a].parent);
}

void union_set(int a, int b){
	int aroot = find_root(a);
	int broot = find_root(b);
	if(aroot == broot);
	else{
        if(list[aroot].rank > list[broot].rank) {
            list[broot].parent = aroot;
            list[aroot].size += list[broot].size;
            list[broot].size = -1;
        }
        else if(list[aroot].rank < list[broot].rank) {
            list[aroot].parent = broot;
            list[broot].size += list[aroot].size;
            list[aroot].size = -1;
        }
		else {
			list[broot].parent = aroot;
			list[aroot].rank++;
            list[aroot].size += list[broot].size;
            list[broot].size = -1;
		}
	}
}

void insert(int a){
	set inp;
	inp.val = a;
	inp.rank = 0;
	inp.parent = a;
    inp.size = 1;
	list[a] = inp;
}

void display(){
	for(int i = 1; i <= set_size; i++){
		cout << list[i].val << ", " << list[i].rank << ", " << list[i].parent << ", " << list[i].size << endl;
	}
}

void input(){
    long long int n, q;
    char c;
    int a1, a2;
    cin >> n;
    set_size = n+1;
    for(int i = 1; i <= n; i++){
        insert(i);
    }
    for(int i = 0; i < n-1; i++){
        cin >> a1 >> a2 >> c;
        if(c == 'b') union_set(a1, a2);
    }
    //display();
    
    long long int sum = 0;
    for(int i = 1; i <= n;i++){
        if(list[i].size > 1){
        	//cout << list[i].val << ", " << list[i].rank << ", " << list[i].parent << ", " << list[i].size << ", ";
            int p = list[i].size;
            sum += (((p*(p-1)/2) * (n-p)) + (p*(p-1)*(p-2)/6));
            //cout << (((p*(p-1)/2) * (n-p)) + (p*(p-1)*(p-2)/6)) << ", " << sum << endl;
        }
    }
    cout << (((n * (n-1) * 1LL * (n-2) * 1LL)/6) - (sum))%MODN << endl;
}

int main() {
    input();
    return 0;
}

/* ************************************************
Kundu is true tree lover. Tree is a connected graph having N vertices and N-1 edges. Today when he got a tree, he colored each edge with one of either red(r) or black(b) color. He is interested in knowing how many triplets(a,b,c) of vertices are there , such that, there is atleast one edge having red color on all the three paths i.e. from vertex a to b, vertex b to c and vertex c to a . Note that (a,b,c), (b,a,c) and all such permutations will be considered as the same triplet.

If the answer is greater than 109 + 7, print the answer modulo (%) 109 + 7.

Input Format 
The first line contains an integer N, i.e., the number of vertices in tree. 
The next N-1 lines represent edges: 2 space separated integers denoting an edge followed by a color of the edge. A color of an edge is denoted by a small letter of English alphabet, and it can be either red(r) or black(b).

Output Format 
Print a single number i.e. the number of triplets.

Constraints 
1 = N = 105
A node is numbered between 1 to N.

Sample Input

5
1 2 b
2 3 r
3 4 r
4 5 b
Sample Output

4
Explanation

Given tree is something like this.
img1

(2,3,4) is one such triplet because on all paths i.e 2 to 3, 3 to 4 and 2 to 4 there is atleast one edge having red color.
(2,3,5), (1,3,4) and (1,3,5) are other such triplets. 
Note that (1,2,3) is NOT a triplet, because the path from 1 to 2 does not have an edge with red color.

Copyright © 2016 HackerRank.
************************************************ */
