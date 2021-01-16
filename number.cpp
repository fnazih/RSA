#include<stdio.h>
#include<iostream>
#include "number.h"
using namespace std;

GrandNombre transform_phi(GrandNombre &gn, GrandNombre &N, GrandNombre &R);

GrandNombre::GrandNombre() {
	for(int i = 0; i < SIZE; i++)
	{
		Tab[i] = 0;
	}
}

GrandNombre::GrandNombre(uint64_t bigInt[SIZE]) {
	for(int i = 0; i < SIZE; i++) {
		Tab[i] = bigInt[i];
	}
}

//addition
GrandNombre GrandNombre::operator+(GrandNombre &gn) {
	int carry = 0;
	GrandNombre result;

	for(int i = SIZE - 1; i >= 0; i--) {
		result.set(i, Tab[i] + gn.getDataIndex(i) + carry);
		carry = (Tab[i] + gn.getDataIndex(i) + carry) >> 32;
	}

	return result;
}

//soustraction
GrandNombre GrandNombre::operator-(GrandNombre &gn) {
	GrandNombre result;

	for(int i = SIZE - 1; i >= 0; i--){
		result.set(i, Tab[i] - gn.getDataIndex(i));
	}

	return result;
}

//multiplication
GrandNombre GrandNombre::operator*(GrandNombre &gn) {
	GrandNombre result;
	uint64_t temp_res;

	for(int j = SIZE - 1; j >= 0; j--) {
		for(int i = SIZE - 1; i >= 0; i--) {
			temp_res = Tab[i]*gn.getDataIndex(j);
			result.set(i + j - (SIZE - 1), result.getDataIndex(i + j - (SIZE - 1)) + temp_res);
		}
	}

	return result;
}

//modular addition
GrandNombre GrandNombre::mod_add(GrandNombre &gn, GrandNombre &N) {
	GrandNombre result, temp_res;

	temp_res = *this + gn;

	if(temp_res > N) {
		result = temp_res - N;
	}
	else {
		result = temp_res;
	}

	return result;
}

//modular substraction
GrandNombre GrandNombre::mod_sub(GrandNombre &gn, GrandNombre &N) {
	GrandNombre result, temp_res, gn_null;
	gn_null = GrandNombre();	//creating the big null number

	temp_res = *this - gn;

	if(temp_res > gn_null) {
		result = temp_res;
	}
	else {
		result = temp_res + N;
	}

	return result;
}

//montgomery multiplication
GrandNombre GrandNombre::montgomery(GrandNombre &gn, GrandNombre &N, GrandNombre &V, GrandNombre &R) {
	GrandNombre result, s, t, m, u, phi_A, phi_B, temp;

	phi_A = transform_phi(*this, N, R);
	phi_B = transform_phi(gn, N, R);

	s = phi_A*phi_B;
	t = s*V;

	while (t > R) {
		t = t - R;
	}

	temp = t*N;
	m = s + temp;

	//u = m/R;

	result = u - N;

	return result;
}

GrandNombre transform_phi(GrandNombre &gn, GrandNombre &N, GrandNombre &R) {
	GrandNombre phi_gn;

	phi_gn = gn*R;

	while (phi_gn > N) {
		phi_gn = phi_gn - N;
	}

	return phi_gn;
}

//main
int main() {

	uint64_t bigInt1[SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x000000000000000F};
	uint64_t bigInt2[SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x000000000000000F};

	GrandNombre gn1(bigInt1);
	GrandNombre gn2(bigInt2);
	GrandNombre gnRes, gnRes2, gnRes3;

	gnRes = gn1 + gn2;
	cout << "gn1 + gn2 = " << gnRes << endl;

	gnRes2 = gn2 - gn1;
	cout << "gn2 - gn1 = " << gnRes2 << endl;

	gnRes3 = gn1*gn2;
	cout << "gn1 * gn2 = " << gnRes3 << endl;

	return 0;
}
