#include "map.hpp"

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
  area[ 0 ][ 7 ][ 3 ].canJump = 1;

  // Unique boss location
  area[ 1 ][ 7 ][ 7 ].uniqueBossId = 1; // Hidden-boos
  area[ 1 ][ 0 ][ 5 ].uniqueBossId = 0; // Boss

  // Player visited
  for ( int a=0; a < MAX_AREA; a++ )
    for ( int x=0; x < MAX_WIDTH; x++ )
      for ( int y=0; y < MAX_HEIGHT; y++ )
        area[a][x][y].playerVisited = 0;

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
  return x < MAX_WIDTH && x >= 0 && y < MAX_HEIGHT && y >= 0 && area[a][x][y].doorInfo;
}

// Rendering map
void renderMap(Frame target, Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT], Player* player) {
  const int roomHeight = 9;
  const int roomWidth = roomHeight*2.2; // Square room
  const int mapCols = target.cols()/roomWidth;
  const int mapLines  = target.lines()/roomHeight;

  WINDOW* view = target.getView();

  target.clear();

  for (int i=0; i < mapCols; i++) {
    for (int j=0; j < mapLines; j++) {
      int mapX = i * roomWidth;
      int mapY = j * roomHeight;
      int areaX = (player->x - mapCols/2) + i;
      int areaY = (player->y - mapLines/2) + j;

      Room room = area[player->c_area][areaX][areaY];

      // Check is invalid
      if (!isValid(area, player->c_area, areaX, areaY) || !room.playerVisited) {
        for (int i=0; i < roomHeight; i++) {
          mvwprintw(view, mapY+i, mapX, seqStr(roomWidth, ".", ".", ".").c_str());
        }
        continue;
      }

      // Render room
      switch(room.doorInfo[D_UP]){
        case DC_NIL:
          mvwprintw(view, mapY, mapX, seqStr(roomWidth, "╔", "═", "╗").c_str());
          break;
        case DC_OPEN:
          mvwprintw(view, mapY, mapX, (
            seqStr(roomWidth/2, "╔", "═", "╝") +
            " " +
            seqStr(roomWidth/2, "╚", "═", "╗")
          ).c_str());
          break;
        case DC_LOCKED:
          mvwprintw(view, mapY, mapX, (
            seqStr(roomWidth/2, "╔", "═", "╝") +
            "X" +
            seqStr(roomWidth/2, "╚", "═", "╗")
          ).c_str());
          break;
      }

      for (int i=1; i < roomHeight-1; i++) {
        mvwprintw(view, mapY+i, mapX, "║");
      }

      switch(room.doorInfo[D_LEFT]){
        case DC_NIL:
          break;
        case DC_OPEN:
          mvwprintw(view, mapY+roomHeight/2-1, mapX, "╝");
          mvwprintw(view, mapY+roomHeight/2,   mapX, " ");
          mvwprintw(view, mapY+roomHeight/2+1, mapX, "╗");
          break;
        case DC_LOCKED:
          mvwprintw(view, mapY+roomHeight/2-1, mapX, "╝");
          mvwprintw(view, mapY+roomHeight/2,   mapX, "X");
          mvwprintw(view, mapY+roomHeight/2+1, mapX, "╗");
          break;
      }

      if (room.hasKey) {
        mvwprintw(view, mapY+1, mapX+roomWidth/2, "🔑");
      }

      // Player graphic
      if (positionToEquals(player, areaX, areaY)) {
        mvwprintw(view, mapY+roomHeight/2, mapX+roomWidth/2, "👳");
        switch(player->direction) {
          case D_UP:
            mvwprintw(view, mapY+roomHeight/2-1, mapX+roomWidth/2, "↑");
            break;
          case D_RIGHT:
            mvwprintw(view, mapY+roomHeight/2, mapX+roomWidth/2+2, "→");
            break;
          case D_DOWN:
            mvwprintw(view, mapY+roomHeight/2+1, mapX+roomWidth/2, "↓");
            break;
          case D_LEFT:
            mvwprintw(view, mapY+roomHeight/2, mapX+roomWidth/2-2, "←");
            break;
        }
      }

      for (int i=1; i < roomHeight-1; i++) {
        mvwprintw(view, mapY+i, mapX+roomWidth-1, "║");
      };
      switch(room.doorInfo[D_RIGHT]){
        case DC_NIL:
          break;
        case DC_OPEN:
          mvwprintw(view, mapY+roomHeight/2-1, mapX+roomWidth-1, "╚");
          mvwprintw(view, mapY+roomHeight/2,   mapX+roomWidth-1, " ");
          mvwprintw(view, mapY+roomHeight/2+1, mapX+roomWidth-1, "╔");
          break;
        case DC_LOCKED:
          mvwprintw(view, mapY+roomHeight/2-1, mapX+roomWidth-1, "╚");
          mvwprintw(view, mapY+roomHeight/2,   mapX+roomWidth-1, "X");
          mvwprintw(view, mapY+roomHeight/2+1, mapX+roomWidth-1, "╔");
          break;
      }

      switch(room.doorInfo[D_DOWN]){
        case DC_NIL:
          mvwprintw(view, mapY+roomHeight-1, mapX, seqStr(roomWidth, "╚", "═", "╝").c_str());
          break;
        case DC_OPEN:
          mvwprintw(view, mapY+roomHeight-1, mapX, (
            seqStr(roomWidth/2, "╚", "═", "╗") +
            " " +
            seqStr(roomWidth/2, "╔", "═", "╝")
          ).c_str());
          break;
        case DC_LOCKED:
          mvwprintw(view, mapY+roomHeight-1, mapX, (
            seqStr(roomWidth/2, "╚", "═", "╗") +
            "X" +
            seqStr(roomWidth/2, "╔", "═", "╝")
          ).c_str());
          break;
      }
    }
  }
}
