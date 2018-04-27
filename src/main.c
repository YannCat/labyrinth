#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"
#include <menu.h>				// Inclue automatiquement curses.h
#include <unistd.h>
#include "fmod.h"
#include <string.h>



int nb_ligne,nb_col;  													// definie le nombre de ligne et de colone du tableau
int xInit, yInit;     													// variable pour definir le point d'initialisation du curseur
int compteur = 0;														// Variable pour le score
int key = 0;			  												// touche clavier initialisé a 0
char tab[ymax][xmax]; 													// créer un tableau de dimension ymax * xmax
char perso = 'O';
char chaine;
char *laby = "files/lv1.txt";
int niv = 0;
int is_reload = 0;

int main ()
{		
	FMOD_SYSTEM  *fmodsys;
	FMOD_SOUND *sound;
	FMOD_System_Create(&fmodsys);
	FMOD_System_Init(fmodsys, 1, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(fmodsys, "music/Mijn.mp3", FMOD_CREATESTREAM, 0, &sound);
	FMOD_System_PlaySound(fmodsys, sound, NULL, 0, NULL);

	menu_princ();
	
	FMOD_Sound_Release(sound);
	FMOD_System_Close(fmodsys);
	FMOD_System_Release(fmodsys);
	exit(0);
	
	return 0;
}
