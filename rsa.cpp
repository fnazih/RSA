#include<iostream>
#include<math.h>
#include<cstdlib>
#include "number.h"
using namespace std;

GrandNombre choosePrimaryNumber();
bool isPrime(GrandNombre number);
GrandNombre gcd(GrandNombre e, GrandNombre phi);

GrandNombre choosePrimaryNumber()
{
	GrandNombre number = GrandNombre();

	while(!isPrime(number))
	{
		number = rand();
	}

	return number;
}

//This function returns true if the parameter is primary, and false otherwise.
bool isPrime(GrandNombre number) {
	int squareRoot = sqrt(number);	//To check if a number is primary, we can divide him by every number until his square root
	GrandNombre gn_null, gn1;
	gn_null = GrandNombre();
	gn1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0000000000000001};

	if(number == gn_null || number == gn1)
	{
		return false;
	}
	for(long int i = 2; i <= squareRoot; i++)
	{
		if(number%i == 0)
		{
			return false;
		}
	}

	return true;
}

//This function returns the greatest common divider between the two parameters
long int gcd(long int e, long int phi)
{

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
