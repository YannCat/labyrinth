#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"
#include <unistd.h>



int main (int argc, char **argv)
{
    initColors();
    // Declaration des variables
	int xmax=41,ymax=21;  // pour definir la taille du  labyrinthe
	char tab[ymax][xmax]; // pour creer un tableau qui sera le labyrinthe par rapport au xmax ymax
	int nb_ligne,nb_col;  // definie le nombre de ligne et de colone du tableau
	
	int xInit, yInit;     // variale pour definir le point d'initialisation du curseur
	int key=0;			  // touche clavier initialisé a 0
	
	

	//drawLab(xmax, ymax, nb_ligne, nb_col, tab); // x etait en com
	char chaine;
    FILE *fichier;  // recupere le fichier ou est stocker le labyrinthe
    fichier=fopen("files/fichier.txt","r");
    
    if(fichier == NULL)
        printf("Erreur lors de l'ouverture du fichier\n"); // si le fichier est introuvable, affiche une erreur
    else
    {
        // initLab();			// initialise le labyrinthe
        initColors();		// initialise les couleurs du labyrinthe
        while (!feof(fichier))  
        {
            for(nb_ligne=0;nb_ligne<=ymax;nb_ligne++)		
            {
                for(nb_col=1;nb_col<=xmax;nb_col++)
                {
                   fscanf(fichier,"%c",&tab[nb_ligne][nb_col]);
                    if(tab[nb_ligne][nb_col] == '1') //mur
                    {
                        attron(COLOR_PAIR(4));
                        mvprintw(nb_ligne,nb_col," ");
                        attroff(COLOR_PAIR(4));
                    }
                    else if(tab[nb_ligne][nb_col] == '0')//couloir
                    {
                        attron(COLOR_PAIR(6));
                        mvprintw(nb_ligne,nb_col," ");
                        attroff(COLOR_PAIR(6));
                    }
                    else if(tab[nb_ligne][nb_col] == 'E')//entree
                    {
                        attron(COLOR_PAIR(8));
                        mvprintw(nb_ligne,nb_col," ");
                        attroff(COLOR_PAIR(8));
                        xInit = nb_ligne; 								// initialisation de la position du curseur
                        yInit = nb_col;									// initialisation de la position du curseur
                    }
                    else if(tab[nb_ligne][nb_col] == 'S')				//sortie
                    {
                        attron(COLOR_PAIR(7));
                        mvprintw(nb_ligne,nb_col," ");
                        attroff(COLOR_PAIR(7));
                    }
                    
                    refresh();       
                }
                fscanf(fichier,"%c",&chaine);
            }
        }
        fclose(fichier);   												// ferme le fichier.txt du labyrinthe
    }

	keypad(stdscr,TRUE);
	curs_set(0);
    nb_ligne= xInit ;
	nb_col= yInit ;
	move(nb_ligne,nb_col);

																		// Deplacement dans le labyrinthe

	while ((key != 'q') && (tab[nb_ligne][nb_col] != 'S'))
	{
		wattrset (stdscr, COLOR_PAIR(5));
		switch (key)
		{
			case KEY_RIGHT:
					if (xmax - 1 > nb_col)
					{
						if (tab[nb_ligne][nb_col +1 ] != '1')
						{
						    addch (' ');
						    nb_col ++;
						   	moveCursor(nb_ligne,nb_col);
					    }
				    }
			break;
			case KEY_LEFT:
				   if (0 < nb_col)
				   {
					    if (tab[nb_ligne][nb_col - 1] != '1')
					    {
						    addch (' ');
						    nb_col --;
						  	moveCursor(nb_ligne,nb_col);					   
					    }
				   }
			break;
			case KEY_DOWN:
				    if (ymax - 1 > nb_ligne)
				    {
					    if (tab[nb_ligne + 1][nb_col] != '1')
					    {
						    addch (' ');
						    nb_ligne ++;
						    moveCursor(nb_ligne,nb_col);
					    }
				    }
			break;
			case KEY_UP:
				    if (0< nb_ligne)
			  	    {
					    if (tab[nb_ligne - 1][nb_col] != '1')
					    {
						    addch (' ');
						    nb_ligne --;
						  	moveCursor(nb_ligne,nb_col);
					    }
				    }
			break;
		}
		key=getch();
		move(nb_ligne,nb_col);
		refresh();
	}
	if(tab[nb_ligne][nb_col] == 'S')
	{
		//printf("Vous avez Gagnez");
		//delay(500); 
		//afficher score et victoire
	}
	echo();
	endwin(); 
	exit(0);
	return 0;
}
