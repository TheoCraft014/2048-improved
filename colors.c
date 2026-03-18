#include <ncurses.h>
#include "colors.h"

// generez perechi de culori
void color_init()
{
    init_pair(CHENAR, COLOR_MAGENTA, COLOR_BLUE);
    init_pair(BACKGROUND, COLOR_BLACK, COLOR_WHITE);
}