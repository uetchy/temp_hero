#include <stdio.h>
#include <string.h>
#include "define.h"
#include "area.h"
#include "player.h"
#include "renderer.h"

// Initializer variables
struct Room area[2][MAX_WIDTH][MAX_HEIGHT];
struct Player player;

int main( void ) {
	// Temporary variables
	char c; // Input

	// Initialize
	initialiseArea(area);
	initializePlayer(&player);

	area[ player.c_area ][ player.x ][ player.y ].playerVisited = 1;


	// Game loop
	while( 1 ) {
		render(area, &player);
		// checkEncountGauge(); // Zakoがいるなら戦闘

		// tryDrinkPotion();						// ポーションがあるか、使うかのチェック
		// tryReadHint();							// ヒントあるかどうか
		// tryTakeKey();								// 鍵があるかどうか
		// moveDirection = getUserMove();			// ユーザーから移動方向を入力してもらう
		// movePlayer( moveDirection );			// ユーザが選んだ方向にプリンスを移動させる

	}

	// TODO: 勝利条件
	// printf( "*************\n" );
	// printf( "* GAME OVER *\n" );
	// printf( "*************\n\n" );
	// if( rescuedPrincess )
	// {
	// 	printf( "Boss: You might have defeated me, but it's not the end.\n" );
	// 	printf( "You have defeated this area[ player.c_area ] boss and you managed to escape from this area[ player.c_area ].\n" );
	// 	printf( "But the Hero's tale is just begin.\n" );
	// }
	// else
	// {
	// 	printf( "You died in battle and your body is eaten by the monsters.\n" );
	// 	printf( "Of course, the world is destroyed.\n" );
	// }

	// Await user input
	printf( "\nPress any key to continue.\n" );
	c = getchar();

	return 0;
}
