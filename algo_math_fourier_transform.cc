#include<iostream>
#include<cmath>
#include<iomanip>
#include<vector>
#include<set>
#include<complex>

using namespace std;
#define PI 3.14159265

void display(vector<complex<double> > matrix[], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << setprecision(1) << fixed << real(matrix[i][j]) << "," << imag(matrix[i][j]) << "   ";
		}
		cout << endl;
	}
}

void display_results(vector<complex<double> > results, int n){
	for(int i = 0; i < n; i++){	
		cout << setprecision(3) << fixed << real(results[i]) << ", " << imag(results[i]) << endl;
	}
}


void compute_discrete_fourier_transform(vector<complex<double> > matrix[], int n, vector<complex<double> > coeffs, vector<complex<double> > &results){
	for(int i = 0; i < n; i++){
		double rtotal = 0.0, itotal = 0.0;
		for(int j = 0; j < n; j++){
			rtotal += (real(matrix[i][j]) * real(coeffs[j]));
			itotal += (imag(matrix[i][j]) * real(coeffs[j]));
		}
		complex<double> d(rtotal, itotal);
		results.insert(results.begin() + i, d);
	}
}

void populate_x_values(vector<complex<double> > matrix[], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			complex<double> c(0.0, ((-2 * PI * i * j )/n));	
			matrix[i].insert(matrix[i].begin() + j, exp(c));
		}
	}
}

vector<complex<double> > compute_fast_fourier_transform(vector<complex<double> > coeffs, int n, int k){
	if(k == 1) {
		return coeffs;
	}
	else{
		vector<complex<double> > even_coeffs;
		vector<complex<double> > odd_coeffs;
		vector<complex<double> > even_results;
		vector<complex<double> > odd_results;
		vector<complex<double> > results(k);

		for(int i = 0; i < k; i++){
			complex<double> c(real(coeffs[i]), 0.0);
			if(i%2 == 0) even_coeffs.insert(even_coeffs.begin() + (i/2), c);
			else odd_coeffs.insert(odd_coeffs.begin() + ((i - 1)/2), c);
		}
		
		even_results = compute_fast_fourier_transform(even_coeffs, n, k/2);
		odd_results = compute_fast_fourier_transform(odd_coeffs, n, k/2);
			
		for(int i = 0; i < k/2; i++){
			complex<double> c(0.0, ((-2 * PI * i )/k));
			complex<double> x_val = exp(c);
			results[i] = (even_results[i] + (x_val * odd_results[i]));
			results[(i + (k/2))] = (even_results[i] - (x_val * odd_results[i]));
		}
		return results;
	}
}

int main(){
	int n;
	cin >> n;
	vector<complex<double> > matrix[n];
	vector<complex<double> > coeffs;
	vector<complex<double> > results;
	double tmp;
	for(int i = 0; i < n; i++) {
		cin >> tmp;
		complex<double> c(tmp, 0);
		coeffs.insert(coeffs.begin() + i, c);
	}
	populate_x_values(matrix, n);
	compute_discrete_fourier_transform(matrix, n, coeffs, results);
	cout << " ------------------------ Magical x matrix -------------------------- " << endl;
	display(matrix, n);
	cout << endl;
	cout << " ------------------------ Results from DFT -------------------------- " << endl;
	display_results(results, n);
	cout << endl;
	results = compute_fast_fourier_transform(coeffs, n, n);
	cout << " ------------------------ Results from FFT ----------------------------------- " << endl;
	display_results(results, n);
	return 0;
}

/*
n = 1, x = {1}

n = 2, x = {1, -1}

n = 4, x = {1, -i, -1, i}

Assume w = ((-2 * j * PI)/n) 
Computation to find x[j] = ( e ^ iw) = cos(w) + isin(w)

*/        
