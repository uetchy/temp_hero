#ifndef H_MAP
#define H_MAP

#include <ncurses.h>

#include "define.hpp"

void initMap(Room[MAX_AREA][MAX_WIDTH][MAX_HEIGHT]);
void renderMap(WINDOW*, Room[MAX_AREA][MAX_WIDTH][MAX_HEIGHT], Player*);

#endif
