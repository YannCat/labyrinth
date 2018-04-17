#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"
#include <unistd.h>
#include "fmod/fmod.h"
#include <string.h>


	int xmax=41,ymax=21; 													// pour definir la taille du  labyrinthe 

int main (int argc, char **argv)
{																			// Declaration des variables
	int compteur = 0;													
	char tab[ymax][xmax]; 													// pour creer un tableau qui sera le labyrinthe par rapport au xmax ymax
	int nb_ligne,nb_col;  													// definie le nombre de ligne et de colone du tableau
	char *quit = "Appuyez sur 'q' pour quitter";
	int taille2 = strlen(quit);
	//int niv = 0;
	
	int xInit, yInit;     													// variable pour definir le point d'initialisation du curseur
	int key=0;			  													// touche clavier initialisé a 0
	FMOD_SYSTEM  *fmodsys;
	FMOD_SOUND *sound;
	FMOD_System_Create(&fmodsys);
	FMOD_System_Init(fmodsys, 1, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(fmodsys, "music/Mijn.mp3", FMOD_CREATESTREAM, 0, &sound);	

																			//drawLab(xmax, ymax, nb_ligne, nb_col, tab); // x etait en com
	char chaine;
	char *lv1 = "files/lv1.txt";
	//char *lv2 = "files/lv2.txt";
    FILE *fichier;  														// recupere le fichier ou est stocker le labyrinthe
    fichier=fopen(lv1,"r");
   
    if(fichier == NULL)
        printf("Erreur lors de l'ouverture du fichier\n"); 					// si le fichier est introuvable, affiche une erreur
    else
    {
        // initLab();														// initialise le labyrinthe
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
							mur(nb_ligne, nb_col);
						break;
						
						case '0':											//affichage des chemins
							chemins(nb_ligne, nb_col);
                        break;
                        
                        case 'E':											//affichage de l'entrée
							entree(nb_ligne, nb_col);
							xInit = nb_ligne; 								// initialisation de la position du curseur
							yInit = nb_col;									// initialisation de la position du curseur
						break;
						
						case 'S':											//affichage de la sortie
							sortie(nb_ligne, nb_col);
						break;
					}
                    
                    refresh();       
                }
                fscanf(fichier,"%c",&chaine);
            }
        }
        fclose(fichier);   													// ferme le fichier.txt du labyrinthe
    }
	FMOD_System_PlaySound(fmodsys, sound, NULL, 0, NULL);
	keypad(stdscr,TRUE);
	curs_set(0);
    nb_ligne = xInit ;
	nb_col = yInit ;
	move((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
	mvprintw(LINES - 1,(COLS / 2) - (taille2 / 2), quit);

																			// Deplacement dans le labyrinthe

	while ((key != 'q') && (tab[nb_ligne][nb_col] != 'S'))
	{
		wattrset (stdscr, COLOR_PAIR(5));
		switch (key)
		{
			case KEY_RIGHT:
					if ( xmax - 1 > nb_col)
					{
						if (tab[nb_ligne][nb_col +1 ] != '1')
						{
						    addch (' ');
						    nb_col ++;
						   	moveCursor((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
					    }
				    }
				    compteur ++;
			break;
			
			case KEY_LEFT:
				   if (0 < nb_col)
				   {
					    if (tab[nb_ligne][nb_col - 1] != '1')
					    {
						    addch (' ');
						    nb_col --;
						  	moveCursor((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);					   
					    }
				   }
				   compteur ++;
			break;
			
			case KEY_DOWN:
				    if (  ymax - 1 > nb_ligne)
				    {
					    if (tab[nb_ligne + 1][nb_col] != '1')
					    {
						    addch (' ');
						    nb_ligne ++;
						    moveCursor((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
					    }
				    }
				    compteur ++;
			break;
			
			case KEY_UP:
				    if (0 < nb_ligne)
			  	    {
					    if (tab[nb_ligne - 1][nb_col] != '1')
					    {
						    addch (' ');
						    nb_ligne --;
						  	moveCursor((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
					    }
				    }
				    compteur ++;
			break;
		}
		key=getch();
		move((LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
		refresh();
	}
	
	if(tab[nb_ligne][nb_col] == 'S')
	{
		wattroff (stdscr, COLOR_PAIR(5));
		clear();
		//refresh();
		char *succes= "Vous avez gagné !";
		char *continuer = "Niveau Suivant ?";
		char *choose = "(o) Oui  /  (n)  Non";
		int taille= strlen(succes);
		int taille2 = strlen(quit);
		int taille3 = strlen(continuer);
		int taille4 = strlen(choose);
		while (key != 'q')
		{
			attron(A_BOLD);
			mvprintw(LINES/2, (COLS / 2) - (taille / 2), succes);
			attroff(A_BOLD);
			mvprintw(LINES/2 + 1, (COLS / 2) - (taille3 / 2), continuer);
			mvprintw(LINES/2 + 2, (COLS / 2) - (taille4 / 2), choose);
			/*if(key == 'o')
				{
				 	niv++;
					restart();
				}*/
			mvprintw(LINES - 1,(COLS / 2) - (taille2 / 2), quit);
			key=getch();
			refresh();
		}
		//afficher score et victoire
	}
	echo();
	endwin();
	FMOD_Sound_Release(sound);
	FMOD_System_Close(fmodsys);
	FMOD_System_Release(fmodsys);
	exit(0);
	return 0;
}
