
#include <iostream>
#include "Partie.h"

Partie::Partie(void)
{
	joueur1="moa";
	joueur2="ordi";
	gagne=false;
	int nbCoup=0;
	trait=joueur1;
	// Création du stock initial de pions.
	for(int i=0;i<(LARGEUR*HAUTEUR)/2;i++)
	{
		listePionRouge.push_back(Pion("rouge"));
		listePionJaune.push_back(Pion("jaune"));
	}
}


Partie::~Partie(void)
{
	// Nettoyage
}

void Partie::joueUnCoup(bool*encore,int*coup,int*ligne,bool*ok,char*c)
{	
	*ok=true;
	int numCase;
	if (!situation.getCol(*coup).isPleine())
	{
		if(this->trait==this->joueur1)
		{
			situation.jouer(this->listePionRouge.back(),*coup);
			this->listePionRouge.pop_back();
			*c='R';
		}
		if(this->trait==this->joueur2)
		{
			situation.jouer(this->listePionJaune.back(),*coup);
			this->listePionJaune.pop_back();
			*c='J';
		}
		nbCoup++;
		cout<<nbCoup<<"\n";
	}
	else
	{
		ok=false;
	}
	this->gagne=situation.isGagne();
	*ligne=this->situation.getCol(*coup).getNbPion()-1;
	*encore=!this->gagne;
	numCase=*ligne+7*(*coup);
	historique.push_back(numCase);
	if(this->trait==this->joueur1) this->trait=this->joueur2;
	else this->trait=this->joueur1;
}

void Partie::annuleCoup(bool*effectue,int* i,int*j)
{
	int derniereCase,ligne,colonne;
	if(this->nbCoup>0)
	{
		derniereCase=this->historique.back();
		this->historique.pop_back();
		ligne=derniereCase%7;
		colonne=(int)(derniereCase-ligne)/7;
		if (nbCoup%2==0) listePionRouge.push_back(this->situation.getCol(colonne).getContenuH(ligne));
		else listePionJaune.push_back(this->situation.getCol(colonne).getContenuH(ligne));
		this->situation.enleve(colonne);
		nbCoup--;
		cout<<nbCoup<<"\n";
		if(this->trait==this->joueur1) this->trait=this->joueur2;
		else this->trait=this->joueur1;
		*effectue=true;
		*i=ligne;
		*j=colonne;
	}
}

int Partie::getNbCoup(void)
{
	return this->nbCoup;
}

void Partie::affiche(void)
{
	char symbole;
	cout<<endl;
	for(int j=HAUTEUR-1;j>=0;j--)
	{
		for(int i=0;i<LARGEUR;i++)
		{
			if(this->situation.getCol(i).getContenuH(j).getCouleur()=="rouge") symbole='.';
			else
			{
				if(this->situation.getCol(i).getContenuH(j).getCouleur()=="jaune") symbole='O';
				else symbole=' ';
			}
			cout<<symbole;
		}
		cout<<endl;
	}
	cout<<endl;
}

