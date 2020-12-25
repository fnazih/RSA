#include<iostream>
#include<math.h>
#include<cstdlib>
using namespace std;

long int choosePrimaryNumber();
bool isPrime(long int number);
long int gcd(long int e, long int phi);

long int choosePrimaryNumber()
{
	long int number = 0;

	while(!isPrime(number))
	{
		number = rand();
	}

	return number;
}

//This function returns true if the parameter is primary, and false otherwise.
bool isPrime(long int number) {
	int squareRoot = sqrt(number);	//To check if a number is primary, we can divide him by every number until his square root

	if(number ==0 || number == 1)
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







