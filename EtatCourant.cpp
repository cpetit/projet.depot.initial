#include "EtatCourant.h"
#include <iostream>

// Constructeur.
EtatCourant::EtatCourant(void)
{
	this->gagne=false;
	// Les colonnes sont numérotées à la création.
	for(int i=0;i<LARGEUR;i++) this->listeCol[i]=Colonne(i);
}

// Destructeur.
EtatCourant::~EtatCourant(void)
{

}

// Getters et setters.
Colonne EtatCourant::getCol(int l)
{
	return this->listeCol[l];
}

// Teste si la partie est gagnée.
bool EtatCourant::isGagne(void)
{
	return false;
}

// Joue un pion à la colonne l.
// Si la colonne est pleine, rien ne se passe.
void EtatCourant::jouer(Pion pi,int l)
{
	if (this->listeCol[l].isPleine()) cout<<"Coup impossible, colonne pleine."<<endl;
	else
	{
		this->listeCol[l].ajoutPion(pi);
	}
}

void EtatCourant::enleve(int l)
{
	this->listeCol[l].enlevePion();
}