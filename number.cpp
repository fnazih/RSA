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
	uint64_t temp_res, res, temp, carry, temp_carry;

	carry = 0;

	for(int j = SIZE - 1; j > 0; j--) {
		for(int i = SIZE - 1; i > 0; i--) {
			temp_res = Tab[i]*gn.getDataIndex(j) + carry;
			carry = temp_res>>32;
			temp_carry = carry<<32;
			res = result.getDataIndex(i + j - (SIZE - 1)) + temp_res - temp_carry;
			cout << "res : " << res << endl;
			result.set(i + j - (SIZE - 1), res);
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
	GrandNombre result, temp_res, temp;

	temp_res = *this + gn;

	while(temp_res > N) {
		temp = temp_res;
		temp_res = temp - N;
	}

	result = temp_res;

	return result;
}

//modular substraction
GrandNombre GrandNombre::mod_sub(GrandNombre &gn, GrandNombre &N) {
	GrandNombre result, temp_res, gn_null;
	gn_null = GrandNombre();	//creating the big null number

	temp_res = *this - gn;

	while (temp_res > N) {
		temp_res = temp_res - N;
	}
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
	cout << "s = " << hex << s << endl;

	t = s*V;
	cout << "t = " << hex << t << endl;

	while (t > R) {
		t = t - R;
	}

	temp = t*N;
	m = s + temp;

	cout << "m = " << hex << m << endl;

	for(int i = 0; i < SIZE/2; i++) { //u = m/R ==> u >> 1025 bits
		Tab[i + SIZE/2] = Tab[i]/2;
		Tab[i] = 0;
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

	//Modeles de Tab
	//uint64_t bigInt1[SIZE] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
	//uint64_t bigInt2[SIZE] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
	uint64_t bigIntR[SIZE] = { 0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
	//uint64_t bigIntN[SIZE] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
	GrandNombre gnRes1, gnRes2, gnRes3, gnResMod, R(bigIntR), V;
	float temps_initial, temps_final;

	//Simple example
	//uint64_t bigInt1[SIZE] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000FFFFFFFF};
	//uint64_t bigInt2[SIZE] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000FFFFFFFF};
	//uint64_t bigIntN[SIZE] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000000FFFFFFF};

	//Complex example
	//bigInt1 = 0x1D4162A0563DF5E6E656FAD7AA77218A5FE79C116376CEE7813D220135BF721E21F2D554493F4C95F1D0A64339003A1987A33A4A5BD408C1CE6CFAF38FFB9BB01CE72E050DB7CFAC8DADA1D9A87859FAED805D165538DFCF6E06862C48FE78E6BC7E179DE9384E8B5E56B838BC2DD382E2D0DA301B7F92FDFF934ADBFDA179256
	//bigInt2 = 0x1CBF7B4F60E4CF37477A698D0A675CA32DDC3B68D4A0218C15A28E24A40268ADE5E5C44A46905D34F7E42FF3D17910CFD39248A4E42CAE87D1A37FFA9C5DBB1BE8D33DAE4B1B37A6E16A51EC0D2A19C7E5A8027450BCEC68B53184CBED59F26538C04C7A98E71513AEF4A6FBCBF2E482C68E6045BC7CC5AFB4FAB949C78AB79F
	//bigIntN = 0x18895842B2FB213C95A89BDA77DEB67AC797F2B206E478F1E2A0A0F8E13D2B458668E0771114502FE3C0236E17CB7CBFC296A8B4BF9D3152951C54F77F1D16DBCE4A52B26A6989BF5FF73B2637BC70EA143086CAA1D6338E9FB5B00108B19F843289A97F6475F3A89F4EF2338E5ED2EA233EEECDA2B445ECBC361BC5B6DB4E193

	//bigIntN = 0x18895842B2FB213C95A89BDA77DEB67AC797F2B206E478F1E2A0A0F8E13D2B458668E0771114502FE3C0236E17CB7CBFC296A8B4BF9D3152951C54F77F1D16DBCE4A52B26A6989BF5FF73B2637BC70EA143086CAA1D6338E9FB5B00108B19F843289A97F6475F3A89F4EF2338E5ED2EA233EEECDA2B445ECBC361BC5B6DB4E193

	uint64_t bigInt1[SIZE] = { 0x000000001D4162A05, 0x0000000063DF5E6E, 0x00000000656FAD7A, 0x00000000A77218A5, 0x00000000FE79C116, 0x00000000376CEE78, 0x0000000013D22013, 0x000000005BF721E2, 0x000000001F2D5544, 0x0000000093F4C95F, 0x000000001D0A6433, 0x000000009003A198, 0x000000007A33A4A5, 0x00000000BD408C1C, 0x00000000E6CFAF38, 0x00000000FFB9BB01, 0x00000000CE72E050, 0x00000000DB7CFAC8, 0x00000000DADA1D9A, 0x0000000087859FAE, 0x00000000D805D165, 0x00000000538DFCF6, 0x00000000E06862C4, 0x000000008FE78E6B,  0x00000000C7E179DE, 0x000000009384E8B5, 0x00000000E56B838B, 0x00000000C2DD382E, 0x000000002D0DA301, 0x00000000B7F92FDF, 0x00000000F934ADBF, 0x00000000DA179256};

	uint64_t bigInt2[SIZE] = { 0x000000001CBF7B4F, 0x0000000060E4CF37, 0x00000000477A698D, 0x000000000A675CA3, 0x000000002DDC3B68, 0x00000000D4A0218C, 0x0000000015A28E24, 0x00000000A40268AD, 0x00000000E5E5C44A, 0x0000000046905D34, 0x00000000F7E42FF3, 0x00000000D17910CF, 0x00000000D39248A4, 0x00000000E42CAE87, 0x00000000D1A37FFA, 0x000000009C5DBB1B, 0x00000000E8D33DAE, 0x000000004B1B37A6, 0x00000000E16A51EC, 0x000000000D2A19C7, 0x00000000E5A80274, 0x0000000050BCEC68, 0x00000000B53184CB, 0x00000000ED59F265, 0x0000000038C04C7A, 0x0000000098E71513, 0x00000000AEF4A6FB, 0x00000000CBF2E482, 0x00000000C68E6045, 0x00000000BC7CC5AF, 0x00000000B4FAB949, 0x00000000C78AB79F};

	//uint64_t bigIntN[SIZE] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000000FFFFFFF};

	GrandNombre gn1(bigInt1);
	GrandNombre gn2(bigInt2);
	GrandNombre N;

	/*
	cout << "gn1 = " << gn1 << endl;
	cout << "gn2 = " << gn2 << endl;
	cout << "N = " << N << endl;

	//check GrandNombre addition
	temps_initial = clock();
	gnRes1 = gn1 + gn2;
	temps_final = clock();
	cout << "gn1 + gn2 = " << gnRes1 << " apres " << dec << temps_final - temps_initial << "ms"<< endl;

	//check GrandNombre substraction
	temps_initial = clock();
	gnRes2 = gn1 - gn2;
	temps_final = clock();
	cout << "gn1 - gn2 = " << gnRes2 << " apres " << dec << temps_final - temps_initial << "ms" << endl;
*/


	//check GrandNombre multiplication : a revoir
	/*
	uint32_t random;
	GrandNombre gn1CalculT, gn2CalculT, gnResCalculT;

	for(int i = 0; i < SIZE; i++) {
		random = rand();
		gn1CalculT.set(i, random);
	}

	for(int j = 0;j < SIZE; j++) {
		random = rand();
		gn2CalculT.set(j, random);
	}

	cout << "multiplication gn" << endl;
	temps_initial = clock();
	gnResCalculT = gn1CalculT*gn2CalculT;
	temps_final = clock();
	cout << "gn1 * gn2 = " << gnResCalculT << " apres " << dec << temps_final - temps_initial << "ms" << endl;
	*/


	/*
	//check GrandNombre division : failed
	gnRes = gn1/gn2;
	cout << "gn1/gn2 = " << gnRes << endl;
	*/

	/*
	//check GrandNombre modular addition
	temps_initial = float(clock())/CLOCKS_PER_SEC;
	gnResMod = gn1.mod_add(gn2, N);
	temps_final = float(clock())/CLOCKS_PER_SEC;
	cout << "(gn1 + gn2) mod N = " << gnResMod << " en " << temps_final - temps_initial << "s" << endl;
	*/

	/*
	//check GrandNombre modular substraction
	temps_initial = float(clock())/CLOCKS_PER_SEC;
	gnResMod = gn1.mod_sub(gn2, N);
	temps_final = float(clock())/CLOCKS_PER_SEC;
	cout << "(gn1 - gn2) mod N = " << gnResMod << " en " << temps_final - temps_initial << "s" << endl;
	*/

	//check montgomery multiplication
	//gnResMod = gn1.montgomery(gn2);
	//cout << "montgomery multiplication of gn1 and gn2 = " << gnResMod << endl;

	//check GrandNombre comparison
	/*
	if(gn1 > gn2) {
		cout << "true"<< endl;
	}
	else {
		cout << "false" << endl;
	}
	*/

	//Calculating mean execution time (change operation and name in "cout")
	uint32_t random;
	GrandNombre gn1CalculT, gn2CalculT, gnResCalculT, NCalculT;
	int temps[100], start, stop, count;

	for(int k = 0; k < 100; k++) {
		for(int i = 1; i < SIZE; i++) {
			random = rand();
			gn1CalculT.set(i, random);
		}

		for(int j = 1; j < SIZE; j++) {
			random = rand();
			gn2CalculT.set(j, random);
		}

		for(int l = 1; l < SIZE; l++) {
			random = rand();
			NCalculT.set(l, random);
		}

		start	= clock();
		gnResCalculT = gn1CalculT + gn2CalculT;
		stop = clock();
		temps[k] = stop - start;
	}

	for(int l = 0; l < 100; l++) {
		count += temps[l];
	}

	float mean;
	mean = 1.0*count/100;

	cout << "Mean time of big number addition : " << mean << "ms" << endl;


	return 0;
}
