#include <menu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fonctions.h"

int highlight = 0;
int highlight_lvl = 0;


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
    int i;
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
	dep_menu(my_menu, my_menu_win);									// Deplacement dans le menu
	unpost_menu(my_menu);
	free_menu(my_menu);
	for(i = 0; i < n_choices; i++)
			free_item(my_items[i]);
	endwin();
}
