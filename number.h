#pragma once
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdint.h>
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
	friend ostream& operator<<(ostream& str, GrandNombre &gn) {
		for(int i = 0; i < SIZE; i++) {
			str << hex << uppercase << setfill('0') << gn.getDataIndex(i);
		}
		return str;
	}
	bool operator>(GrandNombre &gn) {
		uint64_t temp;
		bool bigger = false;

		for(int i = 0; i < SIZE; i++) {
			if(Tab[i] > gn.getDataIndex(i)) {
				bigger = true;
				return bigger;
			}
		}

		return bigger;
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
	GrandNombre montgomery(GrandNombre &gn, GrandNombre &N);
};
