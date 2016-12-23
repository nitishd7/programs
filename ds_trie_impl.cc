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

void insert(string s){
	trie *t = root;
	for(int i = 0; i < s.length(); i++){
		if(t->links[s[i]-97] == nullptr){
			t->links[s[i]-97] = new trie();
			t->links[s[i]-97]->c = s[i];
			t->links[s[i]-97]->fullword = false;
			for(int j = 0; j < 26; j++) t->links[s[i]-97]->links[j] = nullptr;
		}
		t = t->links[s[i]-97];
		if(i == (s.length()-1)) t->fullword = true;
	}
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

/*string find_missing_letter(trie *n, string s, string cs, int i, bool used, int count){
	cout << i << ", " << cs << ", " << used << ", " << count << ", " << s << endl;
	string res = "";
	if((s.length() > cs.length() && n->links[s[i]-97] == nullptr)){
		if((used == false || count == 0) || (used == true || count == 1)){
			for(int j = 0;j < 26; j++){
				if(n->links[j] != nullptr) res = find_missing_letter(n->links[j], s, cs+n->links[j]->c, i, true, count + 1);
				if(res != "") break;
			}
			return res;
		}
		else return "";
	}
	else{
		used = false;
		cout << "Inner: " << i << ", " << (s.length()>cs.length()? n->links[s[i]-97]->fullword:-1) << ", " << cs.length() << ", " << n->fullword << endl;
		if(i == s.length()-1 && (cs.length()<s.length() && n->links[s[i]-97]->fullword == true)) {
			cs += n->links[s[i]-97]->c;
			return cs;
		}
		else if(i == s.length()-1 && (cs.length() >= s.length() && n->fullword == true)){
			return cs;
		}
		else if(i == s.length()-1 && (cs.length()<s.length() && n->links[s[i]-97]->fullword != true )) {
			return find_missing_letter(n->links[s[i]-97],s , cs +n->links[s[i]-97]->c, i, used, count );
		}
		else if(i == s.length()-1 && cs.length() >= s.length()){ //&& n->links[cs[cs.length()-1]-97]->fullword != true){
			if((used == false || count == 0) || (used == true || count == 1)){
				for(int j = 0;j < 26; j++){
					if(n->links[j] != nullptr) res = find_missing_letter(n->links[j], s, cs+n->links[j]->c, i, true, count + 1);
					if(res != "") break;
				}
				return res;
			}
			else return "";
		} 
		else if(i < s.length()-1){
			if(n->links[s[i]-97] != nullptr) return find_missing_letter(n->links[s[i]-97], s, cs+n->links[s[i]-97]->c, i+1, used, count);
			else return "";
		}
	}
}*/

string find_missing_letters(trie *n, string s, string cs, int i, bool used, int count){
	string res = "";
	//cout << i << ", " << cs << ", " << used << ", " << count << ", " << s << endl;
	if(n != nullptr){
		if(i == s.length() && n->fullword == false){
			if((used == false && count == 0) || (used == true && count == 1)){
				for(int j = 0;j < 26; j++){
						if(n->links[j] != nullptr) res = find_missing_letters(n->links[j], s, cs+n->links[j]->c, i, true, count + 1);
						if(res != "") break;
				}
			}
			return res;
		}
		else if(i == s.length() && n->fullword == true) res = cs;
		else if(i < s.length() && n->links[s[i]-97] == nullptr) res = "";
		else if(i < s.length() && n->links[s[i]-97] != nullptr){
			//cout << "2" << endl;
			return find_missing_letters(n->links[s[i]-97], s, cs + n->links[s[i]-97]->c, i+1, false, count);
		}
	}
	//cout << "End of fmsl" << endl;
	return res;
}

string find_missing_word(trie *n, string s, string cs, int i){
	//cout << "fw = " << i << ", " << cs << ", " << ", " << s << endl;
	int iter = 0;
	string res = "";
	if(n != nullptr){
		if(i < s.length() && n->links[s[i]-97] != nullptr) res = find_missing_word(n->links[s[i]-97], s, cs+n->links[s[i]-97]->c, i+1); //gown in (gowns)
		else if (i == s.length()) res = "";
		//else res = find_missing_letter(n, s, cs, i, false, 0);
		if(res == ""){ //gons in (gon, gowns), gong in (going)
			for(int j = 0; j < 26; j++){
				if((j != s[i]-97)){ // && (cs.length() < s.length()
					if(n->links[j] != nullptr) res = find_missing_letters(n->links[j], s, cs+n->links[j]->c, i, true, 1);
					if(res != "") break;
				}
			}
			iter = 1;
			if(res == ""){// gns in (gone, gowns)
			//	cout << "3" << endl;
				for(int j = 0; j < 26; j++){
					if((j != s[i]-97) && (n->links[j] != nullptr)){
						for(int k = 0; k < 26; k++){
							if(n->links[j]->links[k] != nullptr){
								res = find_missing_letters(n->links[j]->links[k], s, cs+n->links[j]->c+n->links[j]->links[k]->c, i, true, 2);
								if(res != "") break;
							}
						}
						if(res != "") break;
					}
				}
			}
		}
		return res;
	}
	return res;
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
	for(int i = 0; i < n; i++){
		words[i]="";
		cin >> words[i];
		insert(words[i]);
	}
	string sw;
	cin >> sw;
	cout << search(sw) << endl;
	for(int i = 0; i < 10; i++){
	string cwi;
	cin >> cwi;
	//string cw = find_missing_letter(root, cwi, "", 0, false, 0);
	string cw = find_missing_word(root, cwi, "", 0);
	cout << "Correct Word = " << cw << endl;
	}
	print(root,"");
	return 0;
}
