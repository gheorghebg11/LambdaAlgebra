#include "monomial.h"

#include <iostream>




using namespace std;

monomial::monomial(vector<int> A) 
{
	core = A;
	tau = 0;
	coadm = 0;
}

monomial::monomial(vector<int> A, int t)
{
	core = A;
	tau = t;
	coadm = 0;
}

monomial::monomial()
{
}

monomial::~monomial() {}

int monomial::getentry(unsigned int entry) const
{
	if (core.size() > entry)
		return core.at(entry);
	else
		cout << "ERROR : Tried to get an entry (getentry) that doesn't exist.";
}



void monomial::printmonomial()
{
	int unsigned i;
	if (core.size() == 0) // If X is just 0, print 0, no Xi's or anything.
		cout << "0";
	else
	{
		if (tau != 0)
			cout << tau << "TAU*";

		for (i = 0; i != core.size(); i++)
			cout << "e" << core.at(i);
	}
}

int monomial::testcoadmissible()
{
	if (coadm == -1)
	{
		return -1;
	}
	else
	{
		int i = 0;
		int n = core.size();
		while (i < n-1)
		{
			if (core.at(n - 2 - i) >= 2 * core.at(n - 1 - i))
				return (n - 2 - i);
			i++;
		}
		coadm = -1;
		return -1;
	}
}

monomial monomial::multby(monomial X)
{
	coadm = 0;
	tau += X.gettau();



	unsigned int i = 0;
	for (i = 0; i < X.getlength(); i++)
		core.push_back(X.getentry(i));

	monomial Y(core,tau);
	return Y;
}