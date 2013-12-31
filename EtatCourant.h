#pragma once
#include <string>
#include <vector>
#include "Pion.h"
#include "Case.h"
#include "Colonne.h"
using namespace std;

class EtatCourant
{
	
	// Attributs
	private:
	Colonne listeCol[LARGEUR];	// Tableau des colonnes qui composent la grille du jeu.
	bool gagne;					// Vrai lorsque la partie est gagnée (et s'arrête).

	// Méthodes
	public:
	EtatCourant(void);
	~EtatCourant(void);
	Colonne getCol(int);
	bool isGagne(void);
	void jouer(Pion,int);		// Tente de jouer un pion dans une colonne.
	void enleve(int);
};

