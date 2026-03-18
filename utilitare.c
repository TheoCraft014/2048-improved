#include <stdio.h>
#include "utilitare.h"
#include <ncurses.h>

// atasez lui matrix2 valorile lui matrix1
void copiez(int matrix1[DIM_TABEL][DIM_TABEL],
            int matrix2[DIM_TABEL][DIM_TABEL])
{
    int i, j;
    for (i = 0; i < DIM_TABEL; i++)
        for (j = 0; j < DIM_TABEL; j++)
            matrix2[i][j] = matrix1[i][j];
}

/*verific daca matrix2 seamana cu matrix1
 daca sunt identice, functia va returna valoarea 1 */
int asemanare(int matrix1[DIM_TABEL][DIM_TABEL], int
                        matrix2[DIM_TABEL][DIM_TABEL])
{
    int i, j;
    for (i = 0; i < DIM_TABEL; i++)
        for (j = 0; j < DIM_TABEL; j++)
            if (matrix2[i][j] != matrix1[i][j])
                return 0;
    return 1;
}

/*numara spatiile goale din matrice
 functia returneaza numarul de spatii goale 
(elemente nule) din matrice */
int nrSpatiu(int matrix[DIM_TABEL][DIM_TABEL])
{
    int nr = 0;
    int i, j;
    for (i = 0; i < DIM_TABEL; i++)
        for (j = 0; j < DIM_TABEL; j++)
            if (matrix[i][j] == 0)
                nr++;
    return nr;
}

/* verific daca matricea are spatii goale
functia returneaza valoarea zero daca nu are spatii
returneaza valoarea 1 altfel */
int verificSpatiu(int matrix[DIM_TABEL][DIM_TABEL])
{
    int i, j;
    for (i = 0; i < DIM_TABEL; i++)
        for (j = 0; j < DIM_TABEL; j++)
            if (matrix[i][j] == 0)
                return 1;

    return 0;
}

/* prin intermediul unor relatii matematice afisez pe ecran valorile
corespunzatoare matricei */
void transpun(int matrix[DIM_TABEL][DIM_TABEL], struct Lungimi lung)
{
    int i, j;
    for (i = 0; i < DIM_TABEL; i++)
        for (j = 0; j < DIM_TABEL; j++) {
            int distX = lung.distantaX + MARIME_ORIZONTALA / 8 * lung.coef +
                        j * lung.coef * MARIME_ORIZONTALA / 4;
            int distY = lung.distantaY + MARIME_VERTICALA / 8 * lung.coef +
                        i * lung.coef * MARIME_VERTICALA / 4;

            /* afisez valorile matricei pe ecran in functie de coordonatele
            calculate anterior */
            if (matrix[i][j] > 0) {
                mvprintw(distY, distX, "%d", matrix[i][j]);
            } else {
                if (matrix[i][j] < 0) {
                    mvprintw(distY, distX, "%d^", (-1) * matrix[i][j]);
                }
            }
        }

    refresh();
}

/* elimin caracterul special deoarece numarul nu mai are pozitia
de generat aleator
 -aceasta eliminare este asociata eliminarii valorilor negative din matrice*/
void actualizezrandom(int matrix[DIM_TABEL][DIM_TABEL])
{
    int i, j;
    for (i = 0; i < DIM_TABEL; i++)
        for (j = 0; j < DIM_TABEL; j++)
            if (matrix[i][j] < 0)
                matrix[i][j] = (-1) * matrix[i][j];
}

/*functia actualizeaza prin intermediul matricei verific[][] casutele goale
 unde se vor putea genera valorile random */
void actualizez(int matrix[DIM_TABEL][DIM_TABEL], int 
verific[DIM_TABEL * DIM_TABEL][2], int *nrValabil)
{
    int i, j;
    // initializez numarul de casute goale cu zero
    *nrValabil = 0;

    for (i = 0; i < DIM_TABEL; i++)
        for (j = 0; j < DIM_TABEL; j++)
        {
            if (matrix[i][j] == 0)
            {
                verific[*nrValabil][0] = i;
                verific[*nrValabil][1] = j;
                (*nrValabil)++;
            }
        }
}
