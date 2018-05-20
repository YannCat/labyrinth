#include "fonctions.h"


char perso = 'O';


void initLab(char *niveau, WINDOW *jeu)
{
		perso = 'O';
	 FILE *fichier;  														// recupere le fichier ou est stocker le labyrinthe
    fichier = fopen(niveau,"r");
   
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
							mur(jeu);
						break;
						
						case '0':											//affichage des chemins
							chemins(jeu);
                        break;
                        
                        case 'E':											//affichage de l'entrée
							entree(jeu);
						break;
						
						case 'S':											//affichage de la sortie
							sortie(jeu);
						break;
					}      
                }
                fscanf(fichier,"%c",&chaine);
            }
        wrefresh(jeu); 
        }
        fclose(fichier);  													// ferme le fichier.txt du labyrinthe
    }
}

void depLab(WINDOW *jeu)
{
	char *quit = "Appuyez sur F2 pour afficher le menu";
	char *nivel = "Niveau %d";
	int taille = strlen(quit);
	int t2 = strlen(nivel);
	curs_set(0);
    nb_ligne = xInit ;
	nb_col = yInit ;
	moveCursor(jeu, (LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
	mvwprintw(jeu, LINES - 1,(COLS / 2) - (taille / 2), quit);
	wattrset (jeu, A_BOLD);
	mvwprintw(jeu, (LINES/2)-(ymax/2) - 2,(COLS / 2) - (t2 / 2), nivel, niv+1);
	wattroff (jeu, A_BOLD);
	wrefresh(jeu);
	start = time(0);
	keypad(stdscr,FALSE);
	keypad(jeu,TRUE);
	while (key != KEY_F(2) && (tab[nb_ligne][nb_col] != 'S'))
	{
		trace_cursor(jeu);
		switch (key)
		{
			case KEY_RIGHT:
				droite(jeu);
			break;
			
			case KEY_LEFT:
				gauche(jeu);					   
			break;
			
			case KEY_DOWN:
				bas(jeu);
			break;
			
			case KEY_UP:
				haut(jeu);
			break;
		}
		key = wgetch(jeu);
		wmove(jeu, (LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
		wrefresh(jeu);
	}
	if (key == KEY_F(2))
	{
		key = 0;
		save();
		clear();
		wrefresh(jeu);
		endwin();
		menu_game();
	}
	else
	{
		endwin();
		fin();
	}
}

void moveCursor(WINDOW *jeu, int nb_ligne, int nb_col) 								//fonction déplacement curseur 
{
	int couleur = 0;
	if (niv == 0) couleur = 5;
	if (niv == 1) couleur = 3;
	if (niv == 2) couleur = 2;
	if (niv == 3) couleur = 5;
    wmove(jeu,nb_ligne, nb_col);
    wattrset (jeu, COLOR_PAIR(couleur));
    waddch(jeu, perso); 														//curseur dessin
    wattroff (jeu, COLOR_PAIR(couleur));
}

void trace_cursor(WINDOW *jeu)
{
	int couleur = 0;
	if (niv == 0) couleur = 5;
	if (niv == 1) couleur = 3;
	if (niv == 2) couleur = 2;
	if (niv == 3) couleur = 5;
	wattrset (jeu, COLOR_PAIR(couleur));
}

void mur(WINDOW *jeu)
{
	int couleur = 0;
	if (niv == 0) couleur = 8;
	if (niv == 1) couleur = 4;
	if (niv == 2) couleur = 1;
	if (niv == 3) couleur = 7;
	wattron(jeu, COLOR_PAIR(couleur));
	mvwprintw(jeu, (LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	wattroff(jeu, COLOR_PAIR(couleur));
}

void chemins(WINDOW *jeu)
{
	wattron(jeu, COLOR_PAIR(6));
	mvwprintw(jeu, (LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	wattroff(jeu, COLOR_PAIR(6));
}

void entree(WINDOW *jeu)
{
	mvwprintw(jeu, (LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	if(is_reload == 0)
	{
		xInit = nb_ligne; 								// initialisation de la position du curseur
		yInit = nb_col;									// initialisation de la position du curseur
	}
	is_reload = 0;
}

void sortie(WINDOW *jeu)
{
	int couleur;
	if( niv == 3) couleur = 8;
	else couleur = 7;
	wattron(jeu, COLOR_PAIR(couleur));
	mvwprintw(jeu, (LINES/2)-(ymax/2) + nb_ligne,(COLS/2)-(xmax/2) + nb_col," ");
	wattroff(jeu, COLOR_PAIR(couleur));	
}

void droite(WINDOW *jeu)
{
	if ( xmax - 1 > nb_col)
	{
		if (tab[nb_ligne][nb_col +1 ] != '1')
		{
			perso = '>';
			waddch (jeu, ' ');
			nb_col ++;
			moveCursor(jeu, (LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
			compteur ++;
		}
	}
}

void gauche(WINDOW *jeu)
{
	if (0 < nb_col)
	{
		if (tab[nb_ligne][nb_col - 1] != '1')
		{
			perso = '<';
			waddch (jeu, ' ');
			nb_col --;
			moveCursor(jeu, (LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
			compteur ++;
		}
	}
}

void bas(WINDOW *jeu)
{
	if (  ymax - 1 > nb_ligne)
	{
		if (tab[nb_ligne + 1][nb_col] != '1')
		{
			perso = 'v';
			waddch (jeu, ' ');
			nb_ligne ++;
			moveCursor(jeu, (LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
			compteur ++;
		}
	}
}

void haut(WINDOW *jeu)
{
	if (0 < nb_ligne)
	{
		if (tab[nb_ligne - 1][nb_col] != '1')
		{
			perso = '^';
			waddch (jeu, ' ');
			nb_ligne --;
			moveCursor(jeu, (LINES/2)-(ymax/2) + nb_ligne, (COLS/2)-(xmax/2) + nb_col);
			compteur ++;
		}
	}
}

void fin()
{
	WINDOW *lafin;
	lafin = newwin(LINES, COLS, 0, 0);
	if(tab[nb_ligne][nb_col] == 'S')
	{
		stop = time(0);
		total_time = (stop - start);
		clear();
		wrefresh(lafin);
		keypad(lafin, TRUE);
		while (key != 'o' && key != 'O' && key != KEY_F(2))
		{
			affich_fin(lafin);
		}
		if(key == 'o' || key == 'O')
		{
			if (niv < nb_map - 1)
			{
				tab_score(compteur);
				perso = 'O';
				compteur = 0;
				niv++;
				prog_princ();
			}
		}
		if (key == KEY_F(2))
		{
			tab_score(compteur);
			clear();
			wrefresh(lafin);
			endwin();
			menu_princ();
		}
	}
}

void affich_fin(WINDOW *win)
{
	char *succes = "Vous avez gagné !";
	char *mouv = "Score : %d";
	char *temps = "Temps : %d s";
	char *continuer = "Niveau Suivant ?";
	char *choose = "(o) Oui  /  (F2)  Menu";
	char *quit = "Appuyez sur F2 pour retourner au menu";
	if(niv >= nb_map - 1)
	{
		continuer = "Vous avez fini le jeu, bravo !";
		choose = "";
	}
	int taille = strlen(succes);
	int taille2 = strlen(quit);
	int taille3 = strlen(continuer);
	int taille4 = strlen(choose);
	int taille5 = strlen(mouv) + 3;
	int taille6 = strlen(temps);
	wattron(win, A_BOLD);
	mvwprintw(win, LINES/2 - 2, (COLS / 2) - (taille / 2), succes);
	wattroff(win, A_BOLD);
	mvwprintw(win, LINES/2 - 1, (COLS / 2) - (taille5 / 2), mouv, compteur);
	mvwprintw(win, LINES/2, (COLS / 2) - (taille6 / 2), temps, total_time);
	mvwprintw(win, LINES/2 + 1, (COLS / 2) - (taille3 / 2), continuer);
	mvwprintw(win, LINES/2 + 2, (COLS / 2) - (taille4 / 2), choose);
	mvwprintw(win, LINES - 1,(COLS / 2) - (taille2 / 2), quit);
	key = wgetch(win);
	wrefresh(win);
}
