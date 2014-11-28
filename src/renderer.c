#include <stdio.h>
#include "renderer.h"

int positionToEquals(struct Player* p, int r_x, int r_y) {
  if ( p->x == r_x && p->y == r_y ) {
    return 1;
  } else {
    return 0;
  }
}

// Rendering map
void render(struct Room area[2][MAX_WIDTH][MAX_HEIGHT], struct Player* player) {
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
