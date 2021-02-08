#include "fonctions.h"



int nb_ligne,nb_col;  													// definie le nombre de ligne et de colone du tableau
int xInit, yInit;     													// variable pour definir le point d'initialisation du curseur
int compteur = 0;														// Variable pour le score
int key = 0;			  												// touche clavier initialisé a 0
char tab[ymax][xmax]; 													// créer un tableau de dimension ymax * xmax
char chaine;
char *laby;
int niv;
int is_reload = 0;
int new_party = 0;
int start, stop;
int total_time;
char pseudo[4];

int main ()
{		
	FMOD_SYSTEM  *fmodsys;
	FMOD_SOUND *sound;
	FMOD_System_Create(&fmodsys);
	FMOD_System_Init(fmodsys, 1, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(fmodsys, "music/Mijn.mp3", FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &sound);
	FMOD_Sound_SetLoopCount(sound, -1);
	FMOD_System_PlaySound(fmodsys, sound, NULL, 0, NULL);

	bienvenue();
	menu_princ();
	
	FMOD_Sound_Release(sound);
	FMOD_System_Close(fmodsys);
	FMOD_System_Release(fmodsys);
	exit(0);
	
	return 0;
}
