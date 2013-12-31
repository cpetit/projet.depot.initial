
#include "Fenetre.h"
#include "Partie.h"
#include <iostream>

// Variables globales devant être appelées dans les différentes
// fonctions de callback dont on ne peut pas modifier le prototype.

Partie maPartie;
int valeurMenu;
char couleurCase[HAUTEUR][LARGEUR];


// Constructeur et destructeur (par défaut).
Fenetre::Fenetre(void)
{
}

Fenetre::~Fenetre(void)
{
}

// Méthodes

// La méthode ouvrir récupère les paramètres arg et argv indispensables
// au lancement de la bibliothèque opengl.
// Elle initialise la fenêtre graphique et gère les évènements.
void Fenetre::ouvrir(int argc, char** argv)
{
	// Prototypes des fonctions qui seront appelées par les fonctions callback.
	void affiche(void);
	void handleButtons(int button, int state, int x, int y);
	void handleResize(int w, int h);
	void handleKey(unsigned char key, int x, int y);
	void menu(int);

	// Initialisations de la fenêtre graphique
	// et des modes utilisés.
	glutInit(&argc, argv);							// Initialisation de glut.  
    glutInitWindowSize(800, 800*1080/1920);			// Taille de la fenetre.
    glutInitWindowPosition(50, 50);					// Position de la fenetre.
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);   // Type d'affficahge RGBA. 

	// Initialisation du tableau donnant la couleur de chaque case de la grille.
	for(int i=0;i<HAUTEUR;i++)
	{
		for(int j=0;j<LARGEUR;j++) couleurCase[i][j]='N';
	}

    glutCreateWindow("PUISSANCE 4 - clic droit pour accéder au menu - q pour quitter -"); 

	// Création du menu
	int m = glutCreateMenu(menu) ;
	glutSetMenu(m) ;
	glutAddMenuEntry("Charger partie.",1) ;
	glutAddMenuEntry("Sauvegarder partie.",2) ;
	glutAddMenuEntry("Annuler coup.",3) ;
	glutAddMenuEntry("Rejouer coup.",4) ;
	glutAddMenuEntry("Nouvelle partie.",5) ;
	glutAttachMenu(GLUT_RIGHT_BUTTON) ;

	// On écoute les évènements via les fonctions callback
	// et on affiche en fonction
	glutDisplayFunc(affiche);
	glutKeyboardFunc(handleKey);
	glutMouseFunc(handleButtons);
	glutReshapeFunc(handleResize);
	// Définition de la couleur de fond avant lancement de la
	// boucle open GL
	glClearColor(0, 0, 1, 0);
	glutMainLoop();
}

// Fonction effectuant l'affichage et sa mise à jour.
void affiche()
{
  int i;
  void annuleCoup(void);

  //GLfloat tabDisque[HAUTEUR][LARGEUR][50*3];
  
  glClear(GL_COLOR_BUFFER_BIT);
  
  switch(valeurMenu)
  {
	case 1: cout<<"Charger."<<endl;break;
	case 2: cout<<"Sauver."<<endl;break;
	case 3: annuleCoup();break;
	case 4: cout<<"Rejouer."<<endl;break;
	case 5: cout<<"Nouvelle."<<endl;break;
  }
 
  // Tracé de la grille.
  glColor3f(0, 0, 0);
  glLineWidth(1);  
  glBegin(GL_LINES);
  for(i = 0; i <= LARGEUR; i++)
  {
      glVertex2f(0, i);
      glVertex2f(LARGEUR, i);
  }
  for(i = 0; i <= LARGEUR; i++)
  {
	glVertex2f(i, 0);
	glVertex2f(i, HAUTEUR);
  }
  glEnd();
  glFlush();

  // Tracé des cases.
  for(int k=0;k<LARGEUR;k++)
  {
	for(int l=0;l<HAUTEUR;l++)
	{
		/* Tentative d'utilisation des draw array
		Pour l'instant ça ne marche pas.
		int j=0;
		for(float i = 0; i < 2 * PI; i += PI / 25)
		{
			tabDisque[k][l][j]=0.5+k+cos((float)i)*0.4;
			tabDisque[k][l][j+1]=0.5+l+sin((float)i)*0.4;
			tabDisque[k][l][j+2]=0.0;
			j=j+3;
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,0,tabDisque[k][l]);
		glDrawArrays(GL_POLYGON,0,150);
		glFlush();*/

		if(couleurCase[l][k]=='N') glColor3f(0, 0, 0);
		else if(couleurCase[l][k]=='R') glColor3f(1, 0, 0);
		else glColor3f(255, 255, 0);
		glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * PI; i += PI / 25)glVertex3f(0.5+k+cos((double)i)*0.4,0.5+l+sin((double)i)*0.4, 0.0);
		glEnd();
		glFlush();
	}
  }
}

void handleButtons(int button, int state, int x, int y)
{
  int i, j;
  float dx, dy; 

  bool* partieEnCours= new bool;
  bool* ok= new bool;
  int* coup=new int;
  int* ligne=new int;
  char* c=new char;

  *partieEnCours=true;
  *ok=true;

	if(button != GLUT_LEFT_BUTTON || state != GLUT_UP) return;  
	y = Height - y;
	dy = Height/(float)HAUTEUR;
	dx = Width/(float)LARGEUR;
	i = (int)(y/dy);
	j = (int)(x/dx); 
	cout<<"clic sur la case ("<<j<<","<<i<<").\n";
	*coup=j;
	maPartie.joueUnCoup(partieEnCours,coup,ligne,ok,c);
	if(*ok)
	{
		if (*c=='R')couleurCase[*ligne][*coup]='R';
		if (*c=='J')couleurCase[*ligne][*coup]='J';
		glutPostRedisplay();
		/*Modif du 31/12/2013 pour corriger le pb d'affichage
		if (*c=='R') glColor3f(1, 0, 0);
		if (*c=='J') glColor3f(255, 255, 0);
		glBegin(GL_POLYGON);
		for(double k = 0; k < 2 * PI; k += PI / 25)glVertex3f(0.5+(*coup)+cos((double)k)*0.4,0.5+(*ligne)+sin((double)k)*0.4, 0.0);
		glEnd();
		glFlush();*/
	}
	delete partieEnCours;
	delete ok;
	delete coup;
	delete ligne;
	delete c;
}

void handleResize(int w, int h)
{
  Width = w;
  Height = h;
  glViewport(0, 0, Width, Height); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, LARGEUR, 0, HAUTEUR);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

void handleKey(unsigned char key,int x, int y)
{
  switch(key)
  {
    case 'q':
    case 'Q':
    exit(0);
  }
}

void menu(int choix)
{
	valeurMenu = choix;
	glutPostRedisplay() ;
}


void annuleCoup(void)
{
	bool* isCoupAnnule= new bool;
	int* i=new int;
	int* j=new int;
	maPartie.annuleCoup(isCoupAnnule,i,j);
	if(*isCoupAnnule)
	{
		couleurCase[*i][*j]='N';
		//glutPostRedisplay() ;
		/*glutPostRedisplay();
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		for(double k = 0; k < 2 * PI; k += PI / 25)glVertex3f(0.5+(*i)+cos((double)k)*0.4,0.5+(*j)+sin((double)k)*0.4, 0.0);
		glEnd();
		glFlush();*/
	}
	delete isCoupAnnule;
	delete i;
	delete j;
}
