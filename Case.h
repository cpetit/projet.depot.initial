#pragma once
#include <string>
#include "Pion.h"
using namespace std;

class Case
{
	// Attributs
	private:
	string etat;		// Trois états: rouge, jaune ou vide.
	Pion pion;			// Le pion qui est éventuellement dans la case.

	// Méthodes
	public:
	Case(void);
	~Case(void);
	string getEtat(void);
	Pion getPion(void);
	void setPion(Pion cePion);
	void setVide(void);
	void info(void);
};

