#ifndef FONCTIONS_H
#define FONCTIONS_H

void initColors();
void drawBar();
void delMenu();
int browseMenu();
int browseMenu();
WINDOW **drawMenu();
void initLab();
void moveCursor();
void drawLab();

void mur();
void chemins();
void entree();
void sortie();
void droite();
void gauche();
void bas();
void haut();

extern int xmax;
extern int ymax;
extern int nb_ligne;
extern int nb_col;
extern int xInit;
extern int yInit;
extern int compteur;
extern char perso;

#endif
