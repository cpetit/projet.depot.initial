// Version du 29/01/14

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
	int numero;					// Numéro de colonne de 0 à LARGEUR-1.
	int nbPion;					// Nombre de pions présents dans la colonne.
	Case listeCase[HAUTEUR];	// La colonne est un tableau (en dur) de cases.

	// Méthodes
	public:
	// Constructeurs et destructeurs.
	Colonne(void);
	Colonne(int);
	~Colonne(void);
	// Getters et setters.
	int getNum(void);
	int getNbPion(void);

	// Autres méthodes
	Pion getContenuH(int);		// Renvoie le pion de la case à hauteur h.
	bool isPleine(void);		// Vrai quand la colonne est pleine.
	void ajoutPion(Pion);		// Ajoute un pion si la colonne n'est pas pleine.
	void enlevePion(void);		// Supprime un pion (en cas d'annulation de coup).
	void info(void);
};

