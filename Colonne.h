#pragma once
#define HAUTEUR 6
#define LARGEUR 7
#include <string>
#include <vector>
#include "Pion.h"
#include "Case.h"
using namespace std;

class Colonne
{
	// Attributs
	private:
	int numero;					// Numéro de colonne de 0 à largeur-1.
	int nbPion;					// Nombre de pions présents dans la colonne.
	Case listeCase[HAUTEUR];	// La colonne est un tableau de cases.

	// Méthodes
	public:
	Colonne(void);
	Colonne(int);
	~Colonne(void);
	int getNum(void);
	int getNbPion(void);
	Pion getContenuH(int);		// Renvoie le pion de la case à hauteur h.
	bool isPleine(void);		// Ajout d'un pion au-dessus des autres.
	void ajoutPion(Pion);
	void enlevePion(void);
	void info(void);
};

