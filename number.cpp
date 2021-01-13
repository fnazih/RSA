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
	uint64_t temp_res;
	int carry = 0;
	GrandNombre result;

	for(int i = SIZE - 1; i >= 0; i--) {
		temp_res = Tab[i] + gn.getDataIndex(i) + carry;
		result.set(i, temp_res);

		if((Tab[i]>>1) + (gn.getDataIndex(i)>>1) >= 0x8000000000000000) {	//if MSB of potential result on 9 bits is a 1
			carry = 1;
		}

		else if((Tab[i]>>1) + (gn.getDataIndex(i)>>1) == 0xFFFFFFFFFFFFFFFF) {
			if(Tab[i]<<(SIZE - 1) == 0x8000000000000000 && gn.getDataIndex(i) == 0x8000000000000000) {	//if overflow because both MSBs are set (1)
				carry = 1;
			}
		}

		else if(Tab[i] + gn.getDataIndex(i) == 0xFFFFFFFFFFFFFFFF && carry == 1) {	//if overflow comes from the carry
					carry = 1;
		}

		else {	//every other situation
			carry = 0;
		}
	}

	return result;
}

//soustraction
GrandNombre GrandNombre::operator-(GrandNombre &gn) {
	int carry = 0;
	GrandNombre result;

	for(int i = SIZE - 1; i >= 0; i--){
		result.set(i, Tab[i] - gn.getDataIndex(i) - carry);

		if(Tab[i] < gn.getDataIndex(i)) {	//if result is negative, we keep a carry
			carry = 1;
		}
		else if(Tab[i] == gn.getDataIndex(i) && carry == 1) { //if result is null, but the carry was set, keep it set
			carry = 1;
		}
		else { //every other case
			carry = 0;
		}
	}

	return result;
}

//multiplication
GrandNombre GrandNombre::operator*(GrandNombre &gn) {
	int carry = 0;
	GrandNombre result;

	for(int i = SIZE - 1; i >= 0; i--) {
		//result
	}

	return result;
}


//main
int main() {

	uint64_t bigInt1[SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0000000000000001, 0, 0, 0x0000000006030001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint64_t bigInt2[SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x000000000000000F, 0, 0x0000000000000001, 0x000000A000600004, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	GrandNombre gn1(bigInt1);
	GrandNombre gn2(bigInt2);
	GrandNombre gnRes, gnRes2;

	gnRes = gn1 + gn2;
	cout << "gn1 + gn2 = " << gnRes << endl;

	gnRes2 = gn2 - gn1;
	cout << "gn2 - gn1 = " << gnRes2 << endl;

	return 0;
}
