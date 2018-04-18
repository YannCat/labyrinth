#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"
#include <unistd.h>
#include "fmod/fmod.h"
#include <string.h>



int nb_ligne,nb_col;  													// definie le nombre de ligne et de colone du tableau
int xInit, yInit;     													// variable pour definir le point d'initialisation du curseur
int compteur = 0;														// Variable pour le score
int key = 0;			  												// touche clavier initialisé a 0
char tab[ymax][xmax]; 													// pour creer un tableau qui sera le labyrinthe par rapport au xmax ymax
char perso = 'O';
char chaine;

int main (int argc, char **argv)
{																			// Declaration des variables
													

	char *quit = "Appuyez sur 'q' pour quitter";
	int taille2 = strlen(quit);
	int niv = 0;
	
	FMOD_SYSTEM  *fmodsys;
	FMOD_SOUND *sound;
	FMOD_System_Create(&fmodsys);
	FMOD_System_Init(fmodsys, 1, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(fmodsys, "music/Mijn.mp3", FMOD_CREATESTREAM, 0, &sound);	

	char *laby = "files/lv1.txt";
	
	initLab(laby);														// Initialise le Labyrinthe
	FMOD_System_PlaySound(fmodsys, sound, NULL, 0, NULL);
	depLab(quit, taille2);												// Deplacement dans le labyrinthe
	
	echo();
	endwin();
	FMOD_Sound_Release(sound);
	FMOD_System_Close(fmodsys);
	FMOD_System_Release(fmodsys);
	exit(0);
	
	return 0;
}
