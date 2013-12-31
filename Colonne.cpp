#include <iostream>
#include "Colonne.h"
#include "Case.h"
#include "Pion.h"

// Constructeur qui crée une colonne de numéro donné
// Elle est initialement vide.
// Le tableau de cases créé est formé de cases vides,
// via le constructeur de cases.

Colonne::Colonne(int ceNumero)
{
	this->numero=ceNumero;
	this->nbPion=0;
}

Colonne::Colonne(void)
{
	this->nbPion=0;
}
// Destructeur
Colonne::~Colonne(void)
{
}

// Getters
int Colonne::getNum(void)
{
	return this->numero;
}

int Colonne::getNbPion(void)
{
	return this->nbPion;
}


// Renvoie le pion se trouvant dans la case à hauteur h.
Pion Colonne::getContenuH(int h)
{
	return this->listeCase[h].getPion();
}

// Vrai si la colonne est pleine.
bool Colonne::isPleine(void)
{
	return(this->listeCase[HAUTEUR-1].getEtat()!="vide");
}

// Ajoute un pion au-dessus des autres et met à jour
// le nombre de pions dans la colonne.
void Colonne::ajoutPion(Pion cePion)
{
	if(!this->isPleine())
	{
		this->listeCase[nbPion].setPion(cePion);
		this->nbPion++;
	}
}

void Colonne::enlevePion(void)
{
	this->listeCase[nbPion].setVide();
	this->nbPion--;
}

void Colonne::info(void)
{
	cout<<"Je suis la colonne "<<this->getNum()<<" : "<<endl;
	cout<<"Je contiens "<<this->nbPion<<" pion(s) : "<<endl;
	for(int i=HAUTEUR-1;i>=0;i--)
	{
		if (this->listeCase[i].getEtat()=="vide")
			cout<<"Case "<<i+1<<" : "<<this->listeCase[i].getEtat()<<endl;
		else
			cout<<"Case "<<i+1<<" : "<<this->listeCase[i].getEtat()<<" (pion numero "<<this->listeCase[i].getPion().getNum()<<")"<<endl;
	}
}