#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

int gcd(int var1, int var2){
	if(var1 > var2){
		var2 = var2 + var1;
		var1 = var2 - var1;
		var2 = var2 - var1;
	}
	if(var1 == var2) return var1;
	else if (var1 == 0) return var2;
	else return gcd(var2%var1, var1);
}

long long int print_all_permutations(string seq, int start, int end){
	long long int counter = 0;
	if(start > end){
		cout << seq << endl;
		return 1;
	}
	else{
		for(int i = start; i <= end; i++){
			swap(seq[i], seq[start]);
			counter += print_all_permutations(seq, start+1, end);
			swap(seq[i], seq[start]); 
		}
	}
	return counter;
}

int main(){
	int opcode;
	int var1, var2;
	string seq;
	long long int count = 0;
	do{
		cout << "Enter operation you would like to perform" << endl;
		cout << "1: Compute gcd" << endl;
		cout << "2: print all permutations of a sequence" << endl;
		cout << "0: exit" << endl;
		cin >> opcode;
		switch(opcode){
			case 1:
				cout << "Enter 2 numbers: ";
				cin >> var1 >> var2;
				cout << gcd(var1, var2);
				break;
			case 2:
				cout << "Enter sequence: " << endl;
				cin.ignore();
				getline(cin, seq);
				count = print_all_permutations(seq, 0, seq.length()-1);
				cout << endl << "Count: " << count;
				break;
			default:
				break;
		}
		cout << endl;
	}while(opcode != 0);
	return 0;
}
