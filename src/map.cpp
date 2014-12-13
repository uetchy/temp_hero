#include <stdio.h>
#include <string.h>

#include "map.hpp"
//area[areaNo][X][Y]
void initMap(Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT]) {
  // Potion location
  area[ 0 ][ 4 ][ 4 ].hasPotion = 1;
  area[ 0 ][ 2 ][ 4 ].hasPotion = 1;
  area[ 0 ][ 3 ][ 2 ].hasPotion = 1;
  area[ 1 ][ 3 ][ 5 ].hasPotion = 1;
  area[ 1 ][ 1 ][ 2 ].hasPotion = 1;

  // Key location
  area[ 0 ][ 1 ][ 2 ].hasKey = 1;
  area[ 1 ][ 7 ][ 6 ].hasKey = 1;

  // Hint location
  strcpy(area[ 0 ][ 3 ][ 6 ].hint, "this is a hint");
  strcpy(area[ 0 ][ 0 ][ 6 ].hint, "this is a hint");
  strcpy(area[ 0 ][ 5 ][ 2 ].hint, "this is a hint");
  strcpy(area[ 0 ][ 7 ][ 7 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 2 ][ 3 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 3 ][ 0 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 7 ][ 5 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 7 ][ 7 ].hint, "Hidden Boss hint");

  // Stair location
  area[ 0 ][ 3 ][ 7 ].canJump = 1;

  // Unique boss location
  area[ 1 ][ 7 ][ 7 ].uniqueBossId = 1; // Hidden-boos
  area[ 1 ][ 0 ][ 5 ].uniqueBossId = 0; // Boss

  // Player visited
  for ( int a=0; a < MAX_AREA; a++ ) {
    for ( int x=0; x < MAX_WIDTH; x++ ) {
      for ( int y=0; y < MAX_HEIGHT; y++ ) {
        area[a][x][y].playerVisited = 0;
      }
    }
  }

  // Init doorinfo
  for ( int a=0; a < MAX_AREA; a++ ) {
    for ( int x=0; x < MAX_WIDTH; x++ ) {
      for ( int y=0; y < MAX_HEIGHT; y++ ) {
        area[a][x][y].doorInfo[ D_UP ] = -1;
      }
    }
  }

  // Area 1 door location
  // Row 1
  area[ 0 ][ 0 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 0 ][ 6 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 0 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 0 ][ 6 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 2
  area[ 0 ][ 1 ][ 2 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 1 ][ 2 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 1 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 1 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 1 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 1 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 1 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 1 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 1 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 1 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 1 ][ 4 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 1 ][ 4 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 1 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 1 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 1 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 1 ][ 6 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 3
  area[ 0 ][ 2 ][ 4 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 2 ][ 4 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 2 ][ 4 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 2 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 2 ][ 5 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 2 ][ 5 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 2 ][ 5 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 2 ][ 5 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 2 ][ 6 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 2 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 2 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 2 ][ 6 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 4
  area[ 0 ][ 3 ][ 2 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 3 ][ 2 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 3 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 3 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 3 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 3 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 3 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 3 ][ 4 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 3 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 3 ][ 4 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 3 ][ 7 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 3 ][ 7 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 7 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 3 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 5
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 4 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 4 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 6 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 6
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 5 ][ 3 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 4 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 5 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 6 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 6 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 5 ][ 6 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 7 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 7 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 5 ][ 7 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 7
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_RIGHT ] = DC_LOCKED;
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 6 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 6 ][ 7 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 7 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 8
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 7 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 7 ][ 7 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 7 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 7 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Area 2 door
  // 1行列目

  // area[ 1 ] (6,1)
  area[ 1 ][ 5 ][ 0 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 5 ][ 0 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 5 ][ 0 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 5 ][ 0 ].doorInfo[ D_DOWN ] = DC_NIL;


  // 2行列目

  // area[ 1 ] (3,2)
  area[ 1 ][ 2 ][ 1 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 2 ][ 1 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 2 ][ 1 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 2 ][ 1 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (4,2)
  area[ 1 ][ 3 ][ 1 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 3 ][ 1 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 3 ][ 1 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 3 ][ 1 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (5,2)
  area[ 1 ][ 4 ][ 1 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 4 ][ 1 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 4 ][ 1 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 4 ][ 1 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (6,2)
  area[ 1 ][ 5 ][ 1 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 5 ][ 1 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 5 ][ 1 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 5 ][ 1 ].doorInfo[ D_DOWN ] = DC_NIL;

  // ３行列目

  // area[ 1 ] (3,3)
  area[ 1 ][ 2 ][ 2 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 2 ][ 2 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 2 ][ 2 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 2 ][ 2 ].doorInfo[ D_DOWN ] = DC_NIL;

  // ４行列目

  // area[ 1 ] (1,4)
  area[ 1 ][ 0 ][ 3 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 0 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 0 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 0 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (2,4)
  area[ 1 ][ 1 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 1 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 1 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 1 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (3,4)
  area[ 1 ][ 2 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 2 ][ 3 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 2 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 2 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (4,4)
  area[ 1 ][ 3 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 3 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 3 ][ 3 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (5,4)
  area[ 1 ][ 4 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 4 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 4 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 4 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (6,4)
  area[ 1 ][ 5 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 5 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 5 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 5 ][ 3 ].doorInfo[ D_DOWN ] = DC_NIL;

  // ５行列目

  // area[ 1 ] (4,5)
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_DOWN ] = DC_NIL;

  //６行列目

  // area[ 1 ] (4,6)
  area[ 1 ][ 3 ][ 5 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 3 ][ 5 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 5 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 5 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (5,6)
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (6,6)
  area[ 1 ][ 5 ][ 5 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 5 ][ 5 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 5 ][ 5 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 5 ][ 5 ].doorInfo[ D_DOWN ] = DC_NIL;

  //７行列目

  // area[ 1 ] (4,7)
  area[ 1 ][ 3 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 3 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 6 ].doorInfo[ D_DOWN ] = DC_NIL;

  // area[ 1 ] (6,7)
  area[ 1 ][ 5 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 5 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 5 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 5 ][ 6 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 8
  // area[ 1 ] (1,8)
  area[ 1 ][ 0 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 0 ][ 7 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 0 ][ 7 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 0 ][ 7 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (2,8)
  area[ 1 ][ 1 ][ 7 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 1 ][ 7 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 1 ][ 7 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 1 ][ 7 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (3,8)
  area[ 1 ][ 2 ][ 7 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 2 ][ 7 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 2 ][ 7 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 2 ][ 7 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (4,8)
  area[ 1 ][ 3 ][ 7 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 3 ][ 7 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 7 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 3 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

  // area[ 1 ] (6,8)
  area[ 1 ][ 5 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 5 ][ 7 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 5 ][ 7 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 5 ][ 7 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (7,8)
  area[ 1 ][ 6 ][ 7 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 6 ][ 7 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 6 ][ 7 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 6 ][ 7 ].doorInfo[ D_DOWN ] = DC_LOCKED;

  // area[ 1 ] (8,8)
  area[ 1 ][ 7 ][ 7 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 7 ][ 7 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 7 ][ 7 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 7 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;
}

int positionToEquals(Player* p, int r_x, int r_y) {
  if ( p->x == r_x && p->y == r_y ) {
    return 1;
  } else {
    return 0;
  }
}

int isValid(Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT], int a, int x, int y) {
  return x < MAX_WIDTH && x >= 0 && y < MAX_HEIGHT && y >= 0 && area[a][x][y].doorInfo[D_UP] != -1;
}

// Rendering map
void renderMap(WINDOW* target, Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT], Player* player) {
  int pa = player->c_area;
  int px = player->x;
  int py = player->y;

  const int maxRange = 5;
  const int startPoint = maxRange/2 * -1;

  clear();

  for (int x=startPoint; x < startPoint+maxRange; x++) {
    for (int y=startPoint; y < startPoint+maxRange; y++) {
      int rx = (x+maxRange/2) * 11;
      int ry = (y+maxRange/2) * 5;

      if (!isValid(area, pa, px+x, py+y)) {
        mvprintw(ry,   rx, "...........");
        mvprintw(ry+1, rx, "...........");
        mvprintw(ry+2, rx, "...........");
        mvprintw(ry+3, rx, "...........");
        mvprintw(ry+4, rx, "...........");
        continue;
      }

      Room room = area[pa][px+x][py+y];

      if ( room.doorInfo[D_UP] == -1 || !room.playerVisited ) {
        mvprintw(ry,   rx, "...........");
        mvprintw(ry+1, rx, "...........");
        mvprintw(ry+2, rx, "...........");
        mvprintw(ry+3, rx, "...........");
        mvprintw(ry+4, rx, "...........");
        continue;
      }

      // Render room
      switch(room.doorInfo[D_UP]){
        case DC_NIL:
          mvprintw(ry, rx, "╔═════════╗");
          break;
        case DC_OPEN:
          mvprintw(ry, rx, "╔═══╝ ╚═══╗");
          break;
        case DC_LOCKED:
          mvprintw(ry, rx, "╔═══╝X╚═══╗");
          break;
        default:
          mvprintw(ry, rx, "╔════?════╗");
      }

      mvprintw(ry+1, rx, "║%d,%d      ║", px+x, py+y);

      switch(room.doorInfo[D_LEFT]){
        case DC_NIL:
          mvprintw(ry+2, rx, "║    ");
          break;
        case DC_OPEN:
          mvprintw(ry+2, rx, "     ");
          break;
        case DC_LOCKED:
          mvprintw(ry+2, rx, "X    ");
          break;
      }

      printw(positionToEquals(player, px+x, py+y) ? "👽" : " ");

      switch(room.doorInfo[D_RIGHT]){
        case DC_NIL:
          printw("    ║");
          break;
        case DC_OPEN:
          printw("     ");
          break;
        case DC_LOCKED:
          printw("    X");
          break;
      }

      mvprintw(ry+3, rx, "║         ║");

      switch(room.doorInfo[D_DOWN]){
        case DC_NIL:
          mvprintw(ry+4, rx, "╚═════════╝");
          break;
        case DC_OPEN:
          mvprintw(ry+4, rx, "╚═══╗ ╔═══╝");
          break;
        case DC_LOCKED:
          mvprintw(ry+4, rx, "╚═══╗X╔═══╝");
          break;
      }
    }
  }
}
