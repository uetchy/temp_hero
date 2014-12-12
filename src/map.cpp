#include <stdio.h>
#include <string.h>

#include "map.hpp"

void initMap(Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT]) {
  // Potion location
  area[ 0 ][ 4 ][ 4 ].hasPotion = 1;
  area[ 0 ][ 4 ][ 2 ].hasPotion = 1;
  area[ 0 ][ 2 ][ 3 ].hasPotion = 1;
  area[ 1 ][ 5 ][ 3 ].hasPotion = 1;
  area[ 1 ][ 2 ][ 1 ].hasPotion = 1;

  // Key location
  area[ 0 ][ 2 ][ 1 ].hasKey = 1;
  area[ 1 ][ 6 ][ 7 ].hasKey = 1;

  // Hint location
  strcpy(area[ 0 ][ 6 ][ 3 ].hint, "this is a hint");
  strcpy(area[ 0 ][ 6 ][ 0 ].hint, "this is a hint");
  strcpy(area[ 0 ][ 2 ][ 5 ].hint, "this is a hint");
  strcpy(area[ 0 ][ 7 ][ 7 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 3 ][ 5 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 0 ][ 3 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 5 ][ 7 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 7 ][ 7 ].hint, "Hidden Boss hint");

  // Stair location
  area[ 0 ][ 7 ][ 3 ].canJump = 1;

  // Unique boss location
  area[ 1 ][ 7 ][ 7 ].uniqueBossId = 1; // Hidden-boos
  area[ 1 ][ 5 ][ 0 ].uniqueBossId = 0; // Boss

  // Player visited
  for ( int a=0; a < MAX_AREA; a++ ) {
    for ( int x=0; x < MAX_WIDTH; x++ ) {
      for ( int y=0; y < MAX_HEIGHT; y++ ) {
        area[a][x][y].playerVisited = 0;
      }
    }
  }

  // Area 1 door location
  // Row 1
  area[ 0 ][ 6 ][ 0 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 6 ][ 0 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 6 ][ 0 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 0 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 2
  area[ 0 ][ 2 ][ 1 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 2 ][ 1 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 2 ][ 1 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 2 ][ 1 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 3 ][ 1 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 3 ][ 1 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 1 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 3 ][ 1 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 4 ][ 1 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 4 ][ 1 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 4 ][ 1 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 1 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 6 ][ 1 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 6 ][ 1 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 1 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 1 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 3
  area[ 0 ][ 4 ][ 2 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 4 ][ 2 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 2 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 6 ][ 2 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 6 ][ 2 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 2 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 2 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 4
  area[ 0 ][ 2 ][ 3 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 2 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 2 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 2 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 3 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 3 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 3 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 4 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 4 ][ 3 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 4 ][ 3 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 5
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 6 ][ 4 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 6 ][ 4 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 4 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 4 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 6
  area[ 0 ][ 2 ][ 5 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 2 ][ 5 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 2 ][ 5 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 2 ][ 5 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 3 ][ 5 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 3 ][ 5 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 5 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 3 ][ 5 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 4 ][ 5 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 4 ][ 5 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 5 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 4 ][ 5 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 6 ][ 5 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 6 ][ 5 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 6 ][ 5 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 6 ][ 5 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 7 ][ 5 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 7 ][ 5 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 5 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 7 ][ 5 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 7
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_RIGHT ] = DC_LOCKED;
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 7 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 7 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 6 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 8
  area[ 0 ][ 3 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 3 ][ 7 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 7 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 3 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

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

// Rendering map
void renderMap(WINDOW* target, Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT], Player* player) {
  int a = player->c_area;
  int x = player->x;
  int y = player->y;

  Room currentRoom = area[a][x][y];
  Room nearRooms[3][3] = {
    {area[a][x-1][y-1], area[a][x][y-1], area[a][x+1][y-1]},
    {area[a][x-1][y  ], area[a][x][y  ], area[a][x+1][y  ]},
    {area[a][x-1][y+1], area[a][x][y+1], area[a][x+1][y+1]}
  };

  for (int x=0; x < 3; x++) {
    for (int y=0; y < 3; y++) {
      Room room = nearRooms[x][y];

      int rx = x * 11;
      int ry = y * 5;

      // Render room
      //"╗", "╔", "╝", "╚", "═", "║"
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
      }

      mvprintw(ry+1, rx, "║         ║");

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

      printw("%s", room.playerVisited ? "👽" : " ");

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
    printw("\n");
  }
}
