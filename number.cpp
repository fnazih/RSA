#include<stdio.h>
#include<iostream>
#include "number.h"
using namespace std;


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
		carry = result.getDataIndex(i) >> SIZE;

		if(carry == 1) {
			result.set(i, result.getDataIndex(i) - 0x0000000100000000);
		}
	}

	return result;
}

//soustraction
GrandNombre GrandNombre::operator-(GrandNombre &gn) {
	int carry = 0;
	GrandNombre result;
	uint64_t temp;

	for(int i = SIZE - 1; i >= 0; i--){
		temp = Tab[i]- gn.getDataIndex(i) - carry;
		result.set(i, temp);
		if(Tab[i] < gn.getDataIndex(i)) {
			carry = 1;
			if(result.getDataIndex(i) >= 0xFFFFFFFF00000000) {
				result.set(i, result.getDataIndex(i) - 0xFFFFFFFF00000000);	//removing negative overflow
			}
			else if(result.getDataIndex(i) == 0xFFFFFFFFFFFFFFFF){
				result.set(i, result.getDataIndex(i) - 0xFFFFFFFFFFFFFFFF);
			}
		}
		else if(Tab[i] == gn.getDataIndex(i) && carry == 1){
			carry = 1;
		}
		else {
			carry = 0;
		}
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

//division
GrandNombre GrandNombre::operator/(GrandNombre &gn) {
	GrandNombre result;
	uint64_t temp_res;

	for(int j = SIZE - 1; j >= SIZE/2; j--) {
		for(int i = SIZE - 1; i >= SIZE/2; i--) {
			if(gn.getDataIndex(j) != 0) {
				temp_res = Tab[i]/gn.getDataIndex(j);
				result.set(i + j - SIZE/2, result.getDataIndex(i + j - SIZE/2) + temp_res);
			}
		}
	}

	return result;
}

//modular addition
GrandNombre GrandNombre::mod_add(GrandNombre &gn, GrandNombre &N) {
	GrandNombre result, temp_res;

	temp_res = *this + gn;

	while(temp_res > N) {
		temp_res = temp_res - N;
	}

	result = temp_res;

	return result;
}

//modular substraction
GrandNombre GrandNombre::mod_sub(GrandNombre &gn, GrandNombre &N) {
	GrandNombre result, temp_res, gn_null;
	gn_null = GrandNombre();	//creating the big null number

	temp_res = *this - gn;

	while(gn_null > temp_res) {
		temp_res = temp_res + N;
	}

	result = temp_res;

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

	for(int i = 0; i < SIZE/2; i++) {

	}

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

	//bigInt1 = 0x1D4162A0563DF5E6E656FAD7AA77218A5FE79C116376CEE7813D220135BF721E21F2D554493F4C95F1D0A64339003A1987A33A4A5BD408C1CE6CFAF38FFB9BB01CE72E050DB7CFAC8DADA1D9A87859FAED805D165538DFCF6E06862C48FE78E6BC7E179DE9384E8B5E56B838BC2DD382E2D0DA301B7F92FDFF934ADBFDA179256
	//bigInt2 = 0x11CBF7B4F60E4CF37477A698D0A675CA32DDC3B68D4A0218C15A28E24A40268ADE5E5C44A46905D34F7E42FF3D17910CFD39248A4E42CAE87D1A37FFA9C5DBB1BE8D33DAE4B1B37A6E16A51EC0D2A19C7E5A8027450BCEC68B53184CBED59F26538C04C7A98E71513AEF4A6FBCBF2E482C68E6045BC7CC5AFB4FAB949C78AB79F

	//0x1D4162A0563DF5E6E656FAD7AA77218A5FE79C116376CEE7813D220135BF721E21F2D554493F4C95F1D0A64339003A1987A33A4A5BD408C1CE6CFAF38FFB9BB01CE72E050DB7CFAC8DADA1D9A87859FAED805D165538DFCF6E06862C48FE78E6BC7E179DE9384E8B5E56B838BC2DD382E2D0DA301B7F92FDFF934ADBF
	//0x11CBF7B4F60E4CF37477A698D0A675CA32DDC3B68D4A0218C15A28E24A40268ADE5E5C44A46905D34F7E42FF3D17910CFD39248A4E42CAE87D1A37FFA9C5DBB1BE8D33DAE4B1B37A6E16A51EC0D2A19C7E5A8027450BCEC68B53184CBED59F26538C04C7A98E71513AEF4A6FBCBF2E482C68E6045BC7CC5AFB4FAB949C78AB79F

	//0xFFEB3D5280EE827D
	//0x29AAC39AA8E75AD7

	uint64_t bigInt1[SIZE] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000FFEB3D52, 0x0000000080EE827D};
	uint64_t bigInt2[SIZE] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000000029AAC39A, 0x00000000A8E75AD7};

	GrandNombre gn1(bigInt1);
	GrandNombre gn2(bigInt2);
	GrandNombre gnRes, gnRes2, gnRes3;

	gnRes = gn1 + gn2;
	cout << "gn1 + gn2 = " << gnRes << endl;

	gnRes2 = gn1 - gn2;
	cout << "gn1 - gn2 = " << gnRes2 << endl;

	gnRes3 = gn1*gn2;
	cout << "gn1 * gn2 = " << gnRes3 << endl;

	return 0;
}
