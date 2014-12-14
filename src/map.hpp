#ifndef H_MAP
#define H_MAP

#include <stdio.h>
#include <string.h>
#include <string>
#include <ncurses.h>

#include "define.hpp"
#include "renderer.hpp"

void initMap(Room[MAX_AREA][MAX_WIDTH][MAX_HEIGHT]);
void renderMap(Frame, Room[MAX_AREA][MAX_WIDTH][MAX_HEIGHT], Player*);
int isValid(Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT], int a, int x, int y);

#endif
