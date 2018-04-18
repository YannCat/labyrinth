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

extern int nb_ligne;
extern int nb_col;
extern int xInit;
extern int yInit;
extern int compteur;
extern int key;
extern char perso;
extern char chaine;
extern char tab[ymax][xmax];

#endif
