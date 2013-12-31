
#pragma once
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include <vector>
#include "Pion.h"
#include "Case.h"
#include "Colonne.h"
#include "EtatCourant.h"
using namespace std;

class Partie
{
	// Attributs
	private:
	string joueur1;
	string joueur2;
	vector<int> historique;
	bool gagne;
	int nbCoup;
	string trait;
	EtatCourant situation;
	vector<Pion> listePionJaune;
	vector<Pion> listePionRouge;

	// Méthodes
	public:
	Partie(void);
	~Partie(void);
	int getNbCoup(void);
	void joueUnCoup(bool*encore,int*coup,int*ligne,bool*ok,char*c);
	void annuleCoup(bool*effectue,int*i,int*j);
	void affiche(void);
};

