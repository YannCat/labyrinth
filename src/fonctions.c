#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

#define ENTER 10
#define ESCAPE 27

void initColors()
{
    initscr(); 
    noecho(); 
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLACK);
    init_pair(2,COLOR_BLACK,COLOR_WHITE); // couleur barre menu
    init_pair(3,COLOR_RED,COLOR_WHITE); 
    init_pair(4, COLOR_BLACK, COLOR_BLACK); //couleur mur
    init_pair(5, COLOR_WHITE, COLOR_GREEN); //couleur curseur
    init_pair(6, COLOR_WHITE, COLOR_WHITE); 
    init_pair(7, COLOR_RED, COLOR_RED); //sortie
    init_pair(8, COLOR_GREEN, COLOR_GREEN); //entree
    curs_set(0); // initalisation curseur
    keypad(stdscr,TRUE); //initialisation clavier
}

void moveCursor(int nb_ligne, int nb_col) //fonction déplacement curseur 
{
    move(nb_ligne,nb_col);
    wattrset (stdscr, COLOR_PAIR(5));
    addch('$'); //curseur dessin
}

/*void initLab()
{
	switch (tab[nb_ligne][nb_col]){
		case '1':											//affichage des murs
			mur()
		break;
		
		case '0':											//affichage des chemins
			
		break;
		
		case 'E':											//affichage de l'entrée
			
			xInit = nb_ligne; 								// initialisation de la position du curseur
			yInit = nb_col;									// initialisation de la position du curseur
		break;
		
		case 'S':											//affichage de la sortie

		break;
}*/

void mur(int nb_ligne, int nb_col)
{
	attron(COLOR_PAIR(4));
	mvprintw((LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	attroff(COLOR_PAIR(4));
}

void chemins(int nb_ligne, int nb_col)
{
	attron(COLOR_PAIR(6));
	mvprintw((LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	attroff(COLOR_PAIR(6));
}

void entree(int nb_ligne, int nb_col)
{
	attron(COLOR_PAIR(8));
	mvprintw((LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	attroff(COLOR_PAIR(8));
}

void sortie(int nb_ligne, int nb_col)
{
	attron(COLOR_PAIR(7));
	mvprintw((LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	attroff(COLOR_PAIR(7));	
}
