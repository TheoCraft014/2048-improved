#include "settime.h"
#include "stare-joc.h"

void afisez_setari_timp(int lin, int col)
{
    mvprintw(lin / 6, col / 2 - strlen("Ultra-Slow") / 2, "Ultra-Slow");
    refresh();

    mvprintw(2 * lin / 6, col / 2 - strlen("Slow") / 2, "Slow");
    refresh();

    mvprintw(3 * lin / 6, col / 2 - strlen("Normal") / 2, "Normal");
    refresh();

    mvprintw(4 * lin / 6, col / 2 - strlen("Fast") / 2, "Fast");
    refresh();

    mvprintw(5 * lin / 6, col / 2 - strlen("Ultra-Fast") / 2, "Ultra-Fast");
}

void setari_timp(struct Joc *gamefile, struct Lungimi lung)
{
    clear();

    char instr[] = "Introduceti timpul de asteptare: ";
    mvprintw(0, lung.colmax / 2 - strlen(instr) / 2, "%s", instr);
    char comand[] = "Apasa ENTER pentru a continua";
    int lungEnter = lung.colmax / 2 - strlen(comand) / 2;

    /*Afisez optiunile*/
    afisez_setari_timp(lung.linmax, lung.colmax);

    int i = 1;
    /*sageata indica optiunea ce va fi aleasa
    initial aceasta este pe prima pozitie (Ultra-Slow)*/
    mvprintw(i * lung.linmax / 6, lung.colmax / 2 - 7, "-> ");
    mvprintw(lung.linmax - 1, lungEnter, "%s", comand);

    while (FOREVER) {
        /*Afisez optiunile*/
        mvprintw(0, lung.colmax / 2 - strlen(instr) / 2, "%s", instr);

        afisez_setari_timp(lung.linmax, lung.colmax);
        mvprintw(lung.linmax - 1, lungEnter, "%s", comand);

        int c = getch();

        /*in functie de sageata apasata, mut pozitia sagetii*/
        switch (c) {
        case KEY_DOWN:
            if (i < 5) {
                i++;
            } else {
                i = 1;
            }
            break;

        case KEY_UP:
            if (i > 1) {
                i--;
            } else {
                i = 2;
            }
            break;
        }
        clear();
        mvprintw(i * lung.linmax / 6, lung.colmax / 2 - 7, "-> ");

        refresh();
        if (c == '\n') {
            break;
        }
    }

    if (i == 1) {
        /*optiunea ultra-slow*/
        gamefile->timp = 400;
    } else if (i == 2) {
        /*optiunea slow*/
        gamefile->timp = 150;
    } else if (i == 3) {
        /*optiunea normal*/
        gamefile->timp = 30;
    } else if (i == 4) {
        /*optiunea fast*/
        gamefile->timp = 15;
    } else if (i == 5) {
        /*optiunea ultra-fast*/
        gamefile->timp = 2;
    }
    clear();
}

/*afisez pe ecran data si ora in timp real */
void timp(int col, int lin, int distantaX, int distantaY)
{
    time_t timp = time(NULL);
    struct tm *time;
    time = localtime(&timp);
    mvprintw(distantaY - 2, distantaX, "ora: %d:%d:%d\n",
             (*time).tm_hour, (*time).tm_min, (*time).tm_sec);

    mvprintw(distantaY - 1, distantaX, "data: %d.%d.%d\n",
             (*time).tm_mday, (*time).tm_mon + 1, (*time).tm_year + 1900);

    refresh();
}