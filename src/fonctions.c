#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"
#include <string.h>

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

void initLab(char *niveau)
{
	 FILE *fichier;  														// recupere le fichier ou est stocker le labyrinthe
    fichier=fopen(niveau,"r");
   
    if(fichier == NULL)
        printf("Erreur lors de l'ouverture du fichier\n"); 					// si le fichier est introuvable, affiche une erreur
    else
    {
        initColors();														// initialise les couleurs du labyrinthe
        while (!feof(fichier))  
        {
            for(nb_ligne=0;nb_ligne<=ymax;nb_ligne++)		
            {
                for(nb_col=1;nb_col<=xmax;nb_col++)
                {
                    fscanf(fichier,"%c",&tab[nb_ligne][nb_col]);
                    switch (tab[nb_ligne][nb_col]){
						case '1':											//affichage des murs
							mur();
						break;
						
						case '0':											//affichage des chemins
							chemins();
                        break;
                        
                        case 'E':											//affichage de l'entrée
							entree();
						break;
						
						case 'S':											//affichage de la sortie
							sortie();
						break;
					}
                    
                    refresh();       
                }
                fscanf(fichier,"%c",&chaine);
            }
        }
        fclose(fichier);   													// ferme le fichier.txt du labyrinthe
    }
}

void depLab(char *quit, int taille2)
{
	keypad(stdscr,TRUE);
	curs_set(0);
    nb_ligne = xInit ;
	nb_col = yInit ;
	moveCursor((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
	mvprintw(LINES - 1,(COLS / 2) - (taille2 / 2), quit, 'q');
	
	while ((key != 'q') && (tab[nb_ligne][nb_col] != 'S'))
	{
		wattrset (stdscr, COLOR_PAIR(5));
		switch (key)
		{
			case KEY_RIGHT:
				droite();
			break;
			
			case KEY_LEFT:
				gauche();					   
			break;
			
			case KEY_DOWN:
				bas();
			break;
			
			case KEY_UP:
				haut();
			break;
		}
		key=getch();
		move((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
		refresh();
	}
	fin();
}

void moveCursor(int nb_ligne, int nb_col) 								//fonction déplacement curseur 
{
    move(nb_ligne,nb_col);
    wattrset (stdscr, COLOR_PAIR(5));
    addch(perso); 														//curseur dessin
    wattroff (stdscr, COLOR_PAIR(5));
}

void mur()
{
	attron(COLOR_PAIR(4));
	mvprintw((LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	attroff(COLOR_PAIR(4));
}

void chemins()
{
	attron(COLOR_PAIR(6));
	mvprintw((LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	attroff(COLOR_PAIR(6));
}

void entree()
{
	attron(COLOR_PAIR(8));
	mvprintw((LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	attroff(COLOR_PAIR(8));
	xInit = nb_ligne; 								// initialisation de la position du curseur
	yInit = nb_col;									// initialisation de la position du curseur
}

void sortie()
{
	attron(COLOR_PAIR(7));
	mvprintw((LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	attroff(COLOR_PAIR(7));	
}

void droite()
{
	if ( xmax - 1 > nb_col)
	{
		if (tab[nb_ligne][nb_col +1 ] != '1')
		{
			perso = '>';
			addch (' ');
			nb_col ++;
			moveCursor((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
			compteur ++;
		}
	}
}

void gauche()
{
	if (0 < nb_col)
	{
		if (tab[nb_ligne][nb_col - 1] != '1')
		{
			perso = '<';
			addch (' ');
			nb_col --;
			moveCursor((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
			compteur ++;
		}
	}
}

void bas()
{
	if (  ymax - 1 > nb_ligne)
	{
		if (tab[nb_ligne + 1][nb_col] != '1')
		{
			perso = 'v';
			addch (' ');
			nb_ligne ++;
			moveCursor((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
			compteur ++;
		}
	}
}

void haut()
{
	if (0 < nb_ligne)
	{
		if (tab[nb_ligne - 1][nb_col] != '1')
		{
			perso = '^';
			addch (' ');
			nb_ligne --;
			moveCursor((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
			compteur ++;
		}
	}
}

void fin()
{
	if(tab[nb_ligne][nb_col] == 'S')
	{
		clear();
		refresh();
		char *succes = "Vous avez gagné !";
		char *mouv = "Score : ";
		char *continuer = "Niveau Suivant ?";
		char *choose = "(o) Oui  /  (n)  Non";
		if(niv >= 2)
		{
			continuer = "Vous avez fini le jeu, bravo !";
			choose = "";
		}
		int taille = strlen(succes);
		int taille3 = strlen(continuer);
		int taille4 = strlen(choose);
		int taille5 = strlen(mouv) + 3;
		while (key != 'o' && key != 'n')
		{
			attron(A_BOLD);
			mvprintw(LINES/2, (COLS / 2) - (taille / 2), succes);
			attroff(A_BOLD);
			mvprintw(LINES/2 + 1, (COLS / 2) - (taille5 / 2), "Score : %d", compteur);
			mvprintw(LINES/2 + 2, (COLS / 2) - (taille3 / 2), continuer);
			mvprintw(LINES/2 + 3, (COLS / 2) - (taille4 / 2), choose);
			mvprintw(LINES - 1,(COLS / 2) - (taille2 / 2), quit, 'n');
			key = getch();
			refresh();
			compteur = 0;
		}
		if(key == 'o')
		{
		niv++;
		prog_princ();
		}
	}
}

void choix_lvl(int choix)
{
	char *lv1 = "files/lv1.txt";
	char *lv2 = "files/lv2.txt";
	char *lv3 = "files/lv3.txt";

	
	switch (choix)
		{
			case 0:
				laby = lv1;
			break;
			
			case 1:
				laby = lv2;
			break;
			
			case 2:
				laby = lv3;
			break;
		}
}

void prog_princ()
{
	choix_lvl(niv);														// Choix de la map.
	initLab(laby);														// Initialise le Labyrinthe
	depLab(quit, taille2);												// Deplacement dans le labyrinthe
}
