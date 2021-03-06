#include<iostream>
#include<math.h>
#include<cstdlib>
#include "number.h"
using namespace std;

bool isPrime(GrandNombre number);
GrandNombre gcd(GrandNombre e, GrandNombre phi);
void RSA(GrandNombre p, GrandNombre q);

//This function returns true if the parameter is primary, and false otherwise.
bool isPrime(GrandNombre number) {
	//int squareRoot = sqrt(SIZE);	//To check if a number is primary, we can divide him by every number until his square root
	GrandNombre gn_null, gn1;
	gn_null = GrandNombre();
	gn1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0000000000000001};

	if(number == gn_null || number == gn1)
	{
		return false;
	}
	for(int i = 2; i <= SIZE; i++)
	{
		if(number/gn1 == 0)
		{
			return false;
		}
	}

	return true;
}

//This function returns the greatest common divider between the two parameters
GrandNombre gcd(GrandNombre e, GrandNombre phi)
{
	GrandNombre temp;

	while (1) {
		temp = e.mod_sub(phi, phi);
	}
}


void RSA(GrandNombre p, GrandNombre q) {
	GrandNombre N, phi_N, p_1, q_1;
	GrandNombre un({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0000000000000001});

	N = p*q;

	p_1 = p - 1;
	q_1 = q - 1;

	phi_N = p_1*q_1;
}


int main()
{
	long int p, q;
	cout << "Choose p" << endl;
	cin << p;
	if(!isPrime(p))
	{
		cout << "Le nombre entre n'est pas premier" << endl;
		return 1;
	}

	cout << "Choose q" << endl;
	cin << q;
	if(!isPrime(q))
	{
		cout << "Le nombre entre n'est pas premier" << endl;
	}

	return 0;
}
