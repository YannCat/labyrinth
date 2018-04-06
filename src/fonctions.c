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

