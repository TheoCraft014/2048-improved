#include "saves.h"
#include "utilitare.h"

void convertesteSirInMatrice(char sir[], int matrice[DIM_TABEL][DIM_TABEL]) {
    int index = 0, i, j;
    for (i = 0; i < DIM_TABEL; i++) {
        for (j = 0; j < DIM_TABEL; j++) {
            sscanf(sir + index, "%d", &matrice[i][j]);
            /*Ajustează index-ul pentru a trece la următorul număr în șir*/
            while (sir[index] != ' ' && sir[index] != '\0') {
                index++;
            }
            index++;  // Treci peste spațiu sau terminare de șir
        }
    }
}

/*salvez toate scorurile intr-un fisier*/
void savescore(struct Joc *gamefile)
{
    FILE *save = fopen("scoruri.txt", "a");
    if (save == NULL)
        printf("Eroare la apelul fisierului scoruri.txt");

    fprintf(save, "%d\n", gamefile->punctaj);
    fclose(save);
}

/*retine scorul maxim din scoruri.txt citind scorurile
retinute din fiecare linie*/
int scor_maxim(void)
{
    /*retin valoarea maxima*/
    int max = 0;
    /*scorul citit*/
    char scor[20];
    int punctaj;
    FILE *saves = fopen("scoruri.txt", "r");
    if (saves == NULL)
        printf("Eroare la citirea fisierului scoruri.txt");

    while (fgets(scor, sizeof(scor), saves) != NULL) {
        punctaj = atoi(scor);
        if (max < punctaj)
            max = punctaj;
    }

    fclose(saves);
    return max;
}

int fisier_gol(FILE *file)
{
    fseek(file, 0, SEEK_END);
    int lung = ftell(file);
    rewind(file);

    return (lung == 0);
}

/*functia salveaza datele jocului intr-un one-liner, separat de "|"*/
void salvez(struct Joc *gamefile)
{
    FILE *saves = fopen("salvari.txt", "a");
    if (saves == NULL) {
        printf("Eroare la apelarea fisierului salvari.txt");
        return ;
    }

    /*verific daca fisierul e gol*/
    if(fisier_gol(saves)) {
        gamefile->ID = 1;
    } else {
        gamefile->ID = saves_count() + 1;
    }

    printf("ID: %d\n", gamefile->ID);
    fprintf(saves, "%d|", gamefile->ID);
    int i, j;
    /*salvez matricea matrix*/
    for (i = 0; i < DIM_TABEL; i++)
        for (j = 0; j < DIM_TABEL; j++)
            fprintf(saves, "%d ", gamefile->matrix[i][j]);
    fprintf(saves, "|");

    /*salvez ceilalti parametri: game_over, punctaj,timp*/
    fprintf(saves, "%d|%d|%d", gamefile->game_over,
            gamefile->punctaj, gamefile->timp);
    /*introduc newline*/
    fprintf(saves, "\n");
    fclose(saves);
}

/*numara numarul de jocuri salvate*/
int saves_count()
{
    int count = 0;
    FILE *saves = fopen("salvari.txt", "r");
    if (saves == NULL) {
        printf("Eroare la apelarea fisierului salvari.txt");
        return -1;
    }
    /*buffer pentru citire*/
    char citire[150];

    while (fgets(citire, sizeof(citire), saves) != NULL) {
        /*fiecare linie e asociata unui joc salvat
        asadar numar numarul de linii*/
        count++;
    }

    fclose(saves);
    return count;
}

void quit(struct Joc *gamefile, struct Lungimi lung)
{
    clear();
    char intrebare[] = "SALVEZI PROGRESUL?";
    mvprintw(1, lung.colmax / 2 - strlen(intrebare) / 2, "%s", intrebare);
    char instruct[] = "Apasa ENTER pentru a continua";
    int lungEnter = lung.colmax / 2 - strlen(instruct) / 2;

    mvprintw(lung.linmax / 3, lung.colmax / 2 - strlen("DA") / 2, "DA");
    mvprintw(2 * lung.linmax / 3, lung.colmax / 2 - strlen("NU") / 2, "NU");

    int i = 1;
    /*sageata indica optiunea ce va fi aleasa
    initial aceasta este pe prima pozitie (DA)*/
    mvprintw(i * lung.linmax / 3, lung.colmax / 2 - 5, "-> ");
    mvprintw(lung.linmax - 1, lungEnter, "%s", instruct);

    while (FOREVER) {
        mvprintw(1, lung.colmax / 2 - strlen(intrebare) / 2, "%s", intrebare);
        mvprintw(lung.linmax / 3, lung.colmax / 2 - strlen("DA") / 2, "DA");
        mvprintw(2 * lung.linmax / 3, lung.colmax / 2 - strlen("NU") / 2, "NU");
        mvprintw(lung.linmax - 1, lungEnter, "%s", instruct);

        int tasta = getch();

        /*in functie de sageata apasata, mut pozitia sagetii*/
        switch (tasta) {
            case KEY_DOWN:
                if (i < 2) {
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
        mvprintw(i * lung.linmax / 3, lung.colmax / 2 - 5, "-> ");

        refresh();
        if (tasta == '\n') {
            break;
        }
    }
    /*optiuni in functie de pozitie
    i = 1 - DA (se salveaza)
    i = 2 - NU (nu se salveaza)*/

    if (i == 1 && gamefile->game_over == MERGE) {
        salvez(gamefile);
        savescore(gamefile);
    }
}

void afisare_jocuri(int ID, struct Lungimi lung)
{
    clear();
    /*afisez pe ecran instructiuni*/
    char instr[] = "Alegeti jocul";
    mvprintw(lung.linmax / 10, lung.colmax / 2 - strlen(instr) / 2, "%s", instr);
    char comand[] = "Apasa ENTER pentru a continua";
    mvprintw(lung.linmax / 6, lung.colmax / 2 - strlen(comand) / 2, "%s", comand);

    FILE *save = fopen("salvari.txt", "r");
    if (save == NULL) {
        printf("Eroare la apelarea fisierului salvari.txt");
        return ;
    }
    /*preiau continutul din fisier pentru fiecare linie*/
    char citire[150];

    while (fgets(citire, sizeof(citire), save) != NULL) {
        char *citirecopy = strdup(citire);
        /*aflu ID-ul care este primul element al liniei*/
        char *IDfinder = strtok(citirecopy, "|");
        int IDcopy = atoi(IDfinder);

        if (IDcopy == ID) {
            /*voi afla matricea si punctajul jocului in functie de linia din
            fisier corespunzatoare ID-ului cerut*/
            char *citirecopy2 = strdup(citire);

            /*aflu portiunea din fisier ce cuprinde elementele matricei*/
            char *matrixEL = strtok(citirecopy2, "|");
            matrixEL = strtok(NULL, "|");

            int matrice[DIM_TABEL][DIM_TABEL];
            convertesteSirInMatrice(matrixEL, matrice);

            for (int i = 0; i < DIM_TABEL; i++) {
                for (int j = 0; j < DIM_TABEL; j++) {
                    mvprintw(lung.linmax / 2 - i, lung.colmax / 2 - (DIM_TABEL * 4) / 2
                             + j * 4, "%d", matrice[i][j]);
                }
            }

            char* punctajfinder = strtok(NULL, "|");
            char punctaj[] = "Punctaj: ";
            punctajfinder = strtok(NULL, "|");
            mvprintw(lung.linmax/2 + lung.linmax/5,
                    lung.colmax / 2 - strlen(punctaj) / 2,
                    "Punctaj: %s\n", punctajfinder);

            free(citirecopy2);
            refresh();
            break;
        }

        free(citirecopy);
    }

    fclose(save);
}


void incarc_joc(int ID, struct Joc *gamefile)
{
    int i,j;
    FILE *save = fopen("salvari.txt", "r");

    if (save == NULL) {
        perror("Eroare la deschiderea fisierului salvari.txt");
        return ;
    }

    char citire[150];

    while(fgets(citire, sizeof(citire), save) != NULL) {
        char *citirecopy = strdup(citire);
        /*copiez adresa sirului ce citeste linia
        aflu ID-ul corespunzator liniei respective separand sirul in 
        subsiruri separate de caracterul "|" - cu rol in a delimita 
        informatii privind datele unui joc*/
        char *IDfinder = strtok(citirecopy, "|");
        int IDcopy = atoi(IDfinder);

        /*verific daca ID-urile coincid*/
        if (IDcopy == ID) {
            char *citirecopy2 = strdup(citire);
            char *matrixEL = strtok(citirecopy2, "|");

            if (matrixEL == NULL) {
                printf("Eroare la citirea matricei din fisier");
                fclose(save);
                return;
            }
            matrixEL = strtok(NULL, "|");
            
            // Setează valorile matricei în structura de jocuri
            convertesteSirInMatrice(matrixEL, gamefile->matrix);

            sscanf(strtok(NULL, "|"), "%d", &gamefile->game_over);
            sscanf(strtok(NULL, "|"), "%d", &gamefile->punctaj);
            sscanf(strtok(NULL, "|"), "%d", &gamefile->timp);

            gamefile->nrValabil = 0;
            /*actualizez nrValabil si matricea verific[][]*/
            for (i = 0; i < DIM_TABEL; i++) {
                for (j = 0; j < DIM_TABEL; j++) {
                    gamefile->verific[gamefile->nrValabil][0] = i;
                    gamefile->verific[gamefile->nrValabil][1] = j;
                    gamefile->nrValabil++;
                }  
            }
            fclose(save);
            return;
        }
    }

    fclose(save);
    
}


void load(struct Joc *gamefile, struct Lungimi lung)
{

    clear();
    int i = 1;
    afisare_jocuri(i, lung);
    while (FOREVER) {
        int tasta = getch();

        switch (tasta)
        {
            case KEY_DOWN:
            case 's':
                if (i < saves_count())
                    i++;
                break;

            case KEY_UP:
            case 'w':
                if (i > 1)
                    i--;
                break;
        }

        afisare_jocuri(i, lung);
        if (tasta == '\n') {
            clear();
            break;
        }
    }
        
    incarc_joc(i, gamefile);
}