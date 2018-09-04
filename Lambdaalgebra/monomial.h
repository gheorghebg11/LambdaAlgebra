#pragma once

#include "mathtools.h"
#include <vector>

using namespace std;







class monomial // This is a product of (tau) and Xi_a's, always denote such a product by X
{

	public: // TODO : All is public for now...
		// Constructors, Destructors
		monomial();
		monomial(vector<int> A); // core = A
		monomial(vector<int> A, int t); // core = A, tau = t
		~monomial();

		// Attributes
		int tau;
		int coadm; // it is -1 if it is coadmissible, 0 if we don't know, 1 if not coadmissible
		vector<int> core;

		// Methods to change attributes
		void settau(int value)  { tau = value; }
		void setentry(unsigned int entry, int value) { core.at(entry) = value; }
		void clearcore() { core.clear(); }
		void addentry(unsigned int value) { core.push_back(value); } 
		void insertentry(unsigned int entry, unsigned int value) { core.insert(core.begin() + entry, value); }
		void setcoadm(int value) { coadm = value; }
		void setvalues(vector<int> A) { core = A; }

		// Methods to get attributes
		int getcoadm() const { return coadm; }
		int gettau() const { return tau; }
		int getlength() const { return core.size(); }
		int getentry(unsigned int entry) const;

		// Other Methods using this class
		void printmonomial();  // print to console the monomial (with the Tau in front)
		int testcoadmissible(); // tests if the monomial is coadmissible, returns -1 if it is, returns the entry where it's not if it's not
		monomial multby(monomial X); // multiply by the monomial X on the right and change the monomial Y we started with by YX. Also returns the product

};

