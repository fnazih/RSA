#include<stdio.h>
#include<iostream>
#include "number.h"
using namespace std;



GrandNombre::GrandNombre() {
	for(int i = 0; i < SIZE; i++)
	{
		this->Tab[i] = 0;
	}
}

GrandNombre::GrandNombre(uint32_t bigInt[SIZE]) {

	for(int i = 0; i < SIZE; i++) {
		this->Tab[i] = bigInt[i];
	}
}

//addition
GrandNombre GrandNombre::operator+(const GrandNombre &gn) const {
	int carry = 0;
	GrandNombre result;

	for(int i = SIZE - 1; i >= 0; i--) {
		result.set(i, this->Tab[i] + gn.getDataIndex(i) + carry);
		if(this->Tab[i] + gn.getDataIndex(i) >= pow(2, 31)) {
			carry = 1;
		}
		else if(this->Tab[i] + gn.getDataIndex(i) == pow(2, 32) && carry == 1) {
			carry = 1;
		}
		else {
			carry = 0;
		}
	}

	return result;
}

GrandNombre GrandNombre::operator-(const GrandNombre &gn) const {
	int carry = 0;
	GrandNombre result;

	for(int i = 0; i < SIZE; i++) {
		result.set(i, Tab->[i] - gn.getDataIndex(i));
	}
	
	return result;
}

GrandNombre GrandNombre::operator*(const GrandNombre &gn) const {

}


friend ostream& GrandNombre::operator<<(ostream& str, const GrandNombre &gn) const {


	return str;
}


int main() {
	
	return 0;
}

