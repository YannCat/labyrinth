#include <menu.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"
#include <string.h>
#include <time.h>
#include <unistd.h>


#define ESCAPE 27

void initcurses()
{
	initscr();
    cbreak();
    noecho();
	initColors();			// initialisation couleurs
    init_pair(1,COLOR_RED,COLOR_BLACK);		//couleur titre menu
	curs_set(0); 			// initalisation curseur
    keypad(stdscr,TRUE);	// initialisation clavier
}

void initColors()
{ 
    start_color();
    init_pair(1,COLOR_CYAN,COLOR_CYAN);		//mur
    init_pair(2,COLOR_WHITE,COLOR_MAGENTA);
    init_pair(3,COLOR_WHITE,COLOR_RED);			//couleur curseur 
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW); //couleur mur
    init_pair(5, COLOR_WHITE, COLOR_BLUE); //couleur curseur
    init_pair(6, COLOR_WHITE, COLOR_WHITE); //couleur couloir
    init_pair(7, COLOR_RED, COLOR_RED); //sortie
    init_pair(8, COLOR_GREEN, COLOR_GREEN);	// couleur mur
}

void initLab(char *niveau, WINDOW *jeu)
{
	
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
			exit(0);
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
	char *quit = "Appuyez sur F2 pour quitter";
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

void choix_lvl()
{
	char *lv1 = "files/lv1.txt";
	char *lv2 = "files/lv2.txt";
	char *lv3 = "files/lv3.txt";
	char *lv4 = "files/lv4.txt";
	
	switch (niv)
		{
			case 0:
				if(is_reload == 0 && new_party == 1)
				{
					choix_pseudo();
				}
				laby = lv1;
			break;
			
			case 1:
				if(is_reload == 0 && new_party == 1)
				{
					choix_pseudo();
				}
				laby = lv2;
			break;
			
			case 2:
				if(is_reload == 0 && new_party == 1)
				{
					choix_pseudo();
				}
				laby = lv3;
			break;
			case 3:
				if(is_reload == 0 && new_party == 1)
				{
					choix_pseudo();
				}
				laby = lv4;
			break;
		}
}
void tab_score(int score)
{
	char *tab_score = "files/score.txt";
	FILE *fichier;  														// recupere le fichier ou est stocker le labyrinthe
    fichier=fopen(tab_score,"a");
   
    if(fichier == NULL)
        printf("Erreur lors de l'ouverture du fichier\n"); 					// si le fichier est introuvable, affiche une erreur
    else
    {
		fprintf(fichier,"%s\t%d\t%d\t%d\n", pseudo, niv + 1, score, total_time);
	}
    fclose(fichier);
}

void affich_score()
{
	int i = 0;
	char nom[20][50] = {"\0"};
	char level[20][10] = {"\0"};
	char point[20][4] = {"\0"};
	char temps[20][5] = {"\0"};
	
	int t11[20], t21[20], t31[20], t41[20];
	
	char *tab_score = "files/score.txt";
	FILE *fichier;
	fichier = fopen(tab_score,"r");
	
	while (!feof(fichier))  
	{
		fscanf(fichier,"%s\t%s\t%s\t%s\n", 	nom[i], level[i], point[i], temps[i]);
		t11[i] = strlen(nom[i]);
		t21[i] = strlen(level[i]);
		t31[i] = strlen(point[i]);
		t41[i] = strlen(temps[i]);
		i++;		
	}
    fclose(fichier);
    
    int ttab = i + 2;
    
    clear();
	endwin();
	WINDOW *f1, *f2, *f3, *f4;
	initscr();
    cbreak();
    noecho();
	start_color();			// initialisation couleurs
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_BLUE,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	
	f1 = subwin(stdscr, ttab + 1 , COLS/4 - 1, (LINES / 2) - (ttab / 2), 0);
	f2 = subwin(stdscr, ttab + 1 , COLS/4 - 1, (LINES / 2) - (ttab / 2), (COLS / 4)); 
	f3 = subwin(stdscr, ttab + 1 , COLS/4 - 1, (LINES / 2) - (ttab / 2), 2 * (COLS / 4)); 
	f4 = subwin(stdscr, ttab + 1 , COLS/4 - 1, (LINES / 2) - (ttab / 2), 3 * (COLS / 4)); 
	
	box(f1, ACS_VLINE, ACS_HLINE);
    box(f2, ACS_VLINE, ACS_HLINE);
    box(f3, ACS_VLINE, ACS_HLINE);
    box(f4, ACS_VLINE, ACS_HLINE);
    
	char *titre1 = "Pseudo";
	char *titre2 = "Niveau";
	char *titre3 = "Score";
	char *titre4 = "Temps";
	
	int t1 = strlen(titre1);
	int t2 = strlen(titre2);
	int t3 = strlen(titre3);
	int t4 = strlen(titre4);
	
    wattrset (f1, COLOR_PAIR(1));
    wattrset (f2, COLOR_PAIR(2));
    wattrset (f3, COLOR_PAIR(3));
    wattrset (f4, COLOR_PAIR(4));
    
    mvwprintw(f1, 1, ((COLS / 4) / 2) - (t1 / 2), titre1);
    mvwprintw(f2, 1, ((COLS / 4) / 2) - (t2 / 2), titre2);
    mvwprintw(f3, 1, ((COLS / 4) / 2) - (t3 / 2), titre3);
    mvwprintw(f4, 1, ((COLS / 4) / 2) - (t4 / 2), titre4);
    
    wattroff (f1, COLOR_PAIR(1));
    wattroff (f2, COLOR_PAIR(2));
    wattroff (f3, COLOR_PAIR(3));
    wattroff (f4, COLOR_PAIR(4));
    
    for(i = 0; i < ttab; i++)
    {
		mvwprintw(f1, i + 2, ((COLS / 4) / 2) - (t11[i] / 2), nom[i]);
		mvwprintw(f2, i + 2, ((COLS / 4) / 2) - (t21[i] / 2), level[i]);
		mvwprintw(f3, i + 2, ((COLS / 4) / 2) - (t31[i] / 2), point[i]);
		mvwprintw(f4, i + 2, ((COLS / 4) / 2) - (t41[i] / 2), temps[i]);
	}
	
	wrefresh(f1);
    wrefresh(f2);
    wrefresh(f3);
    wrefresh(f4);
    
    getch();
    endwin();
    clear();
    menu_princ();
}

void save()
{
	char *save = "files/save.txt";
	FILE *fichier;  														// recupere le fichier ou est stocker le labyrinthe
    fichier=fopen(save,"w");
   
    if(fichier == NULL)
        printf("Erreur lors de l'ouverture du fichier\n"); 					// si le fichier est introuvable, affiche une erreur
    else
    {
		fprintf(fichier,"%d¤%d¤%d¤%d\n",niv, nb_ligne, nb_col, compteur);
	}
    fclose(fichier);
}

void reprendre()
{
	is_reload = 1;
	char *save = "files/save.txt";
	FILE *fichier;  														// recupere le fichier ou est stocker le labyrinthe
    fichier=fopen(save,"r");
   
    if(fichier == NULL)
        printf("Erreur lors de l'ouverture du fichier\n"); 					// si le fichier est introuvable, affiche une erreur
    else
    {
		fscanf(fichier,"%d¤%d¤%d¤%d\n",&niv, &xInit, &yInit, &compteur);
	}
    fclose(fichier);
}
	

void choix_pseudo()
{
	initcurses();
	WINDOW *nickname;
	nickname = newwin(LINES, COLS, 0, 0);
	clear();
	echo();
	char *choix = "Entrez votre pseudo (4 caractère max):";
	char *quit = "Appuyez sur F2 pour afficher le menu";
	int taille = strlen(choix);
	int taille2 = strlen(quit);
	wattron(nickname, A_BOLD);
	mvwprintw(nickname, LINES/2 , (COLS / 2) - (taille / 2), choix);
	wattroff(nickname, A_BOLD);
	mvwprintw(nickname, LINES - 1,(COLS / 2) - (taille2 / 2), quit);
	//getstr(pseudo);
	mvwscanw(nickname, LINES/2 + 1, (COLS / 2) - 2, "%s", &pseudo);
	wrefresh(nickname);
	new_party = 0;
	noecho();
	endwin();
	refresh();
	clear();
}
	
void prog_princ()
{
	choix_lvl();															// Choix de la map.
	initcurses();
	WINDOW *jeu;
	jeu = newwin(LINES, COLS, 0, 0);
	initLab(laby, jeu);														// Initialise le Labyrinthe
	depLab(jeu);															// Deplacement dans le labyrinthe
	clear();
	wrefresh(jeu);
	endwin();
}
