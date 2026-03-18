#ifndef SETTIME_H
#define SETTIME_H

#include <ncurses.h>
#include <string.h>
#include "stare-joc.h"
#include <time.h>

void afisez_setari_timp(int lin, int col);

void setari_timp(struct Joc *gamefile, struct Lungimi lung);

void timp(int col, int lin, int distantaX, int distantaY);

#endif