#pragma once
#include <iostream>
#include <math.h>
#include <stdint.h>
using namespace std;

#define SIZE 64		//for a 2048 bits number, we need 32 unsigned integers of 64 bits

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
	friend ostream& operator<<(ostream& str, const GrandNombre &gn) const;
};
