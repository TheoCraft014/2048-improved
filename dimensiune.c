#include "dimensiune.h"
#include <string.h>
#include <ncurses.h>

/*creaza panoul in care ai optiunea de a alege dimensiunea ecranului*/
void setare_dimensiune(struct Lungimi lung)
{
    /*implementez ecranul*/
    noecho();
    char instr[] = "Alegeti dimensiunea ecranului";
    char comand[] = "Apasa ENTER pentru a continua";
    mvprintw(1, lung.colmax - 4 * strlen(instr), "%s", instr);
    int i = 1;
    int lungEnter = lung.colmax / 2 - strlen(comand) / 2;

    mvprintw(lung.linmax / 3, lung.colmax / 2 
            - strlen("MICA") / 2, "MICA");

    mvprintw(2 * lung.linmax / 3, lung.colmax / 2 
            - strlen("MARE") / 2, "MARE");

    /*sageata indica optiunea ce va fi aleasa
    initial aceasta este pe prima pozitie */
    mvprintw(i * lung.linmax / 3, lung.colmax / 2 - 7, "-> ");
    mvprintw(lung.linmax - 1, lungEnter, "%s", comand);

    while (FOREVER) {
        /*implementez ecranul*/
        mvprintw(1, lung.colmax / 2 - strlen(instr) / 2, "%s", instr);
        mvprintw(lung.linmax / 3, lung.colmax / 2 
                - strlen("MICA") / 2, "MICA");
        mvprintw(2 * lung.linmax / 3, lung.colmax / 2 
                - strlen("MARE") / 2, "MARE");
                
        mvprintw(lung.linmax - 1, lungEnter, "%s", comand);

        int c = getch();

        /*in functie de sageata apasata, mut pozitia sagetii*/
        switch (c) {
        case KEY_DOWN:
            if (i == 1) {
                i++;
            } else {
                i = 1;
            }
            break;

        case KEY_UP:
            if (i == 2) {
                i--;
            } else {
                i = 2;
            }
            break;
        }
        clear();
        mvprintw(i * lung.linmax / 3, lung.colmax / 2 - 7, "-> ");

        refresh();
        /*programul se inchide la apasarea tastei ENTER*/
        if (c == '\n') {
            clear();
            break;
        }
    }

    /*dimensiunea coeficientului depinde de pozitie
    i = 1 -> dimensiune mica
    i = 2 -> dimensiune mare */
    lung.coef = i;

    /*se retine intr-un fisier valoarea coeficientului pentru dimensiune*/
    FILE *outputdim = fopen("dimensiune.txt", "w");
    fprintf(outputdim, "%d", lung.coef);
    fclose(outputdim);
}