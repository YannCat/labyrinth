#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "fonctions.h"

#define ENTER 10
#define ESCAPE 27
#define xmax 41
#define ymax 21

int main()
{
    int choice;
    WINDOW *menubar,*messagebar;
    initColors(); //initalisation des couleurs
    bkgd(COLOR_PAIR(1));
    menubar=subwin(stdscr,1,42,0,0); //creation barre de menu
    messagebar=subwin(stdscr,1,79,23,1);//creation barre de message (en bas de l'ecran)
    drawBar(menubar);
    refresh();

	int selected_item;
    FILE *fsave;
    char tab[ymax][xmax];
    int nb_ligne,nb_col;
    int key=0;;
    int x=0, y=0;// initialisation de la position
    do 
    {
        WINDOW **menu_items;
        choice=getch(); //recupèration de la touche entrée 
        werase(messagebar);
        wrefresh(messagebar);
        if (choice==KEY_F(2)) //si on appuie sur F2
        {
            menu_items=drawMenu(0);
            selected_item=browseMenu(menu_items,9,0); //on crée un menu
            delMenu(menu_items,10);

            switch (selected_item)
            {
                case 0 : // nouvelle partie
                {
                    fsave=fopen("fichier.txt","r"); //ouvrir fichier sauvegarde labyrinthe 
                    if(fsave == NULL) //si pas de fichier
                        printf("Erreur lors de l'ouverture du fichier\n"); //afficher erreur
                    else
                    {
                        initLab(); //init a 1
                        initColors();
                        while (!feof(fsave)) // tant que different de fin du fichier
                        {
                            for(nb_ligne=1;nb_ligne<=ymax;nb_ligne++)
                            {
                                for(nb_col=0;nb_col<=xmax;nb_col++)
                                {
                                    fscanf(fsave,"%c",&tab[nb_ligne][nb_col]); //récupération ligne
                                    switch(tab[nb_ligne][nb_col])
                                    {
                                        case '0'://couloir
                                        {
                                            attron(COLOR_PAIR(4)); //prendre couleur
                                            mvprintw(nb_ligne,nb_col," ");
                                            attroff(COLOR_PAIR(4)); //lacher couleur
                                            break;
                                        }
                                        case '1'://mur
                                        {
                                            attron(COLOR_PAIR(6)); //prendre couleur
                                            mvprintw(nb_ligne,nb_col," ");
                                            attroff(COLOR_PAIR(6)); //lacher couleur
                                            break;
                                        }
                                        case '2'://entree
                                        {
                                            attron(COLOR_PAIR(8)); //prendre couleur
                                            mvprintw(nb_ligne,nb_col," ");
                                            attroff(COLOR_PAIR(8)); //lacher couleur
                                            x = nb_ligne;
                                            y = nb_col;
                                            break;
                                        }
                                        case '3'://sortie
                                        {
                                            attron(COLOR_PAIR(7)); //prendre couleur
                                            mvprintw(nb_ligne,nb_col," ");
                                            attroff(COLOR_PAIR(7)); //lacher couleur
                                            break;
                                        }
                                    }
                                    refresh();       
                                }
                            }
                        }
                        
                        fclose(fsave); //fermeture fichier
                        keypad(stdscr,TRUE);
                        curs_set(0);//invisible cursor
                        nb_ligne= x;//init position x départ curseur 
                        nb_col= y; //init position y départ curseur
                        move(nb_ligne,nb_col); //déplacement a position départ 
                        while ((key != 'q') && (tab[nb_ligne][nb_col] != '3')) // tant que different de 'q' et pas à l'arrivée
                        {
                            wattrset (stdscr, COLOR_PAIR(5));
                            switch (key) //selon la touche
                            {
                                case KEY_RIGHT:
                                        if (xmax - 1 > nb_col) // si pas au max 
                                        {
                                            if (tab[nb_ligne][nb_col +1 ] != '1') // si couloir 
                                            {
                                                addch (' ');
                                                nb_col ++;
                                                moveCursor(nb_ligne,nb_col);
                                            }
                                        }
                                break;
                                case KEY_LEFT:
                                       if (0 < nb_col) // si pas au min 
                                       {
                                            if (tab[nb_ligne][nb_col - 1] != '1')// si couloir
                                            {
                                                addch (' ');
                                                nb_col --;
                                                moveCursor(nb_ligne,nb_col);                       
                                            }
                                       }
                                break;
                                case KEY_DOWN:
                                        if (ymax - 1 > nb_ligne) // si pas au max
                                        {
                                            if (tab[nb_ligne + 1][nb_col] != '1') // si couloir
                                            {
                                                addch (' ');
                                                nb_ligne ++;
                                                moveCursor(nb_ligne,nb_col);
                                            }
                                        }
                                break;
                                case KEY_UP:
                                        if (0< nb_ligne) // si pas au min 
                                        {
                                            if (tab[nb_ligne - 1][nb_col] != '1') // si couloir
                                            {
                                                addch (' ');
                                                nb_ligne --;
                                                moveCursor(nb_ligne,nb_col);
                                            }
                                        }
                                break;
                            }
                            key=getch(); // key recoit la touche clavier appuyé
                            move(nb_ligne,nb_col);
                            refresh();
                        }
                    }
                    wprintw(messagebar,"You have selected menu item %d.",selected_item+1);
                    break;
                }
                case 1 : //load game
                {
                    fsave=fopen("fichier.txt","r"); // ouverture en mode lecture
                    if(fsave == NULL)
                        printf("Erreur lors de l'ouverture du fichier\n");
                    else
                    {
                        initLab();
                        initColors();
                        FILE *fparam;
                        fparam=fopen("sauvegardeLab.txt","r"); //ouverture fichier en mode lecture 
                        if(fparam == NULL)
                            printf("Erreur lors de l'ouverture du fichier\n");
                        else
                        {
                            fscanf(fparam, "%d %d",&x,&y); //recup position dans fichier
                        }
                        while (!feof(fsave))  //tant que different de fin de fichier 
                        {
                            for(nb_ligne=1;nb_ligne<=ymax;nb_ligne++)
                            {
                                for(nb_col=0;nb_col<=xmax;nb_col++)
                                {
                                    fscanf(fsave,"%c",&tab[nb_ligne][nb_col]);//récupération d'une ligne 
                                    switch(tab[nb_ligne][nb_col])
                                    {
                                        case '0'://couloir
                                        {
                                            if(nb_ligne==x && nb_col==y)
                                            {
                                                attron(COLOR_PAIR(8)); //prendre couleur
                                                mvprintw(nb_ligne,nb_col," ");
                                                attroff(COLOR_PAIR(8)); //lacher couleur
                                            }
                                            else
                                            {
                                                attron(COLOR_PAIR(4)); //prendre couleur
                                                mvprintw(nb_ligne,nb_col," ");
                                                attroff(COLOR_PAIR(4)); //lacher couleur
                                            }
                                            break;
                                        }
                                        case '1'://mur
                                        {
                                            attron(COLOR_PAIR(6)); //prendre couleur
                                            mvprintw(nb_ligne,nb_col," ");
                                            attroff(COLOR_PAIR(6)); //lacher couleur
                                            break;
                                        }
                                        case '2'://entree devenu couloir 
                                        {
                                            attron(COLOR_PAIR(6)); //prendre couleur
                                            mvprintw(nb_ligne,nb_col," ");
                                            attroff(COLOR_PAIR(6)); //lacher couleur
                                            break;
                                        }
                                        case '3'://sortie
                                        {
                                            attron(COLOR_PAIR(7)); //prendre couleur
                                            mvprintw(nb_ligne,nb_col," ");
                                            attroff(COLOR_PAIR(7)); //lacher couleur
                                            break;
                                        }
                                    }
                                    refresh();       
                                }
                            }
                        }
                        fclose(fsave);
                        keypad(stdscr,TRUE);
                        curs_set(0);//invisible curseur
                        nb_ligne= x; //init position x a la valeur récupérée
                        nb_col= y;//init position x a la valeur récupérée
                        move(nb_ligne,nb_col);
                        while ((key != 'q') && (tab[nb_ligne][nb_col] != '3'))
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
                    }
                    wprintw(messagebar,"You have selected menu item %d.",selected_item+1);
                    break;
                }

                case 2 : //save game
                {
                    fsave=fopen("sauvegardeLab.txt","w"); //ouvrir fichier sauvegarde
                    if(fsave == NULL) //si pas possible
                        printf("Erreur lors de l'ouverture du fichier\n"); //afficher erreur
                    else
                    {
                        fprintf(fsave,"%d %d\n", nb_ligne, nb_col); //ecrire x et y
                        fclose(fsave); //fermer fichier
                    }
                    wprintw(messagebar,"You have selected menu item %d.",selected_item+1); //afficher message sur la barre de message
                    break;
                }

                case 3 : //load lab1
                { 
                    break; //non implementée 
                }
                case 4 : //load lab2
                { 
                    break; //non implementée 
                }
                case 5 : //load lab3
                { 
                    break; //non implementée 
                }
                case 6 : //load lab4
                { 
                    break; //non implementée 
                }
                default : 
                    wprintw(messagebar,"You haven't selected any item."); //message d'erreur
            }
            touchwin(stdscr);
            refresh();    
        } 
    } while (selected_item != 7); //si 7 alors quitter
    delwin(menubar); //supprimer barre menu
    delwin(messagebar); //supprimer barre de message
    endwin(); //fermer proprement la fenêtre
    return 0;
}
