#ifndef H_MAP
#define H_MAP

#include "define.h"

void initMap(struct Room[2][MAX_WIDTH][MAX_HEIGHT]);
void renderMap(struct Room[2][MAX_WIDTH][MAX_HEIGHT], struct Player*);

#endif
