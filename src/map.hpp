#ifndef H_MAP
#define H_MAP

#include <ncurses.h>

#include "define.hpp"
#include "renderer.hpp"

void initMap(Room[MAX_AREA][MAX_WIDTH][MAX_HEIGHT]);
void renderMap(WINDOW*, Room[MAX_AREA][MAX_WIDTH][MAX_HEIGHT], Player*);
int isValid(Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT], int a, int x, int y);

#endif
