#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include "dimensiune.h"
#include "stare-joc.h"
#include "colors.h"
#include "mutari.h"
#include "utilitare.h"
#include "settime.h"
#include "saves.h"

/*alege random intre 2 si 4 cu 75% sanse sa returneze valoarea 2*/
int randval()
{
    int nr = rand() % 4;
    if (nr == 0) {
        nr = 4;
    } else {
        nr = 2;
    }

    return nr;
}

void generezrandom(struct Joc *gamefile, struct Lungimi lung)
{
    if (gamefile->nrValabil > 0) {
        int i, val, indexrand;
        /*aleg aleatoriu valoarea matricei*/
        val = randval();

        /*aleg un numar aleatoriu dintre coloanele libere*/
        indexrand = rand() % (gamefile->nrValabil);
        int lin, col;
        lin = gamefile->verific[indexrand][0];
        col = gamefile->verific[indexrand][1];

        /*elimin coloana respectiva din lista coloanelor libere*/
        for (i = indexrand; i < gamefile->nrValabil - 1; i++) {
            gamefile->verific[i][0] = gamefile->verific[i + 1][0];
            gamefile->verific[i][1] = gamefile->verific[i + 1][1];
        }
        /*numarul de coloane valabile scade*/
        (gamefile->nrValabil)--;

        /*ofer valoarea random casutei corespunzatoare din matrice
        aceasta va avea valoare negativa pentru a afisa pe ecran ca este
        valoarea nou aparuta in joc*/
        gamefile->matrix[lin][col] = (-1) * val;
    }
}

void titlu(int col, int lin)
{
    char titlu[] = "~~~2048 GAME~~~";
    mvprintw(0, col / 2 - strlen(titlu) / 2, "%s", titlu);
    refresh();

    char instr[] = "Apasa orice tasta pentru a continua";
    mvprintw(lin - 4, col / 2 - strlen(instr) / 2, "%s", instr);
    refresh();
    getch();
    clear();
}

void creezJoc(struct Lungimi lung, struct Joc *gamefile)
{
    clear();
    /*indice pentru separarea liniilor*/
    int pas;

    attron(COLOR_PAIR(1));

    /*creez liniile verticale*/
    for (pas = 0; pas <= DIM_TABEL; pas++) {
        mvvline(lung.distantaY, 8 * pas * lung.coef + lung.distantaX,
                '|', MARIME_VERTICALA * lung.coef);
    }
    refresh();

    /*creez liniile orizontale*/
    for (int pas = 0; pas <= DIM_TABEL; pas++) {
        mvhline(lung.distantaY + 4 * pas * lung.coef, lung.distantaX, '=',
                MARIME_ORIZONTALA * lung.coef);
    }

    attroff(COLOR_PAIR(1));
    refresh();

    /*punctajul*/
    int lungpct = strlen("Punctaj:") / 2;
    mvprintw(lung.distantaY, lung.distantaX / 2 - lungpct, "Punctaj:");
    mvprintw(lung.distantaY + 1, lung.distantaX / 2 - lungpct, "%d ",
             gamefile->punctaj);

    refresh();

    /*highscore*/
    lungpct = strlen("Highscore:") / 2;
    mvprintw(lung.distantaY +3, lung.distantaX / 2 - lungpct, "Highscore");
    mvprintw(lung.distantaY + 4, lung.distantaX / 2 - lungpct, "%d ", 
             scor_maxim() );

    /*variabila de umplutura pentru punctaje*/
    int p;
    /*variabila pseudobooleana care verifica
    daca 2 matrici sunt identice*/
    int seamana;

    // distanta de la marginea dreapta pana la textul legendei
    int spatiuMT = lung.distantaX + MARIME_ORIZONTALA * lung.coef +
                   lung.dMT * lung.coef;

    /*declar matricile de copie*/
    int copie[DIM_TABEL][DIM_TABEL];
    int copie2[DIM_TABEL][DIM_TABEL];

    /*implementez legenda pe ecran */
    mvprintw(lung.linmax / 6, spatiuMT, "Comenzi:");

    /*pentru fiecare directie verific daca mutarea este valida
    daca mutarea nu este valida, comanda nu se va afisa pe ecran
    - verificarea are loc pentru fiecare directie*/
    copiez(gamefile->matrix, copie);
    copiez(gamefile->matrix, copie2);
    actualizezrandom(copie);
    actualizezrandom(copie2);
    p = 0;
    nord(copie, &p);
    seamana = asemanare(copie2, copie);
    if (seamana == 0) {
        mvprintw(lung.linmax / 6 + 1, spatiuMT, "W: mutare sus");
    }

    copiez(gamefile->matrix, copie);
    copiez(gamefile->matrix, copie2);
    actualizezrandom(copie);
    actualizezrandom(copie2);
    p = 0;
    sud(copie, &p);
    seamana = asemanare(copie2, copie);
    if (seamana == 0) {
        mvprintw(lung.linmax / 6 + 2, spatiuMT, "S: mutare jos");
    }

    copiez(gamefile->matrix, copie);
    copiez(gamefile->matrix, copie2);
    actualizezrandom(copie);
    actualizezrandom(copie2);
    p = 0;
    vest(copie, &p);
    seamana = asemanare(copie2, copie);
    if (seamana == 0) {
        mvprintw(lung.linmax / 6 + 3, spatiuMT, "D: mutare dreapta");
    }

    copiez(gamefile->matrix, copie);
    copiez(gamefile->matrix, copie2);
    actualizezrandom(copie);
    actualizezrandom(copie2);
    p = 0;
    est(copie, &p);
    seamana = asemanare(copie2, copie);
    if (seamana == 0) {
        mvprintw(lung.linmax / 6 + 4, spatiuMT, "A: mutare stanga");
    }

    mvprintw(lung.linmax / 6 + 5, spatiuMT, "Q: meniu");

    refresh();
}

void afisez_meniu(int col, int lin)
{
    char menu[] = "------MENU------";
    mvprintw(0, col / 2 - strlen(menu) / 2, "%s", menu);
    refresh();

    char instruct[] = "Apasa ENTER pentru a continua";
    int lungEnter = col / 2 - strlen(instruct) / 2;
    mvprintw(lin - 1, lungEnter, "%s", instruct);

    mvprintw(lin / 7, col / 2 - strlen("New Game") / 2, "New Game");
    refresh();

    mvprintw(2 * lin / 7, col / 2 - strlen("Resume") / 2, "Resume");
    refresh();

    mvprintw(3 * lin / 7, col / 2 - strlen("Save") / 2, "Save");
    refresh();

    mvprintw(4 * lin / 7, col / 2 - strlen("Load") / 2, "Load");
    refresh();

    mvprintw(5 * lin / 7, col / 2 - strlen("Settings") / 2, "Settings");
    refresh();

    mvprintw(6 * lin / 7, col / 2 - strlen("Quit") / 2, "Quit");
    refresh();
}

void newGame(struct Joc *gamefile, struct Lungimi lung)
{
    int i, j;
    /*initializez nr de casute valabile si punctajul cu zero */
    gamefile->nrValabil = 0;
    gamefile->punctaj = 0;

    /*introduc in matricea verific[][] coordonatele casutelor
    care au valoarea zero astfel retin casutele disponibile 
    pentru adaugarea unui element random*/
    for (i = 0; i < DIM_TABEL; i++) {
        for (j = 0; j < DIM_TABEL; j++) {
            gamefile->matrix[i][j] = 0;
            gamefile->verific[gamefile->nrValabil][0] = i;
            gamefile->verific[gamefile->nrValabil][1] = j;
            gamefile->nrValabil++;
        }
    }

    /*indica rularea jocului*/
    gamefile->game_over = MERGE;

    /*la inceputul jocului sunt doua valori generate random*/
    generezrandom(gamefile, lung);
    generezrandom(gamefile, lung);
}

void Game(struct Joc *gamefile, WINDOW *window, struct Lungimi lung)
{
    int i, j;
    /*generez jocul*/
    nodelay(window, true);
    creezJoc(lung, gamefile);
    timp(lung.colmax, lung.linmax, lung.distantaX, lung.distantaY);
    transpun(gamefile->matrix, lung);

    int timptrecut = 0;
    while (FOREVER) {
        timptrecut++;

        for (i = 0; i < DIM_TABEL; i++)
            for (j = 0; j < DIM_TABEL; j++)
                if (gamefile->matrix[i][j] == 2048) {
                    gamefile->game_over = CASTIGAT;
                    break;
                }

        /*opresc jocul daca a fost castigat jocul*/
        if (gamefile->game_over == CASTIGAT) {
            creezJoc(lung, gamefile);
            transpun(gamefile->matrix, lung);
            sleep(5);
            clear();
            break;
        }

        int tasta = getch();

        timp(lung.colmax, lung.linmax, lung.distantaX, lung.distantaY);
        transpun(gamefile->matrix, lung);
        // pun delay de 100 microsecunde
        napms(100);
        refresh();

        /*execut o mutare automata la trecerea timpului*/
        if (timptrecut == gamefile->timp) {
            actualizezrandom(gamefile->matrix);
            mutAutomat(gamefile);
            transpun(gamefile->matrix, lung);
            actualizez(gamefile->matrix, gamefile->verific,
                       &gamefile->nrValabil);
            generezrandom(gamefile, lung);
            creezJoc(lung, gamefile);
            refresh();

            timptrecut = 0;
        }

        /*daca matricea nu mai are spatii goale, verific
        daca mai pot avea loc mutari, in caz contrar se incheie jocul*/

        if (verificSpatiu(gamefile->matrix) == 0) {
            int copie[DIM_TABEL][DIM_TABEL];
            int copie2[DIM_TABEL][DIM_TABEL];

            /* matricea copie2 retine valoarea nemodificata a lui matrix
            insa cu toate valorile pozitive ;

            Variabila de umplutura este pentru functiile de directie
            - calculeaza punctajul

            prin matricile de copie ma asigur ca ambele matrici au valori
            pozitive pentru executia corespunzatoare a mutarilor */
            int p = 0;
            copiez(gamefile->matrix, copie);
            copiez(gamefile->matrix, copie2);
            actualizezrandom(copie);
            actualizezrandom(copie2);
            nord(copie, &p);
            /*matricea copie va retine valoarea lui matrix dupa mutare apoi
            se va compara cu copie2 */
            int nordIdentic = asemanare(copie2, copie);

            /*procedez analog pentru fiecare directie*/
            copiez(gamefile->matrix, copie);
            copiez(gamefile->matrix, copie2);
            actualizezrandom(copie);
            actualizezrandom(copie2);
            sud(copie, &p);
            int sudIdentic = asemanare(copie2, copie);

            copiez(gamefile->matrix, copie);
            copiez(gamefile->matrix, copie2);
            actualizezrandom(copie);
            actualizezrandom(copie2);
            vest(copie, &p);
            int vestIdentic = asemanare(copie2, copie);

            copiez(gamefile->matrix, copie);
            copiez(gamefile->matrix, copie2);
            actualizezrandom(copie);
            actualizezrandom(copie2);
            est(copie, &p);
            int estIdentic = asemanare(copie2, copie);

            /*verifica daca au fost posibile mutari
            functia asemanare() verifica daca exista asemanare intre matricea
            initiala si matricea dupa fiecare mutare

            daca toate asemanarile au val 1 inseamna ca matricea nu mai
            poate avea mutari */
            gamefile->game_over = nordIdentic + sudIdentic +
                                  estIdentic + vestIdentic;
            if (gamefile->game_over == PIERDUT) {
                creezJoc(lung, gamefile);
                transpun(gamefile->matrix, lung);
                // jocul a fost pierdut, se inchide
                sleep(5);
                clear();
                break;
            }
        }

        // verific comenzile valide
        if (tolower(tasta) == 'q') {
            // intrerup jocul si intru in meniu
            clear();
            nodelay(window, false);
            break;
        } else {
            /* matricea copie2 retine valoarea nemodificata a lui matrix
             insa cu toate valorile pozitive
             matricea copie va retine valoarea lui matrix dupa mutare apoi se
             va compara cu copie2
             deoarece matricea are valori negative (simbol asociat
             generarii random) mutarile trebuie sa aiba loc intre valori
             strict pozitive
             */
            int copie[DIM_TABEL][DIM_TABEL];
            int copie2[DIM_TABEL][DIM_TABEL];
            switch (tolower(tasta))
            {
                case 'w':
                case KEY_UP:

                /*retin valorile matricei*/
                copiez(gamefile->matrix, copie);
                copiez(gamefile->matrix, copie2);
                /*le ofer valori pozitive*/
                actualizezrandom(copie);
                actualizezrandom(copie2);
                int p = 0;
                /*efectuez o mutare matricei copie*/
                nord(copie, &p);
                /*verific daca matricile sunt asemanatoare, in caz contrar
                mutarea e valida*/
                int seamana = asemanare(copie2, copie);
                if (seamana == 0) {
                    /*actualizez matricea sa nu mai fie valoarea
                    random evidentiata*/
                    actualizezrandom(gamefile->matrix);
                    /*execut functia*/
                    nord(gamefile->matrix, &gamefile->punctaj);
                    /*reactualizez ecranul*/
                    transpun(gamefile->matrix, lung);
                    actualizez(gamefile->matrix, gamefile->verific,
                               &gamefile->nrValabil);
                    generezrandom(gamefile, lung);
                    creezJoc(lung, gamefile);
                    /*resetez timpul trecut*/
                    timptrecut = 0;
                    refresh();
                }
                break;

                /*acelasi algoritm are loc pentru fiecare tasta apasata,
                difera doar directia/sensul mutarii*/
                case 'a':
                case KEY_LEFT:

                    copiez(gamefile->matrix, copie);
                    copiez(gamefile->matrix, copie2);
                    actualizezrandom(copie);
                    actualizezrandom(copie2);
                    p = 0;
                    vest(copie, &p);
                    seamana = asemanare(copie2, copie);
                    if (seamana == 0)
                    {
                        actualizezrandom(gamefile->matrix);
                        vest(gamefile->matrix, &gamefile->punctaj);
                        transpun(gamefile->matrix, lung);
                        actualizez(gamefile->matrix, gamefile->verific,
                                &gamefile->nrValabil);
                        generezrandom(gamefile, lung);
                        creezJoc(lung, gamefile);
                        timptrecut = 0;
                        refresh();
                    }
                break;

                case 's':
                case KEY_DOWN:

                    copiez(gamefile->matrix, copie);
                    copiez(gamefile->matrix, copie2);
                    actualizezrandom(copie);
                    actualizezrandom(copie2);
                    p = 0;
                    sud(copie, &p);
                    seamana = asemanare(copie2, copie);
                    if (seamana == 0)
                    {
                        actualizezrandom(gamefile->matrix);
                        sud(gamefile->matrix, &gamefile->punctaj);
                        transpun(gamefile->matrix, lung);
                        actualizez(gamefile->matrix, gamefile->verific,
                                &gamefile->nrValabil);
                        generezrandom(gamefile, lung);
                        creezJoc(lung, gamefile);
                        timptrecut = 0;
                        refresh();
                    }
                break;

                case 'd':
                case KEY_RIGHT:

                    copiez(gamefile->matrix, copie);
                    copiez(gamefile->matrix, copie2);
                    actualizezrandom(copie);
                    actualizezrandom(copie2);
                    p = 0;
                    est(copie, &p);
                    seamana = asemanare(copie2, copie);
                    if (seamana == 0)
                    {
                        actualizezrandom(gamefile->matrix);
                        est(gamefile->matrix, &gamefile->punctaj);
                        transpun(gamefile->matrix, lung);
                        actualizez(gamefile->matrix, gamefile->verific,
                                    &gamefile->nrValabil);
                        generezrandom(gamefile, lung);
                        creezJoc(lung, gamefile);
                        timptrecut = 0;
                        refresh();
                    }
                break;
            }
        }
    }

    if (gamefile->game_over == PIERDUT) {
        clear();
        while (FOREVER)
        {
            nodelay(window, false);
            int lungmsj1 = strlen("GAME OVER") / 2;
            mvprintw(lung.linmax / 2, lung.colmax / 2 - lungmsj1,
                     "GAME OVER");
            int lungmsj = strlen("Apasa ENTER pentru a iesi") / 2;
            mvprintw(lung.linmax - 1, lung.colmax / 2 - lungmsj / 2,
                     "Apasa ENTER pentru a iesi");
            refresh();
            char apas = getch();
            if (apas == '\n') {
                clear();
                savescore(gamefile);
                break;
            }
        }
    } else {
        if (gamefile->game_over == CASTIGAT) {
            clear();
            while (FOREVER) {
                nodelay(window, false);

                char mesaj[] = "AI CASTIGAT!!";
                int lunghol = lung.colmax / 2 - strlen(mesaj)/ 2 ;
                mvprintw(lung.linmax / 2, lunghol, "%s", mesaj);

                int lungmsj = strlen("Apasa ENTER pentru a iesi") / 2;
                mvprintw(lung.linmax - 1, lung.colmax / 2 - lungmsj / 2,
                         "Apasa ENTER pentru a iesi");
                refresh();
                char apas = getch();
                if (apas == '\n') {
                    clear();
                    savescore(gamefile);
                    break;
                }
            }
        }
    }
}

void menu(struct Joc *gamefile, struct Lungimi lung, WINDOW *window)
{
    /* meniul depinde de dimensiunile maxime
    ale nr de linii si coloane */

    /*tipul textului ce va fi afisat pe ecran*/
    attron(A_BOLD);
    /*afisez instructiunea*/
    noecho();
    
    /*afisez continutul meniului*/
    afisez_meniu(lung.colmax, lung.linmax);

    int i = 1;
    /*sageata indica optiunea ce va fi aleasa
    initial aceasta este pe prima pozitie (New Game)*/
    mvprintw(i * lung.linmax / 7, lung.colmax / 2 - 7, "-> ");

    while (FOREVER) {
        afisez_meniu(lung.colmax, lung.linmax);
        
        int tasta = getch();

        /*in functie de sageata apasata, mut pozitia sagetii*/
        switch (tasta) {
        case KEY_DOWN:
            if (i < 6) {
                i++;
            } else {
                i = 1;
            }
            break;

        case KEY_UP:
            if (i > 1) {
                i--;
            } else {
                i = 6;
            }
            break;
        }
        clear();
        mvprintw(i * lung.linmax / 7, lung.colmax / 2 - 7, "-> ");

        refresh();
        if (tasta == '\n') {
            break;
        }
    }

    /*optiuni in functie de pozitie
    i = 1 - New Game
    i = 2 - Resume
    i = 3 - Save
    i = 4 - Load
    i = 5 - Settings
    i = 6 - Quit */
    if (i == 6) {
        /*putem salva jocul doar daca ruleaza*/
        if(gamefile->game_over == MERGE) {
            quit(gamefile, lung);
        }
        endwin();
        exit(0);
    } else if (i == 5) {
        clear();
        setari_timp(gamefile, lung);
        menu(gamefile, lung, window);
    } else if(i == 3) {
        if(gamefile->game_over == MERGE) {
            savescore(gamefile);
            salvez(gamefile);
            clear();
            menu(gamefile, lung, window);
        } else {
            clear();
            int mesaj = lung.colmax / 2 -
                        strlen("Nu exista vreun joc pornit") / 2;
            mvprintw(lung.linmax / 2, mesaj, "Nu exista vreun joc pornit");
            refresh();
            getch();
            clear();
            menu(gamefile, lung, window);
        }
    } else if(i == 4) {
        FILE *save = fopen("salvari.txt", "r");
        if(fisier_gol(save)) {
             clear();
            int mesaj = lung.colmax / 2 -
                        strlen("Nu exista vreun joc salvat") / 2;
            mvprintw(lung.linmax / 2, mesaj, "Nu exista vreun joc salvat");
            refresh();
            getch();
            clear();
        } else {
            load(gamefile, lung);
            Game(gamefile, window, lung);
        }
        menu(gamefile, lung, window);
    } else if (i == 2) {
        if (gamefile->game_over == MERGE) {
            Game(gamefile, window, lung);
            menu(gamefile, lung, window);
        } else {
            clear();
            int mesaj = lung.colmax / 2 -
                        strlen("Nu exista vreun joc pornit") / 2;
            mvprintw(lung.linmax / 2, mesaj, "Nu exista vreun joc pornit");
            refresh();
            getch();
            clear();
            menu(gamefile, lung, window);
        }
    } else if (i == 1) {
        newGame(gamefile, lung);
        Game(gamefile, window, lung);
        menu(gamefile, lung, window);
    }
    clear();
    attroff(A_BOLD);
}

int main(void)
{
    // initializari
    srand(time(NULL));

    // se inhiba afisarea caracterelor introduse la tastatura
    noecho();

    // initializez ecranul
    WINDOW *window = initscr();

    // initializez culorile
    start_color();

    // retine perechile de culori din culors.h
    color_init();

    // se ascunde cursorul
    curs_set(0);

    // initializez jocul
    struct Joc gamefile;

    // permit tastatura
    keypad(window, TRUE);

    struct Lungimi lung;
    // aflu dimensiunile ecranului
    getmaxyx(window, lung.linmax, lung.colmax);

    setare_dimensiune(lung);
    // preiau dimensiunea ecranului din fisier
    FILE *dimread = fopen("dimensiune.txt", "r");
    fscanf(dimread, "%d", &lung.coef);

    fclose(dimread);
    // distanta pe ecran de la matrice la instructiuni
    lung.dMT = 5 * lung.coef;

    // distanta dintre matrice si marginea dreapta a ecranului
    lung.distantaX = 20 * lung.coef;

    // distanta dintre matrice si marginea superioara a ecranului
    lung.distantaY = lung.linmax / 6;

    /* lungimea ocupata de legenda pe orizontala, aflat experimental */
    int lungtut = 42 * lung.coef - lung.distantaX;

    /* din motive estetice, dimensiunea ecranului trebuie sa aiba
    anumite valori, altfel programul nu va rula */

    /*conditii dimensiune verticala*/
    int conditie1 = (lung.linmax < MARIME_VERTICALA * 
    lung.coef + lung.distantaY + 1);
    /*conditii dimensiune orizontala*/
    int conditie2 = (lung.colmax < MARIME_ORIZONTALA * 
    lung.coef + lung.distantaX + lungtut);

    if (conditie1 || conditie2) {
        clear();
        printw("Dimensiuni ale ecranului invalide. Va rugam reincercati.");
        mvprintw(1, 0, "Apasati pentru a continua...");
        refresh();
        getch();
        clear();
        endwin();
        return 0;
    }

    /*generez titlul si meniul*/
    titlu(lung.colmax, lung.linmax);
    menu(&gamefile, lung, window);

    endwin();

    return 0;
}