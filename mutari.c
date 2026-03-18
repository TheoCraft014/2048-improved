#include <stdio.h>
#include "mutari.h"
#include "utilitare.h"

/* executa mutarea in sus a casutelor */
void nord(int matrix[DIM_TABEL][DIM_TABEL], int *punctaj)
{
    int i, j, parcurg = 0;
    // poz este un vector ce retine coordonatele unei casute valide
    int poz[2] = {0};
    for (j = 0; j < DIM_TABEL; j++) {
        parcurg = 0;
        for (i = 0; i < DIM_TABEL; i++) {
            if (matrix[i][j] != 0 && parcurg == 0) {
                parcurg = matrix[i][j];
                poz[0] = i;
                poz[1] = j;
            } else {
                if (matrix[i][j] != 0 && parcurg != 0) {
                    if (matrix[i][j] == parcurg) {
                        // multiplic casuta retinuta cu 2
                        matrix[poz[0]][poz[1]] *= 2;
                        *punctaj += matrix[poz[0]][poz[1]];
                        parcurg = 0;
                        // elimin casuta care s-a unit cu casuta mai
                        // apropiata de margine
                        matrix[i][j] = 0;
                        poz[0] = poz[1] = 0;
                    } else {
                        // reinitializez pozitia
                        poz[0] = i;
                        poz[1] = j;
                        parcurg = matrix[i][j];
                    }
                }
            }
        }
    }

    // calculeaza distanta fiecarei celule valide pana la margine
    int distanta;
    for (j = 0; j < DIM_TABEL; j++) {
        distanta = 0;
        for (i = 0; i < DIM_TABEL; i++) {
            if (matrix[i][j] == 0) {
                distanta++;
            } else {
                if (distanta > 0) {
                    matrix[i - distanta][j] = matrix[i][j];
                    matrix[i][j] = 0;
                }
            }
        }
    }
}

/* executa mutarea in jos a casutelor */
void sud(int matrix[DIM_TABEL][DIM_TABEL], int *punctaj)
{
    int i, j, parcurg = 0;
    // poz este un vector ce retine coordonatele unei casute
    int poz[2] = {0};
    for (j = 0; j < DIM_TABEL; j++) {
        parcurg = 0;
        for (i = DIM_TABEL - 1; i >= 0; i--) {
            if (matrix[i][j] != 0 && parcurg == 0) {
                parcurg = matrix[i][j];
                poz[0] = i;
                poz[1] = j;
            } else {
                if (matrix[i][j] != 0 && parcurg != 0) {
                    if (matrix[i][j] == parcurg) {
                        matrix[poz[0]][poz[1]] *= 2;
                        *punctaj += matrix[poz[0]][poz[1]];
                        parcurg = 0;
                        matrix[i][j] = 0;
                        poz[0] = poz[1] = 0;
                    } else {
                        poz[0] = i;
                        poz[1] = j;
                        parcurg = matrix[i][j];
                    }
                }
            }
        }
    }

    // calculeaza distanta fiecarei celule valide pana la margine
    int distanta;
    for (j = 0; j < DIM_TABEL; j++) {
        distanta = 0;
        for (i = DIM_TABEL - 1; i >= 0; i--) {
            if (matrix[i][j] == 0) {
                distanta++;
            } else {
                if (distanta > 0) {
                    matrix[i + distanta][j] = matrix[i][j];
                    matrix[i][j] = 0;
                }
            }
        }
    }
}

/* executa mutarea in stanga a casutelor */
void vest(int matrix[DIM_TABEL][DIM_TABEL], int *punctaj)
{
    int i, j, parcurg = 0;
    // poz este un vector ce retine coordonatele unei casute
    int poz[2] = {0};
    for (i = 0; i < DIM_TABEL; i++) {
        parcurg = 0;
        for (j = 0; j < DIM_TABEL; j++) {
            if (matrix[i][j] != 0 && parcurg == 0) {
                parcurg = matrix[i][j];
                poz[0] = i;
                poz[1] = j;
            } else {
                if (matrix[i][j] != 0 && parcurg != 0) {
                    if (matrix[i][j] == parcurg) {
                        matrix[poz[0]][poz[1]] *= 2;
                        *punctaj += matrix[poz[0]][poz[1]];
                        parcurg = 0;
                        matrix[i][j] = 0;
                        poz[0] = poz[1] = 0;
                    } else {
                        poz[0] = i;
                        poz[1] = j;
                        parcurg = matrix[i][j];
                    }
                }
            }
        }
    }

    // calculeaza distanta fiecarei celule valide pana la margine
    int distanta;
    for (i = 0; i < DIM_TABEL; i++) {
        distanta = 0;
        for (j = 0; j < DIM_TABEL; j++) {
            if (matrix[i][j] == 0) {
                distanta++;
            } else {
                if (distanta > 0) {
                    matrix[i][j - distanta] = matrix[i][j];
                    matrix[i][j] = 0;
                }
            }
        }
    }
}

/*executa mutarea in dreapta a casutelor */
void est(int matrix[DIM_TABEL][DIM_TABEL], int *punctaj)
{
    int i, j, parcurg = 0;
    // poz este un vector ce retine coordonatele unei casute
    int poz[2] = {0};
    for (i = 0; i < DIM_TABEL; i++) {
        parcurg = 0;
        for (j = DIM_TABEL - 1; j >= 0; j--) {
            if (matrix[i][j] != 0 && parcurg == 0) {
                parcurg = matrix[i][j];
                poz[0] = i;
                poz[1] = j;
            } else {
                if (matrix[i][j] != 0 && parcurg != 0) {
                    if (matrix[i][j] == parcurg) {
                        matrix[poz[0]][poz[1]] *= 2;
                        *punctaj += matrix[poz[0]][poz[1]];
                        parcurg = 0;
                        matrix[i][j] = 0;
                        poz[0] = poz[1] = 0;
                    } else {
                        poz[0] = i;
                        poz[1] = j;
                        parcurg = matrix[i][j];
                    }
                }
            }
        }
    }

    // calculeaza distanta fiecarei celule valide pana la margine
    int distanta;
    for (i = 0; i < DIM_TABEL; i++) {
        distanta = 0;
        for (j = DIM_TABEL - 1; j >= 0; j--) {
            if (matrix[i][j] == 0) {
                distanta++;
            } else {
                if (distanta > 0) {
                    matrix[i][j + distanta] = matrix[i][j];
                    matrix[i][j] = 0;
                }
            }
        }
    }
}

/*executa mutarea automata dupa un interval de timp*/
void mutAutomat(struct Joc *gamefile)
{
    /*voi verifica validitatea mutarilor analog algoritmului dim tema2.c */
    int copie[DIM_TABEL][DIM_TABEL];
    int copie2[DIM_TABEL][DIM_TABEL];

    // variabila de umplutura - calculeaza punctajul
    int p = 0;
    // alege mutarea care lasa nr maxim de spatii
    int poz = 0;
    // verific care mutare lasa cele mai multe spatii
    int max = -1;

    /*  
    poz = 1 - mutare nord
    poz = 2 - mutare sud
    poz = 3 - mutare vest
    poz = 4 - mutare est   

    copiez valorile in 2 matrici, mut in nord/sud/est/vest elementele unei
    matrici, si daca se aseamana cu matricea
    */

   /*nord*/
    copiez(gamefile->matrix, copie);
    copiez(gamefile->matrix, copie2);
    actualizezrandom(copie);
    actualizezrandom(copie2);
    nord(copie, &p);
    int nordi = asemanare(copie2, copie);
    if (nrSpatiu(copie) > max && nordi == 0) {
        max = nrSpatiu(copie);
        poz = 1;
    }

    /*sud*/
    copiez(gamefile->matrix, copie);
    copiez(gamefile->matrix, copie2);
    actualizezrandom(copie);
    actualizezrandom(copie2);
    sud(copie, &p);
    int sudi = asemanare(copie2, copie);
    if (nrSpatiu(copie) > max && sudi == 0) {
        max = nrSpatiu(copie);
        poz = 2;
    }

    /*vest*/
    copiez(gamefile->matrix, copie);
    copiez(gamefile->matrix, copie2);
    actualizezrandom(copie);
    actualizezrandom(copie2);
    vest(copie, &p);
    int vesti = asemanare(copie2, copie);
    if (nrSpatiu(copie) > max && vesti == 0) {
        max = nrSpatiu(copie);
        poz = 3;
    }

    /*est*/
    copiez(gamefile->matrix, copie);
    copiez(gamefile->matrix, copie2);
    actualizezrandom(copie);
    actualizezrandom(copie2);
    est(copie, &p);
    int esti = asemanare(copie2, copie);
    if (nrSpatiu(copie) > max && esti == 0) {
        max = nrSpatiu(copie);
        poz = 4;
    }

    /* retinem pozitia in care a avut loc mutarea optima
     in functie de pozitie executam mutarea in cadrul jocului */
    if (poz == 1 && nordi == 0) {
        actualizezrandom(gamefile->matrix);
        nord(gamefile->matrix, &gamefile->punctaj);
    } else if (poz == 2 && sudi == 0) {
        actualizezrandom(gamefile->matrix);
        sud(gamefile->matrix, &gamefile->punctaj);
    } else if (poz == 3 && vesti == 0) {
        actualizezrandom(gamefile->matrix);
        vest(gamefile->matrix, &gamefile->punctaj);
    } else if (poz == 4 && esti == 0) {
        actualizezrandom(gamefile->matrix);
        est(gamefile->matrix, &gamefile->punctaj);
    }
}
