#ifndef FONCTIONS_H
#define FONCTIONS_H

#define xmax 41					// pour definir la taille du  labyrinthe
#define ymax 21

void initColors();
void initLab();
void depLab();
void moveCursor();
void mur();
void chemins();
void entree();
void sortie();
void droite();
void gauche();
void bas();
void haut();
void fin();
void choix_lvl();
void prog_princ();

extern int nb_ligne;
extern int nb_col;
extern int xInit;
extern int yInit;
extern int compteur;
extern int key;
extern int niv;
extern int taille2;
extern char *quit;
extern char perso;
extern char chaine;
extern char tab[ymax][xmax];
extern char *laby;

#endif
