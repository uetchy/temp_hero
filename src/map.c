#include <stdio.h>
#include <string.h>
#include "map.h"

void initMap(struct Room area[2][MAX_WIDTH][MAX_HEIGHT]) {
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
  // area[ 0 ][ 7 ][ 4 ].canJump;


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

int positionToEquals(struct Player* p, int r_x, int r_y) {
  if ( p->x == r_x && p->y == r_y ) {
    return 1;
  } else {
    return 0;
  }
}

// Rendering map
void renderMap(struct Room area[2][MAX_WIDTH][MAX_HEIGHT], struct Player* player) {
  int x, y;

  // Show per room
  for( y = 1; y <= MAX_HEIGHT; y++ ) {

    // 1. North wall
    for( x = 1; x <= MAX_WIDTH; x++ ) {
      if( area[ player->c_area ][ x ][ y ].playerVisited ) {
        if( area[ player->c_area ][ x ][ y ].doorInfo[ D_UP ] == DC_NIL ) {
          printf( "*******" );
        }
        else if( area[ player->c_area ][ x ][ y ].doorInfo[ D_UP ] == DC_OPEN ) {
          printf( "***D***" );
        }
        else if( area[ player->c_area ][ x ][ y ].doorInfo[ D_UP ] == DC_LOCKED ) {
          printf( "***L***" );
        }
      }
      else
      {
        printf( "       " );
      }
    }
    printf( "\n" );

    // 2. White space
    for( x = 1; x <= MAX_WIDTH; x++ ) {
      if( area[ player->c_area ][ x ][ y ].playerVisited ) {
        printf( "*     *" );
      } else {
        printf( "       " );
      }
    }
    printf( "\n" );

    // 3. Visited info
    for ( x = 1; x <= MAX_WIDTH; x++ ) {
      if ( area[ player->c_area ][ x ][ y ].playerVisited ) {
        printf( "*     *" );
      } else {
        printf( "       " );
      }
    }
    printf( "\n" );

    // 4. Door info
    for ( x = 1; x <= MAX_WIDTH; x++ ) {
      if ( area[ player->c_area ][ x ][ y ].playerVisited ) {
        if ( area[ player->c_area ][ x ][ y ].doorInfo[ D_LEFT ] == DC_NIL ) {
          printf( "* " );
        }
        else if( area[ player->c_area ][ x ][ y ].doorInfo[ D_LEFT ] == DC_OPEN ) {
          printf( "D " );
        }
        else if( area[ player->c_area ][ x ][ y ].doorInfo[ D_LEFT ] == DC_LOCKED ) {
          printf( "L " );
        }

        // Indicate player and items
        if ( positionToEquals(player, x, y) ) {
          if ( player->hasPotion ) {
            printf( "Pp" );
          } else {
            printf( "P " );
          }
        }
        else
        {
          printf( "  " );
        }

        // Unique boss indicated?
        if ( area[ player->c_area ][ x ][ y ].uniqueBossId == B_BOSS ) {
          printf( "B " );
        } else if( area[ player->c_area ][ x ][ y ].uniqueBossId == B_HIDDEN_BOSS ) {
          printf( "U " );
        } else {
          printf( "  " );
        }

        // Room has key?
        if ( area[ player->c_area ][ x ][ y ].hasKey ) {
          printf( "K " );
        } else {
          printf( "  " );
        }

        // Door information
        if( area[ player->c_area ][ x ][ y ].doorInfo[ D_RIGHT ] == DC_NIL ) {
          printf( "*" );
        }
        else if( area[ player->c_area ][ x ][ y ].doorInfo[ D_RIGHT ] == DC_OPEN ) {
          printf( "D" );
        }
        else if( area[ player->c_area ][ x ][ y ].doorInfo[ D_RIGHT ] == DC_LOCKED ) {
          printf( "L" );
        }
      }
      else {
        printf( "       " );
      }
    }
    printf( "\n" );

    // 5. Key and Postion
    for ( x = 1; x <= MAX_WIDTH; x++ ) {
      if( area[ player->c_area ][ x ][ y ].playerVisited ) {
        if ( player->hasKey ) {
          printf( "* K " );
        } else {
          printf( "*   " );
        }
        if ( area[ player->c_area ][ x ][ y ].hasPotion ) {
          printf( "p *" );
        } else {
          printf( "  *" );
        }
      } else {
        printf( "       " );
      }
    }
    printf( "\n" );

    // 6. South wall
    for ( x = 1; x <= MAX_WIDTH; x++ ) {
      if ( area[ player->c_area ][ x ][ y ].playerVisited ) {
        if( area[ player->c_area ][ x ][ y ].doorInfo[ D_DOWN ] == DC_NIL ) {
          printf( "*******" );
        }
        else if( area[ player->c_area ][ x ][ y ].doorInfo[ D_DOWN ] == DC_OPEN ) {
          printf( "***D***" );
        }
        else if( area[ player->c_area ][ x ][ y ].doorInfo[ D_DOWN ] == DC_LOCKED ) {
          printf( "***L***" );
        }
      } else {
        printf( "       " );
      }
    }
    printf( "\n" );

  }

  // 記号の説明
  printf( "P = Prince, S = Stinker, $ = Super Stinker\n" );
  printf( "& = Stinker smell, # = Super Stinker smell\n" );
  printf( "K = Sword, P! = Prince has sword, H = Health potion\n" );
  printf( "D = Open Door, L = Locked door, * = Wall \n" );

  // 健康状況を表示
  printf( "\nPlayer HP: %d\n", player->hp );
}
