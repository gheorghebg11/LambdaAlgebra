#include "term.h"

#include <fstream>

term::term()
{
}

term::term(monomial X)
{
	expression.push_back(X);
}


term::~term()
{
}

void term::settobe(monomial X)
{
	expression.clear();
	expression.push_back(X);
}

void term::setentry(int monomialnbr, int monomialentry, int value)
{
	expression.at(monomialnbr).setentry(monomialentry, value);
}

void term::insertentry(int monomialnbr, int monomialentry, int value)
{
	expression.at(monomialnbr).insertentry(monomialentry, value);
}

void term::addentry(int monomialnbr, int value)
{
	expression.at(monomialnbr).addentry(value);
}


void term::changefirstnonadm()
{
	unsigned int i = 0;

	while (i < expression.size())
	{
		int j = -1;
		j = expression.at(i).testcoadmissible();
		if (j == -1)
		{
			expression.at(i).setcoadm(-1);
			i++;
		}
		else
		{
			
			term R = coadmissiblespot(expression.at(i), j);

			if (R.getmonomial(0).getlength() == 1) // that is, if the relation we got is just one 0
			{
				expression.erase(expression.begin() + i);
				if (expression.size() == 0)
				{
					monomial x;
					x.addentry(0);
					expression.push_back(x);
				}
			}
			else
			{
				int n = R.getnumbermonomials();
				monomial X = expression.at(i);

				expression.at(i).settau(expression.at(i).gettau() + R.getmonomial(0).gettau());
				expression.at(i).setentry(j, R.getmonomial(0).getentry(0));
				expression.at(i).setentry(j + 1, R.getmonomial(0).getentry(1));

				int k = 1;
				while (k < n)
				{
					X.setentry(j, R.getmonomial(k).getentry(0));
					X.setentry(j + 1, R.getmonomial(k).getentry(1));
					expression.insert(expression.begin() + i + k, X);
					expression.at(i + k).settau(expression.at(i + k).gettau() + R.getmonomial(k).gettau());
					k++;
				}
			}
		}
	}
}

void term::changeincoadmissible()
{
	unsigned int i = 0;
	while (i < expression.size())
	{
		if (expression.at(i).getcoadm() == -1)
		{
			i++;
		}
		else
		{
			changefirstnonadm();
		}
	}
}


void term::order()
{
	term M;
	int i = 0, j = 0;
	int n = expression.size();
	for (i = 0; i < n; i++)
	{

	}

}

term term::Relation(unsigned int a, unsigned int b)
{
	term M;
	unsigned int c;

	if (a >= 2 * b)
	{
		c = 2 * b;
		while (c <= (int)2 * (a + b) / 3)
		{
			if (mathtools::binom(a - c - 1, c - 2 * b) % 2 == 1)
			{
				monomial X;
				X.addentry(c);
				X.addentry(a + b - c);
				if (a % 2 == 1 && b % 2 == 1 && c % 2 == 0)
					X.settau(X.gettau() + 1);
				M.addmonomial(X);
			}
			c++;
		}
	}
	monomial x;      // If the relation that pops out is 0, we add a 0 to M so that it's not empty and gives no error.
	x.addentry(0);
	if (M.getnumbermonomials() == 0)
		M.addmonomial(x);
	return M;
}

void term::printterm()
{
	unsigned int i;
	unsigned int n = expression.size();

	if ( n != 0)
	{
		for (i = 0; i < n; i++)
		{
			expression.at(i).printmonomial();
			if (i != n - 1)
				cout << " + ";
		}
	}
	else
	{
		cout << "0";
	}
}

term term::coadmissiblespot(monomial X, unsigned int spot)
{
	term R = Relation(X.getentry(spot), X.getentry(spot + 1));

	if (R.getmonomial(0).getlength() == 1) // that is, if the relation that pops out is just 0
	{
		monomial x;
		x.addentry(0);
		term T(x);
		return T;
	}
	else
	{
		return R;
	}
}

void term::printinfile()
{
	ofstream outFile;
	outFile.open("Relations.txt", fstream::app);

	unsigned int i;
	if (expression.size() != 0)
	{
		for (i = 0; i < expression.size(); i++)
		{
			monomial X;
			X = expression.at(i);
			int j;
			if (X.getentry(0) == 0) // If X is just 0, print 0, no Xi's or anything.
				outFile << "0";
			else
			{
				if (X.gettau() != 0)
					outFile << X.gettau() << "TAU*";
				for (j = 0; j != X.getlength(); ++j)
				{
					//if (j == 0)
						outFile << "e" << X.getentry(j);
					//else
						//outFile << "*e" << X.getentry(j);
				}
			}

			if (i != expression.size() - 1)
				outFile << " + ";
		}
	}

	outFile.close();
}


void term::printinfileincoadmform()
{
	ofstream outFile;


	outFile.open("Relations.txt", fstream::app);
	outFile << "Coadm form of ";
	outFile.close();

	printinfile(); // now we type the term M in file

	outFile.open("Relations.txt", fstream::app);
	outFile << " is ";
	outFile.close();

	changeincoadmissible(); // now we replace M in coadm form
	printinfile(); // and now we print M

	outFile.open("Relations.txt", fstream::app); // just for the endl
	outFile << endl;
	outFile.close();
}

term term::multby(term M)
{
	term Z;

	int i = 0, j=0;
	for (i = 0; i < expression.size(); i++)
	{
		for (j = 0; j < M.getnumbermonomials(); j++)
		{
			Z.addmonomial(expression.at(i).multby(M.getmonomial(j)));
		}
	}
	return Z;
}

void term::addterm(term M)
{
	int i = 0;
	for (i = 0; i < M.getnumbermonomials(); i++)
	{
		expression.push_back(M.getmonomial(i));
	}
}

term term::differential(unsigned int a, unsigned int tau)
{
	term M;
	monomial R({ 0 });
	R.settau(tau);

	unsigned int c = 1;
	for (c = 1; c <= ceil((a - 1)/2); c++)
	{
		if (mathtools::binom(a - c - 1, c) % 2 == 1)
		{
			R.clearcore();
			R.addentry(c);
			R.addentry(a - c);
			M.addmonomial(R);
		}
	}

	if (M.getnumbermonomials() == 0)
	{
		R.setcoadm(0);
		M.addmonomial(R);
	}

	return M;
}



term term::differential(monomial X)
{
	term M;
	term R; // where we temporary store the diff on Xi_a, where Xi_a's are the Xi_'s in X (R is a term, not a monomial!)
	int i = 0, j=0, k=0;


	for (i = 0; i < X.getlength(); i++) //we use the Leibniz rule where i is the position where we take the differential
	{
		R = term::differential(X.getentry(i),X.gettau());
		if (R.getmonomial(0).getentry(0) != 0)
		{
			for (j = 0; j < R.getnumbermonomials(); j++) //we iterate on the number of monomials that R has and we'll change all of them
			{
				for (k = 0; k < i; k++) //we first put the terms coming before position i, in front of R
				{
					R.insertentry(j, k, X.getentry(k));
					//R.getmonomial(j).setentry(k, X.getentry(k));
				}
				for (k = i + 1; k < X.getlength(); k++)
				{
					R.addentry(j, X.getentry(k));
					//R.getmonomial(j).addentry(X.getentry(k));
				}
			}
			M.addterm(R);
		}

	}

	return M;
}

term term::differential()
{
	int i = 0;
	term M;

	for (i = 0; i < expression.size(); i++)
	{
		M.addterm(differential(expression.at(i)));
	}
	return M;
}