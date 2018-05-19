#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <menu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "fmod.h"


#define xmax	41					// pour definir la taille du  labyrinthe
#define ymax	21
#define nb_map	4
#define ENTER	10
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

extern int nb_ligne;
extern int nb_col;
extern int xInit;
extern int yInit;
extern int compteur;
extern int key;
extern int niv;
extern int is_reload;
extern int new_party;
extern char perso;
extern char chaine;
extern char tab[ymax][xmax];
extern char *laby;
extern int start;
extern int stop;
extern int total_time;
extern char pseudo[4];

					/**************************************************************Fonction du fichier labyrinthe********************************************************************/

void initLab();
void depLab();
void moveCursor();
void trace_cursor();
void mur();
void chemins();
void entree();
void sortie();
void droite();
void gauche();
void bas();
void haut();
void fin();
void affich_fin();

					/**************************************************************Fonction du fichier fonction********************************************************************/


void initcurses();
void initColors();
void choix_lvl();
void tab_score();
void affich_score();
void save();
void reprendre();
void choix_pseudo();
void bienvenue();
void prog_princ();

					/**************************************************************Fonction du fichier menu.c********************************************************************/

void menu_princ();
void menu_lvl();
void menu_game();

void choix_menu();
void choix_menu_lvl();
void choix_menu_game();

void dep_menu();
void dep_menu_lvl();
void dep_menu_game();

void titre_menu();
void suppr_menu();
void creation_items();
void print_in_middle();


#endif
