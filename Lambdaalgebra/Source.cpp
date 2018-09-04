#include <iostream>
#include <vector>

#include "monomial.h"
#include "mathtools.h"
#include "term.h"

using namespace std;




/* TODO :
1) Change public, private, etc
2) Fix the function binom, for big numbers to work, and make it faster too. (also make it faster mod 2)
3) In Coaddmissible spot pass the ADDRESS of the monomial
4) Changefirstnonadm does more than just change 1 spot, I think it goes from right to left and changes all that it sees wrong, one turn at a time. My goal was to set this function to just change one and call it a ton of times in a loop to change the whole thing.
*/



int main()
{

	cout << "Hello World !" << endl << endl;

	//monomial X  ({8,1,8,1 });
	monomial X({ 3,5,7 });

	monomial Y ({ 3, 1 });


	X.printmonomial();
	cout << endl;
	

	term M(X);
	term N(Y);
	
	term L;


	L = term::differential(X);
	L.printterm();
	
	cout << endl << "This term now should be 0 :" <<endl;

	L = L.differential();
	L.printterm();
	cout << endl << endl;
	L.changeincoadmissible();
	L.printterm();
	cout << endl << endl;
	L.changeincoadmissible();
	L.printterm();
	







	/*
	term N(Y); // Need to creat Y non empty because we are below

	int i, j, k, l, m;
	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			for (k = 1; k < 10; k++)
			{
				for (l = 1; l < 10; l++)
				{
					for (m = 1; m < 10; m++)
					{
						Y.setvalues({ i, j, k, l, m });
						N.settobe(Y);
						N.printinfileincoadmform();
					}
				}
			}
		}
	}
	*/



	cout << endl << endl << endl;
	system("pause");
	return 0;
}






/////////////////////////////// FUNCTIONS THAT ARE IN SOURCE.CPP

