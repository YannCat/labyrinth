#include <menu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fonctions.h"

int highlight = 0;
int highlight_lvl = 0;
int highlight_game = 0;

/**************************************************************************Fonction commune******************************************************************************************************************/

void suppr_menu(MENU *my_menu, ITEM **my_items, int n_choices)
{
	int i;
	unpost_menu(my_menu);
	free_menu(my_menu);
	for(i = 0; i < n_choices; i++)
			free_item(my_items[i]);
	endwin();
}

void creation_items(int n_choices, char *choices[], ITEM **my_items)
{
	int i;
	for(i = 0; i < n_choices; i++)
	{
		my_items[i] = new_item(choices[i], "");
	}
}

void titre_menu(WINDOW *win, char *titre)
{
	box(win, 0, 0);
	print_in_middle(win, 1, 0, 40, titre, COLOR_PAIR(1));
	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, 38);
	mvwaddch(win, 2, 39, ACS_RTEE);
	//mvprintw(LINES - 1, 0, "F2 pour quitter");
	refresh();
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int taille, x, y;
	float temp;
	
	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	taille = strlen(string);
	temp = (width - taille)/ 2;
	x = startx + temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}


/***********************************************************************************Menu Principale**********************************************************************************************************/

void menu_princ()
{	
	char *choices[] = {
                        "          Nouvelle partie             ",
                        "             Reprendre                ",
                        "            Choisir map               ",
                        "           Configuration              ",
                        "               Score                  ",
                        "              Quitter                 ",
                        (char *)NULL,
                  };				
	MENU *my_menu;
    WINDOW *my_menu_win;
    int n_choices = ARRAY_SIZE(choices);
    ITEM **my_items = calloc(n_choices, sizeof(ITEM *));
    char *titre = "Menu Labyrinthe";
	
	initcurses();													// Initialize curses
    creation_items(n_choices, choices, my_items);					// Creation des choix du menu
    my_menu = new_menu(my_items);									// Creation du menu 
	my_menu_win = newwin(10, 40, LINES/2 - 5, COLS/2 - 19);
	keypad(my_menu_win, TRUE);
	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
	titre_menu(my_menu_win, titre);									// Affichage du titre du menu
	post_menu(my_menu);
	wrefresh(my_menu_win);
	dep_menu(my_menu, my_menu_win, my_items, n_choices);									// Deplacement dans le menu
	suppr_menu(my_menu, my_items, n_choices);
	endwin();
}

void dep_menu(MENU *my_menu, WINDOW *win, ITEM **my_items, int n_choices)
{
	int c;
	while(1)						// avant : while(c != KEY_F(2))
	{
			c = getch(); 
		    switch(c)
	        {	
			case KEY_DOWN:
				if (highlight < 5)
				{
					highlight ++;
					menu_driver(my_menu, REQ_DOWN_ITEM);
				}
				
			break;
			
			case KEY_UP:
				if (highlight > 0)	
				{	
					menu_driver(my_menu, REQ_UP_ITEM);
					highlight --;
				}
			break;
			
			case ENTER: /* Enter */
				choix_menu(my_menu, my_items, n_choices);
			break;
			}
                wrefresh(win);
	}	

}

void choix_menu(MENU *my_menu, ITEM **my_items, int n_choices)
{
	switch (highlight) 
	{	
	case 0 :			//Lancer le jeu
		suppr_menu(my_menu, my_items, n_choices);
		clear();
		refresh();
		new_party = 1;
		prog_princ();
	break;
	case 1 :			//Reprendre
		suppr_menu(my_menu, my_items, n_choices);
		clear();
		refresh();
		reprendre();
		prog_princ();
	break;	
	case 2 :			//Choisir map
		suppr_menu(my_menu, my_items, n_choices);
		clear();
		refresh();
		menu_lvl();
	break;	
	case 3 :			//Configuration
		suppr_menu(my_menu, my_items, n_choices);
		clear();
		refresh();
		endwin();
		exit(0);
	break;	
	case 4 :			//Score
		suppr_menu(my_menu, my_items, n_choices);
		clear();
		refresh();
		affich_score();
	break;
	case 5 :			//Quitter
		suppr_menu(my_menu, my_items, n_choices);
		clear();
		refresh();
		endwin();
		exit(0);
	break;				
	}
}

/************************************************************************************Menu Niveau************************************************************************************************************/

void menu_lvl()
{	
	char *choiceslvl[] = {
                        "               Level 1                 ",
                        "               Level 2                 ", 
                        "               Level 3                 ",
                        "               Level 4                 ",
                        "               Quitter                 ",
                        (char *)NULL,
                  };				
	MENU *my_menu_lvl;
    WINDOW *my_menu_win_lvl;
    int lvl_choices = ARRAY_SIZE(choiceslvl);
    ITEM **my_items_lvl = calloc(lvl_choices, sizeof(ITEM *));
    char *titre_lvl = "Choix du Niveau";
	
	initcurses();													// Initialize curses
    creation_items(lvl_choices, choiceslvl, my_items_lvl);					// Creation des choix du menu
    my_menu_lvl = new_menu(my_items_lvl);									// Creation du menu level
	my_menu_win_lvl = newwin(9, 40, LINES/2 - 5, COLS/2 - 19);			// ( hauteur,largeur,ypos,xpos)
	keypad(my_menu_win_lvl, TRUE);
	set_menu_win(my_menu_lvl, my_menu_win_lvl);
	set_menu_sub(my_menu_lvl, derwin(my_menu_win_lvl, 5, 38, 3, 1));
	titre_menu(my_menu_win_lvl, titre_lvl);									// Affichage du titre du menu
	post_menu(my_menu_lvl);
	wrefresh(my_menu_win_lvl);
	dep_menu_lvl(my_menu_lvl, my_menu_win_lvl, my_items_lvl, lvl_choices);									// Deplacement dans le menu
	suppr_menu(my_menu_lvl, my_items_lvl, lvl_choices);
}

void choix_menu_lvl(MENU *my_menu_lvl, ITEM **my_items_lvl, int lvl_choices)
{
	switch (highlight_lvl) 
	{	
	case 0 :			//Map 1
		suppr_menu(my_menu_lvl, my_items_lvl, lvl_choices);
		clear();
		refresh();
		niv = 0;
		new_party = 1;
		prog_princ();
	break;
	case 1 :			//Map 2
		suppr_menu(my_menu_lvl, my_items_lvl, lvl_choices);
		clear();
		refresh();
		niv = 1;
		new_party = 1;
		prog_princ();
	break;	
	case 2 :			//Map 3
		suppr_menu(my_menu_lvl, my_items_lvl, lvl_choices);
		clear();
		refresh();
		niv = 2;
		new_party = 1;
		prog_princ();
	break;	
	case 3 :			//Map 4
		suppr_menu(my_menu_lvl, my_items_lvl, lvl_choices);
		clear();
		refresh();
		niv = 3;
		new_party = 1;
		prog_princ();
	break;	
	case 4 :			//Quitter
		suppr_menu(my_menu_lvl, my_items_lvl, lvl_choices);
		clear();
		refresh();
		endwin();
		exit(0);
	break;			
	}
}

void dep_menu_lvl(MENU *my_menu_lvl, WINDOW *win, ITEM **my_items_lvl, int lvl_choices)
{
	int c;
	while(1)						// avant : while(c != KEY_F(2))
	{
		c = getch(); 
		switch(c)
			{	
			case KEY_DOWN:
				menu_driver(my_menu_lvl, REQ_DOWN_ITEM);
				if (highlight_lvl < 4)				highlight_lvl ++;
				
			break;
			
			case KEY_UP:
				menu_driver(my_menu_lvl, REQ_UP_ITEM);
				if (highlight_lvl > 0)				highlight_lvl --;
			break;
			
			case ENTER: /* Enter */
				choix_menu_lvl(my_menu_lvl, my_items_lvl, lvl_choices);
			break;
			}
		wrefresh(win);
	}	
}

/************************************************************************Menu en Jeu*************************************************************************************************************************/

void menu_game()
{	
	char *choicesgame[] = {
                        "              Reprendre                ",
                        "               Quitter                 ",
                        (char *)NULL,
                  };				
	MENU *my_menu_game;
    WINDOW *my_menu_win_game;
    int game_choices = ARRAY_SIZE(choicesgame);
    ITEM **my_items_game = calloc(game_choices, sizeof(ITEM *));
    char *titre_game = "Pause";
	
	initcurses();													// Initialize curses
    creation_items(game_choices, choicesgame, my_items_game);					// Creation des choix du menu
    my_menu_game = new_menu(my_items_game);									// Creation du menu level
	my_menu_win_game = newwin(6, 40, LINES/2 - 5, COLS/2 - 19);			// ( hauteur,largeur,ypos,xpos)
	keypad(my_menu_win_game, TRUE);
	set_menu_win(my_menu_game, my_menu_win_game);
	set_menu_sub(my_menu_game, derwin(my_menu_win_game, 3, 38, 3, 1));
	titre_menu(my_menu_win_game, titre_game);									// Affichage du titre du menu
	post_menu(my_menu_game);
	wrefresh(my_menu_win_game);
	dep_menu_game(my_menu_game, my_menu_win_game, my_items_game, game_choices);									// Deplacement dans le menu
	suppr_menu(my_menu_game, my_items_game, game_choices);
}

void choix_menu_game(MENU *my_menu_game, ITEM **my_items_game, int game_choices)
{
	switch (highlight_game) 
	{	
	case 0 :			// Reprendre
		suppr_menu(my_menu_game, my_items_game, game_choices);
		clear();
		refresh();
		reprendre();
		prog_princ();
	break;
	case 1 :			// Quitter
		suppr_menu(my_menu_game, my_items_game, game_choices);
		clear();
		refresh();
		endwin();
		exit(0);
	break;			
	}
}

void dep_menu_game(MENU *my_menu_game, WINDOW *win, ITEM **my_items_game, int game_choices)
{
	int c;
	while(1)						// avant : while(c != KEY_F(2))
	{
		c = getch(); 
		switch(c)
			{	
			case KEY_DOWN:
				menu_driver(my_menu_game, REQ_DOWN_ITEM);
				if (highlight_game < 1)				highlight_game ++;
				
			break;
			
			case KEY_UP:
				menu_driver(my_menu_game, REQ_UP_ITEM);
				if (highlight_game > 0)				highlight_game --;
			break;
			
			case ENTER: /* Enter */
				choix_menu_game(my_menu_game, my_items_game, game_choices);
			break;
			}
		wrefresh(win);
	}	
}
