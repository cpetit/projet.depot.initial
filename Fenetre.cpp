// Version du 04/02/14

#include "Fenetre.h"
#include "Partie.h"
#include <iostream>

// Variables globales devant �tre appel�es dans les diff�rentes
// fonctions de callback (dont on ne peut pas modifier le prototype).

Partie maPartie;
int valeurMenu;
char couleurCase[HAUTEUR][LARGEUR];

// Constructeur et destructeur (par d�faut).
Fenetre::Fenetre(void)
{
}

Fenetre::~Fenetre(void)
{
}

// M�thodes

// La m�thode ouvrir r�cup�re les param�tres arg et argv indispensables
// au lancement de la biblioth�que opengl.
// Elle initialise la fen�tre graphique et g�re les �v�nements.

void Fenetre::ouvrir(int argc, char** argv)
{

	// Prototypes des fonctions qui seront appel�es par les fonctions callback
	// lorsqu'un �v�nement se d�clenche.
	void affiche(void);
	void handleButtons(int button, int state, int x, int y);
	void handleResize(int w, int h);
	void handleKey(unsigned char key, int x, int y);
	void menu(int);
	//_________________________________________________________________________


	// Initialisation du tableau donnant la couleur de chaque case de la grille.
	for(int i=0;i<HAUTEUR;i++)
	{
		for(int j=0;j<LARGEUR;j++) couleurCase[i][j]='N';
	}
	//_________________________________________________________________________
	

	// Initialisations de la fen�tre graphique
	// et des modes graphiques utilis�s.
	glutInit(&argc, argv);							// Initialisation de glut.  
    glutInitWindowSize(800, 800*1080/1920);			// Taille de la fenetre.
    glutInitWindowPosition(50, 50);					// Position de la fenetre.
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);   // Type d'affficahge RGBA. 
    glutCreateWindow("PUISSANCE 4 - clic droit pour acc�der au menu - q pour quitter -"); 
	//_________________________________________________________________________


	// Cr�ation du menu
	int m = glutCreateMenu(menu) ;
	glutSetMenu(m) ;
	glutAddMenuEntry("Charger partie.",1) ;
	glutAddMenuEntry("Sauvegarder partie.",2) ;
	glutAddMenuEntry("Annuler coup.",3) ;
	glutAddMenuEntry("Rejouer coup.",4) ;
	glutAddMenuEntry("Nouvelle partie.",5) ;
	glutAttachMenu(GLUT_RIGHT_BUTTON) ;
	//_____________________________________________


	// On �coute les �v�nements via les fonctions callback
	// et on effctue l'affichage en fonction des appels.
	glutDisplayFunc(affiche);
	glutKeyboardFunc(handleKey);
	glutMouseFunc(handleButtons);
	glutReshapeFunc(handleResize);
	//____________________________________________________

	// Lancement de la boucle principale d'affichage et de
	// la machine � �tats opengl.
	glutMainLoop();
}


// Fonction effectuant l'affichage et sa mise � jour.
// Cette fonction est automatiquement appel�e (via la 
// fonction callback glutDisplayFunc) d�s qu'un affichage
// est � effectuer.
void affiche()
{
  int i;
  void annuleCoup(void); // prototype d'annuleCoup

  // GLfloat tabDisque[HAUTEUR][LARGEUR][50*3];
  
  glClearColor(0, 0, 1, 0);		// Couleur de fond
  glClear(GL_COLOR_BUFFER_BIT);	// Nettoyage de la fen�tre 
  
  // Ecoute du menu et ex�cution de la fonction
  // correspondante � chaque choix (via le callback !).
  switch(valeurMenu)
  {
	case 1: cout<<"Charger."<<endl;break;
	case 2: cout<<"Sauver."<<endl;break;
	case 3: annuleCoup();break;
	case 4: cout<<"Rejouer."<<endl;break;
	case 5: cout<<"Nouvelle."<<endl;break;
  }
  valeurMenu=0;
 
  // Trac� de la grille.
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

  // Trac� initial des cases.
  glEnableClientState(GL_NORMAL_ARRAY);
  for(int k=0;k<LARGEUR;k++)
  {
	for(int l=0;l<HAUTEUR;l++)
	{
		if(couleurCase[l][k]=='N') glColor3f(0, 0, 0);
		else if(couleurCase[l][k]=='R') glColor3f(1, 0, 0);
		else glColor3f(255, 255, 0);
		glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * PI; i += PI / 25)glVertex3f(0.5+k+cos((double)i)*0.4,0.5+l+sin((double)i)*0.4, 0.0);
		glEnd();
		glFlush();
	}
	//GLUquadricObj *circle = gluNewQuadric ();
	//if (circle != 0) gluQuadricDrawStyle(circle, GLU_FILL); 
	//gluDisk (nomDuDisque,centre,rayon,rayonTrouCentral,1);
	//gluDisk (circle,0,2,60,4); 

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
	}
	delete partieEnCours;
	delete ok;
	delete coup;
	delete ligne;
	delete c;
}

// Fonction de changement de taille ou de place
// de la fen�tre et de mise � jour des �l�ments � afficher.
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
		glutPostRedisplay() ;
	}
	delete isCoupAnnule;
	delete i;
	delete j;
}
