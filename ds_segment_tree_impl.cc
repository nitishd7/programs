#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAX (1 << 20)
int maxarr[MAX];

int construct_tree(int l, int r, int ind, int p[], int size){
	if(abs(r-l) == 1){
		maxarr[ind] = min(p[l],p[r]);
		return maxarr[ind];
	}
	else if(abs(r-l) == 0) return p[l];
	else{
		int mid = (l + r)/2;
		maxarr[ind] = construct_tree(l, mid, (ind * 2), p, size) + construct_tree(mid+1, r, ((ind * 2) + 1), p, size);
		return maxarr[ind];
	}
}

int update_tree(int l, int r, int ind, int p[], int size, int uind){
	if(uind <= r){
		if(abs(r-l) == 1){
			maxarr[ind] = p[l] + p[r];
			return maxarr[ind];
		}
		else if(abs(r-l) == 0) return p[l];
		else{
			int mid = (l+r)/2;
			if(uind <= mid) maxarr[ind] = ((mid+1)<r?maxarr[((ind * 2) + 1)]:p[r]) + update_tree(l, mid,(ind * 2), p, size, uind);
			else maxarr[ind] = (mid>l?maxarr[(ind * 2)]:p[l]) + update_tree(mid + 1, r,((ind * 2)+1), p, size, uind);
			return maxarr[ind];
		}
	}
}

int read_from_tree(int l, int r, int ind, int p[], int size, int uind){
	if(r == uind) return maxarr[ind];
	else if(r < uind) return maxarr[ind];
	else if(abs(r-l) == 1) return p[l];
	else if(abs(r-l) == 0) return p[l];
	else{
		int mid = (l+r)/2;
		if(uind <= mid) return read_from_tree(l, mid, (ind * 2), p, size, uind);
		else return maxarr[(ind * 2)] + read_from_tree(mid+1, r, ((ind * 2)+1), p , size, uind); 
	}
}

void display(int a[], int n, string txt){
	cout << txt << " : ";
	for(int i = 0; i < n; i++){
		if(a[i] != 0) cout << i << "-" << a[i] << " ";
	}
	cout << endl;
}

int main() {
    int m, n, q, a, ni, mi, p, count =0;
    cin >> m >> n >> q;
    int marr[m] ={0}, narr[n] = {0},karr[n+1] = {0};
    for(int i = 0; i < n; i++) {
        cin >> narr[i];
        marr[narr[i]]++;
    }
    for(int i = 0; i < m; i++){
        karr[marr[i]]++;
    }
    //display(karr, n+1, "karr");
    construct_tree(0, n, 1, karr, n+1);
    //display(maxarr, (2*n), "maxarr");
    
    for(int i = 0; i < q; i++){
        cin >> a;
        switch(a)
        {
            case 1: 
                cin >> ni >> mi;
                karr[marr[narr[ni]]]--;
                update_tree(0, n, 1, karr, n+1, marr[narr[ni]]);
                karr[marr[narr[ni]]-1]++;
                update_tree(0, n, 1, karr, n+1, marr[narr[ni]]-1);
                marr[narr[ni]]--;
				karr[marr[mi]]--;
				update_tree(0, n, 1, karr, n+1, marr[mi]);
                karr[marr[mi]+1]++;
                update_tree(0, n, 1, karr, n+1, marr[mi]+1);
                narr[ni] = mi;
                marr[mi]++;
                break;
            case 2:
                count = 0;
                cin >> p;
                cout << (p>0? read_from_tree(0, n, 1, karr, n+1, p-1): 0) << endl;
                break;
        }
    }
    return 0;
}

//Gretchen and Play from HackerRank
/*5 5 6
0 1 2 3 4
2 2
1 0 2
2 2
2 1
1 3 1
2 2*/

