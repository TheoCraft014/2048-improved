#ifndef SAVES_H
#define SAVES_H

#include <ncurses.h>
#include <stdio.h>
#include "stare-joc.h"
#include <stdlib.h>
#include <string.h>
#include "utilitare.h"

void savescore(struct Joc *gamefile);
int scor_maxim(void);
void quit(struct Joc *gamefile, struct Lungimi lung);
void load(struct Joc *gamefile, struct Lungimi lung);
void salvez(struct Joc *gamefile);
int saves_count(void);
void afisare_jocuri(int ID, struct Lungimi lung);
void incarc_joc(int ID, struct Joc *gamefile);
void convertesteSirInMatrice(char sir[], 
int matrice[DIM_TABEL][DIM_TABEL]);
int fisier_gol(FILE *file);

#endif