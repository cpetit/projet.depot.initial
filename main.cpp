  
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Pion.h"
#include "Case.h"
#include "Colonne.h"
#include "EtatCourant.h"
#include "Partie.h"
#include "Fenetre.h"
using namespace std;

int main(int argc, char** argv)
{

	Fenetre maFenetre;
	maFenetre.ouvrir(argc,argv);

	system("PAUSE");
    return(0);
} 