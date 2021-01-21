#pragma once
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <ctime>
using namespace std;

#define SIZE 32		//for a 2048 bits number, we need 64 unsigned integers of 64 bits since we will multiply 32 bits number together
#define BITS sizeof(uint64_t)

class GrandNombre {
private:
	uint64_t Tab[SIZE];
public:
	GrandNombre();
	GrandNombre(uint64_t bigInt[SIZE]);
	uint64_t getDataIndex(int i) { return Tab[i]; }
	void set(int i, uint64_t data) { this->Tab[i] = data; }
	GrandNombre operator+(GrandNombre &gn);
	GrandNombre operator-(GrandNombre &gn);
	GrandNombre operator*(GrandNombre &gn);
	GrandNombre operator/(GrandNombre &gn);
	friend ostream& operator<<(ostream& str, GrandNombre &gn) {
		for(int i = 0; i < SIZE; i++) {
			str << hex << uppercase << setfill('0') << gn.getDataIndex(i);
		}
		return str;
	}
	bool operator>(GrandNombre &gn) {

		for(int i = 0; i < SIZE; i++) {
			if(Tab[i] > gn.getDataIndex(i)) {
				if(i == 0) return true;
				else {
					int count = 0;
					for(int j = 0; j < i; j++) {
						if(Tab[j] == 0) count+= 1;
					}
					if(count == i) return true;	//if Tab[i] is first non-null bit64, it is the biggest
				}
			}
		}

		return false;
	}
	bool operator==(GrandNombre &gn) {
		int equal = 0;

		for(int i = 0; i < SIZE; i++) {
			if(Tab[i] == gn.getDataIndex(i)) {
				equal++;
			}
		}

		if(equal == SIZE) {
			return true;
		}
		else {
			return false;
		}
	}
	GrandNombre mod_add(GrandNombre &gn, GrandNombre &N);
	GrandNombre mod_sub(GrandNombre &gn, GrandNombre &N);
	GrandNombre montgomery(GrandNombre &gn, GrandNombre &N, GrandNombre &V, GrandNombre &R);
};

GrandNombre transform_phi(GrandNombre &gn, GrandNombre &N, GrandNombre &R);
//uint64_t r[SIZE] = { 0x0000000100000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//const GrandNombre R(r);
