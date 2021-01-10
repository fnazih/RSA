#pragma once
#include <iostream>
#include <math.h>
#include <stdint.h>
using namespace std;

#define SIZE 64		//for a 2048 bits number, we need 64 unsigned integers of 32 bits since we are on a VM (x32)

class GrandNombre {
private:
	uint32_t Tab[SIZE];
public:
	GrandNombre();
	GrandNombre(uint32_t bigInt[SIZE]);
	uint32_t getDataIndex(int i) { return Tab[i]; }
	void set(int i, uint32_t data) { this->Tab[i] = data; }
	GrandNombre operator+(const GrandNombre &gn) const;
	GrandNombre operator-(const GrandNombre &gn) const;
	GrandNombre operator*(const GrandNombre &gn) const;
	friend ostream& operator<<(ostream& str, GrandNombre gn) {
		for(int i = 0; i < SIZE; i++) {
			str << hex << gn.getDataIndex(i);
		}

		return str;
	}
};
