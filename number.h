#pragma once
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdint.h>
using namespace std;

#define SIZE 64		//for a 2048 bits number, we need 64 unsigned integers of 64 bits since we will multiply 32 bits number together
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
	friend ostream& operator<<(ostream& str, GrandNombre &gn) {
		for(int i = 0; i < SIZE; i++) {
			str << hex << uppercase << setfill('0') << gn.getDataIndex(i);
		}
		return str;
	}
};
