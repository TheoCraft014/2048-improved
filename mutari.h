#ifndef MUTARI_H
#define MUTARI_H

#include "stare-joc.h"
#include "utilitare.h"

void nord(int matrix[DIM_TABEL][DIM_TABEL], int *punctaj);
void sud(int matrix[DIM_TABEL][DIM_TABEL], int *punctaj);
void est(int matrix[DIM_TABEL][DIM_TABEL], int *punctaj);
void vest(int matrix[DIM_TABEL][DIM_TABEL], int *punctaj);
void mutAutomat(struct Joc *gamefile);

#endif