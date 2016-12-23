#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAX 10000
#define nullptr 0
class trie{
	public:
		char c;
		trie *links[26];
		bool fullword;
};

trie *root = nullptr;

void create_root(){
	root = new trie();
	root->c = '\0';
	for(int i = 0; i < 26; i++) root->links[i] = nullptr;
	root->fullword = false;
}

bool insert(string s){
	trie *t = root;
	bool flag = true;
	int i = 0;
	for(i = 0; i < s.length(); i++){
		if(t->links[s[i]-97] == nullptr){
			t->links[s[i]-97] = new trie();
			t->links[s[i]-97]->c = s[i];
			t->links[s[i]-97]->fullword = false;
			for(int j = 0; j < 26; j++) t->links[s[i]-97]->links[j] = nullptr;
		}
		t = t->links[s[i]-97];
		if(t->fullword == true) {
			flag = false;
			break;
		}
        if(i == (s.length()-1)) {
            int j = 0;
            for(j = 0; j < 26;j++){
                if(t->links[j] != nullptr){
                    flag = false;
                    break;
                }
            }
            if(j == 26) flag = true;
            t->fullword = true;
        }
	}
	return flag;
}

bool search(string s){
	trie *t = root;
	int i =0;
	for(i = 0; i < s.length(); i++){
		if(t->links[s[i]-97] == nullptr) break;
		else t = t->links[s[i]-97];
	}
	if(i < s.length()) return false;
	else if(t->fullword == true) return true;
	else return false;
}

void print(trie *n, string s){
	if(n->fullword == true) cout << (s+n->c) << endl;
	for(int i = 0; i < 26; i++){
		if(n->links[i] != nullptr) print(n->links[i], s+n->c);
	}
}

int main(){
	create_root();
	
	int n = 0;
	cin >> n;
	string words[n];
	int i = 0;
	for(i = 0; i < n; i++){
		words[i]="";
		cin >> words[i];
		bool flag = insert(words[i]);
		if(flag == false){
			cout << "BAD SET" << endl;
			cout << words[i] << endl;
			break;
		}
	}
	if(i == n) cout << "GOOD SET" << endl;
	return 0;
}

/* **************************************************************
Given N strings. Each string contains only lowercase letters from a-j(both inclusive). The set of N strings is said to be GOOD SET if no string is prefix of another string else, it is BAD SET. (If two strings are identical, they are considered prefixes of each other.)

For example, aab, abcde, aabcd is BAD SET because aab is prefix of aabcd.

Print GOOD SET if it satisfies the problem requirement. 
Else, print BAD SET and the first string for which the condition fails.

Input Format 
First line contains N, the number of strings in the set. 
Then next N lines follow, where ith line contains ith string.

Constraints 
1=N=105 
1= Length of the string =60

Output Format 
Output GOOD SET if the set is valid. 
Else, output BAD SET followed by the first string for which the condition fails.

Sample Input00

7
aab
defgab
abcde
aabcde
cedaaa
bbbbbbbbbb
jabjjjad
Sample Output00

BAD SET
aabcde
Sample Input01

4
aab
aac
aacghgh
aabghgh
Sample Output01

BAD SET
aacghgh
Explanation 
aab is prefix of aabcde. So set is BAD SET and it fails at string aabcde.
************************************************************** */
