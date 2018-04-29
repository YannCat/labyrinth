#ifndef FONCTIONS_H
#define FONCTIONS_H

#define xmax	41					// pour definir la taille du  labyrinthe
#define ymax	21
#define nb_map	4
#define ENTER	10
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

	/**************************************************************Fonction Et Variables Nécessaire au fonctionnement du Labyrinthe********************************************************************/

void initcurses();
void initColors();
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
void choix_lvl();
void tab_score();
void choix_pseudo();
void prog_princ();
void save();


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

	/**************************************************************Fonction Et Variables Nécessaire au fonctionnement du menu********************************************************************/

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
void reprendre();
void creation_items();
void print_in_middle();
void affich_score();

extern int highlight;
extern int highlight_lvl;
extern int highlight_game;

#endif
