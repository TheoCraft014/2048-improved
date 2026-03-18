#ifndef UTILITARE_H
#define UTILITARE_H

#include "stare-joc.h"

void copiez(int matrix1[DIM_TABEL][DIM_TABEL],
            int matrix2[DIM_TABEL][DIM_TABEL]);

int asemanare(int matrix1[DIM_TABEL][DIM_TABEL], int
                                                     matrix2[DIM_TABEL][DIM_TABEL]);

int nrSpatiu(int matrix[DIM_TABEL][DIM_TABEL]);

int verificSpatiu(int matrix[DIM_TABEL][DIM_TABEL]);

/* prin intermediul unor relatii matematice afisez pe ecran valorile
corespunzatoare matricei */
void transpun(int matrix[DIM_TABEL][DIM_TABEL], struct Lungimi lung);

void actualizezrandom(int matrix[DIM_TABEL][DIM_TABEL]);

void actualizez(int matrix[DIM_TABEL][DIM_TABEL], int verific[DIM_TABEL 
* DIM_TABEL][2], int *nrValabil);

#endif