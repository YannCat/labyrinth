#include "fonctions.h"

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
	mvwscanw(nickname, LINES/2 + 1, (COLS / 2) - 2, "%s", &pseudo);
	wrefresh(nickname);
	new_party = 0;
	noecho();
	endwin();
	refresh();
	clear();
}
	
void bienvenue()
{
	initcurses();
	WINDOW *hello;
	hello = newwin(LINES, COLS, 0, 0);
	noecho();
	char *pres = " THE MAZE";
	char *creator = "created by Yann CATALA & Tristan CHARPENTIER";
	int t = strlen(pres);
	int t2 = strlen(creator);
	init_pair(1,COLOR_RED,COLOR_BLACK);
	wattron(hello, COLOR_PAIR(1));
	wattron(hello, A_BOLD);
	mvwprintw(hello, LINES/2 , (COLS / 2) - (t / 2), pres);
	wattroff(hello, COLOR_PAIR(1));
	wattroff(hello, A_BOLD);
	mvwprintw(hello, LINES/2 + 1, (COLS / 2) - (t2 / 2), creator);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	wattron(hello, COLOR_PAIR(2));
	mvwprintw(hello, LINES - 1, 0, "copyright 2017 - 2018");
	wrefresh(hello);
	sleep(3);
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
