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
extern char chaine;
extern char tab[ymax][xmax];
extern char *laby;
extern int start;
extern int stop;
extern int total_time;
extern char pseudo[4];

					/**************************************************************Fonction du fichier labyrinthe********************************************************************/

void initLab();			// affiche le labyrinthe
void depLab();			// permet de se déplacer dans le labyrinthe
void moveCursor();		// fonction permettant de déplacer le personnage dans le labyrinthe
void trace_cursor();	// affiche le chemin du personnage
void mur();				// affiche les murs
void chemins();			// affiche les chemins
void entree();			// place l'entrée du labyrinthe
void sortie();			// place la sortie du labyrinthe
void droite();			// déplace le personnage vers la droite
void gauche();			// déplace le personnage vers la gauche
void bas();				// déplace le personnage vers le bas
void haut();			// déplace le personnage vers le haut
void fin();				// gère la sortie du labyrinthe
void affich_fin();		// affiche le message de fin

					/**************************************************************Fonction du fichier fonction********************************************************************/


void initcurses();		// initialise les fonctions nécessaires à l'utilisation de ncurses
void initColors();		// initialise les fonctions d'affichage des couleurs
void choix_lvl();		// permet de choisir le chemin vers le fichier de la map du labyrinthe
void tab_score();		// enregistre les scores dans un fichier .txt
void affich_score();	// affiche le tableau des scores
void save();			// sauvegarde la position du personnage dans un fichier .txt
void reprendre();		// lis les informations dans le fichier de sauvegarde
void choix_pseudo();	// permet de choisir son pseudo
void bienvenue();		// affiche la page de préseantation du jeu au lancement
void prog_princ();		// programme réunissant toute les fonctions nécessaire au labyrinthe

					/**************************************************************Fonction du fichier menu.c********************************************************************/

void menu_princ();		// fonction servant à l'affichage du menu principal
void menu_lvl();		// fonction servant à l'affichage du choix du niveau	
void menu_game();		// fonction servant à l'affichage du menu pause

void choix_menu();		// affiche les différente possibilité du menu principal 
void choix_menu_lvl();	// affiche les différente possibilité du menu du choix du niveau
void choix_menu_game();	// affiche les différente possibilité du menu pause

void dep_menu();		// permet de se déplacer dans le menu principal
void dep_menu_lvl();	// permet de se déplacer dans le menu du choix du niveau
void dep_menu_game();	// permet de se déplacer dans le menu pause

void titre_menu();		// permet d'afficher le titre du menu	
void suppr_menu();		// permet de supprimer le menu afficher
void creation_items();	// permet de créer les differents choix possible
void print_in_middle();	// permet de centrer l'affichage du titre du menu


#endif
