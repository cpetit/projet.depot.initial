#include "Pion.h"
#include <iostream>
#include <string>
int Pion::compteur=0;
int Pion::nbPionJaune=0;
int Pion::nbPionRouge=0;

// Constructeurs
Pion::Pion()
{
	//cout<<"Constructeur defaut.\n";
}

// Le seul constructeur dont nous aurons besoin affectera obligatoirement une
// couleur à chaque pion en début de partie.
Pion::Pion(string cetteCouleur)
{
	compteur++;
	if (cetteCouleur=="rouge") this->nbPionRouge++;
	else this->nbPionJaune++;
	this->num=compteur;
	this->couleur=cetteCouleur;
}

// Destructeur
Pion::~Pion(void)
{
	compteur--; 
	if (this->couleur=="rouge") this->nbPionRouge--;
	if (this->couleur=="jaune") this->nbPionJaune--;
}

// Getter et setter
// On n'aura pas à fixer le numéro ou la couleur du pion
// qui seront déterminés au moment de la création et uniquement
// par le constructeur. Donc, pas de setters correspondants.
// Tous les pions sont créés en début de partie et aucun n'est
// détruit en cours de partie.

int Pion::getNum(void)
{
	return this->num;
}

string Pion::getCouleur(void)
{
	return this->couleur;
}

void Pion::info(void)
{
	cout<<"Je suis le pion "<<this->getNum()<<" et je suis de couleur "<<this->getCouleur()<<"."<<endl;
}