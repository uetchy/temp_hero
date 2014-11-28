#include <string.h>
#include "define.h"


void initialiseArea(struct Room area[2][MAX_WIDTH][MAX_HEIGHT], struct Player player) {

  // Potion location
  area[ 0 ][ 5 ][ 5 ].hasPotion = 1;
  area[ 0 ][ 5 ][ 3 ].hasPotion = 1;
  area[ 0 ][ 3 ][ 4 ].hasPotion = 1;
  area[ 1 ][ 6 ][ 4 ].hasPotion = 1;
  area[ 1 ][ 3 ][ 2 ].hasPotion = 1;

  // Key location
  area[ 0 ][ 8 ][ 8 ].hasKey = 1;
  area[ 1 ][ 7 ][ 8 ].hasKey = 1;

  // Hint location
  strcpy(area[ 0 ][ 7 ][ 4 ].hint, "this is a hint");
  strcpy(area[ 0 ][ 7 ][ 1 ].hint, "this is a hint");
  strcpy(area[ 0 ][ 3 ][ 6 ].hint, "this is a hint");
  strcpy(area[ 0 ][ 8 ][ 8 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 4 ][ 6 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 1 ][ 4 ].hint, "this is a hint");
  strcpy(area[ 1 ][ 6 ][ 8 ].hint, "this is a hint");

  // Stair location
  area[ 0 ][ 7 ][ 4 ].canJump;
  
  
  // Unique boss location
  area[ 1 ][ 8 ][ 8 ].uniqueBossId = 1; // Hidden-boos
  area[ 1 ][ 6 ][ 1 ].uniqueBossId = 0; // Boss

  // Player visited
  for ( int a; a <= 2; a++ )
    for ( int x; x <= 8; x++ )
      for ( int y; y <= 8; y++ )
        area[a][x][y].playerVisited = 0;


  // Area 1 door location
  // Row 1
  area[ 0 ][ 7 ][ 1 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 7 ][ 1 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 7 ][ 1 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 7 ][ 1 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 2
  area[ 0 ][ 3 ][ 2 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 3 ][ 2 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 3 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 4 ][ 2 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 4 ][ 2 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 4 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 4 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 2 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 7 ][ 2 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 7 ][ 2 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 2 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 2 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 3
  area[ 0 ][ 5 ][ 3 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 5 ][ 3 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 3 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 6 ][ 3 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 3 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 4
  area[ 0 ][ 3 ][ 4 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 3 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 3 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 4 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 4 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 5 ][ 4 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 7 ][ 4 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 7 ][ 4 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 4 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 8 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 8 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 8 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;

  // Row 5
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 5 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 7 ][ 5 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 7 ][ 5 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 5 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 5 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 6
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 3 ][ 6 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 4 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 4 ][ 6 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 4 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 6 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 5 ][ 6 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 5 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 5 ][ 6 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 5 ][ 6 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 6 ][ 6 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 6 ][ 6 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 6 ][ 6 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 0 ][ 6 ][ 6 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 7 ][ 6 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 7 ][ 6 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 7 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 7 ][ 6 ].doorInfo[ D_DOWN ] = DC_OPEN;

  area[ 0 ][ 8 ][ 6 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 0 ][ 8 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 8 ][ 6 ].doorInfo[ D_RIGHT ] = DC_NIL;

  // Row 7
  area[ 0 ][ 4 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 4 ][ 7 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 7 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 8 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 8 ][ 7 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 0 ][ 8 ][ 7 ].doorInfo[ D_RIGHT ] = DC_OPEN;

  // Row 8
  area[ 0 ][ 4 ][ 8 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 4 ][ 8 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 4 ][ 8 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 0 ][ 4 ][ 8 ].doorInfo[ D_DOWN ] = DC_NIL;

  area[ 0 ][ 8 ][ 8 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 0 ][ 8 ][ 8 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 0 ][ 8 ][ 8 ].doorInfo[ D_RIGHT ] = DC_LOCKED;

  // Area 2 door
  // 1行列目

  // area[ 1 ] (6,1)
  area[ 1 ][ 6 ][ 1 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 6 ][ 1 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 6 ][ 1 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 6 ][ 1 ].doorInfo[ D_DOWN ] = DC_NIL;


  // 2行列目

  // area[ 1 ] (3,2)
  area[ 1 ][ 3 ][ 2 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 3 ][ 2 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 3 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (4,2)
  area[ 1 ][ 4 ][ 2 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 4 ][ 2 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 4 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 4 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (5,2)
  area[ 1 ][ 5 ][ 2 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 5 ][ 2 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 5 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 5 ][ 2 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (6,2)
  area[ 1 ][ 6 ][ 2 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 6 ][ 2 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 6 ][ 2 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 6 ][ 2 ].doorInfo[ D_DOWN ] = DC_NIL;
  
  // ３行列目

  // area[ 1 ] (3,4)
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_DOWN ] = DC_NIL;
  
  // ４行列目

  // area[ 1 ] (1,4)
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_DOWN ] = DC_NIL;

  // area[ 1 ] (1,4)
  area[ 1 ][ 1 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 1 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 1 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 1 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (2,4)
  area[ 1 ][ 2 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 2 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 2 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 2 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (3,4)
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 3 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (4,4)
  area[ 1 ][ 4 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 4 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 4 ][ 4 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (5,4)
  area[ 1 ][ 5 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 5 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 5 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 5 ][ 4 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (6,4)
  area[ 1 ][ 6 ][ 4 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 6 ][ 4 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 6 ][ 4 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 6 ][ 4 ].doorInfo[ D_DOWN ] = DC_NIL;

  // ５行列目

  // area[ 1 ] (4,5)
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 5 ].doorInfo[ D_DOWN ] = DC_NIL;

  //６行列目

  // area[ 1 ] (4,6)
  area[ 1 ][ 4 ][ 6 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 4 ][ 6 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 6 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (5,6)
  area[ 1 ][ 5 ][ 6 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 5 ][ 6 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 5 ][ 6 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 5 ][ 6 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (6,6)
  area[ 1 ][ 6 ][ 6 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 6 ][ 6 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 6 ][ 6 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 6 ][ 6 ].doorInfo[ D_DOWN ] = DC_NIL;

  //７行列目

  // area[ 1 ] (4,7)
  area[ 1 ][ 4 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 4 ][ 7 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 7 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

  // area[ 1 ] (6,7)
  area[ 1 ][ 6 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 6 ][ 7 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 6 ][ 7 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 6 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

  // area[ 1 ] (4,7)
  area[ 1 ][ 4 ][ 7 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 4 ][ 7 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 7 ].doorInfo[ D_RIGHT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 7 ].doorInfo[ D_DOWN ] = DC_NIL;

  // Row 8
  // area[ 1 ] (1,8)  
  area[ 1 ][ 1 ][ 8 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 1 ][ 8 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 1 ][ 8 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 1 ][ 8 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (2,8)
  area[ 1 ][ 2 ][ 8 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 2 ][ 8 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 2 ][ 8 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 2 ][ 8 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (3,8)
  area[ 1 ][ 3 ][ 8 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 3 ][ 8 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 3 ][ 8 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 3 ][ 8 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (4,8)
  area[ 1 ][ 4 ][ 8 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 4 ][ 8 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 4 ][ 8 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 4 ][ 8 ].doorInfo[ D_DOWN ] = DC_NIL;

  // area[ 1 ] (6,8)
  area[ 1 ][ 6 ][ 8 ].doorInfo[ D_UP ] = DC_NIL;
  area[ 1 ][ 6 ][ 8 ].doorInfo[ D_LEFT ] = DC_OPEN;
  area[ 1 ][ 6 ][ 8 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 6 ][ 8 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (7,8)
  area[ 1 ][ 7 ][ 8 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 7 ][ 8 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 7 ][ 8 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 7 ][ 8 ].doorInfo[ D_DOWN ] = DC_OPEN;

  // area[ 1 ] (8,8)
  area[ 1 ][ 8 ][ 8 ].doorInfo[ D_UP ] = DC_OPEN;
  area[ 1 ][ 8 ][ 8 ].doorInfo[ D_LEFT ] = DC_NIL;
  area[ 1 ][ 8 ][ 8 ].doorInfo[ D_RIGHT ] = DC_NIL;
  area[ 1 ][ 8 ][ 8 ].doorInfo[ D_DOWN ] = DC_NIL;
}
