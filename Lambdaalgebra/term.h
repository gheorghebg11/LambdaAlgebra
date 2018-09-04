#pragma once

#include "monomial.h"


using namespace std;


class term
{
public:

	// Constructors, Destructors
	term();
	term(monomial X);
	~term();

	// Attributes
	vector<monomial> expression;

	// Methods to change attributes
	void addmonomial(monomial X) { expression.push_back(X); } 
	void settobe(monomial X);
	void setentry(int monomialnbr, int monomialentry, int value); // in the monomial nbr given, at the place entry given, set the given entry (i.e., write on it, not insert)
	void insertentry(int monomialnbr, int monomialentry, int value); // in the monomial nbr given, at the place entry given, insert the given entry
	void addentry(int monomialnbr, int value); // in the monomial nbr given, add the entry value at the end
	void changefirstnonadm();
	void changeincoadmissible();
	void order(); // order lexicographically
	void modtwo(); // cancel terms that appear twice, i.e., the coefficients are mod 2 now


	// Methods to get attributes
	int getnumbermonomials() { return expression.size(); } 
	monomial getmonomial(int i) { return expression.at(i); }

	// Other Methods using this class
	static term Relation(unsigned int a, unsigned int b); // Given a >= 2b, returns the coadmissible formula for Xi_a*Xi_b.
	void printterm();
	static term coadmissiblespot(monomial X, unsigned int spot); // Returns a term that fixes the coadmissibility at tne indicated spot
	void printinfile();
	void printinfileincoadmform();
	term multby(term M); // if you call it as N.multby(M), then it returns the product N*M
	void addterm(term M); // add the term M
	static term differential(unsigned int a, unsigned int tau); // returns the differential on T^{tau} * Xi_a, where T is the motivic tau
	static term differential(monomial X);
	term differential();
	

};

