#ifndef FONCTIONS_H
#define FONCTIONS_H

#define xmax	41					// pour definir la taille du  labyrinthe
#define ymax	21
#define nb_map	3
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
extern char perso;
extern char chaine;
extern char tab[ymax][xmax];
extern char *laby;

	/**************************************************************Fonction Et Variables Nécessaire au fonctionnement du menu********************************************************************/

void menu_princ();
void creation_items();
void print_in_middle();
void choix_menu();
void titre_menu();
void dep_menu();
void reprendre();	

extern int highlight;

#endif
