#include <stdio.h>
#include <string.h>
#include "define.h"

// Initializer variables
struct Room area[2][8][8];
struct Player player;

int main( void ) {
	// Temporary variables
	char c; // Input

	// Initialize
	initialiseArea(area);
	initializePlayer(player);

	printf("start render");

	render();

	// Game Loop
	// while( 1 ) {
	// 	// render();
	// 	// checkEncountGauge(); // Zakoがいるなら戦闘

	// 	// tryDrinkPotion();						// ポーションがあるか、使うかのチェック
	// 	// tryReadHint();							// ヒントあるかどうか
	// 	// tryTakeKey();								// 鍵があるかどうか
	// 	// moveDirection = getUserMove();			// ユーザーから移動方向を入力してもらう
	// 	// movePlayer( moveDirection );			// ユーザが選んだ方向にプリンスを移動させる

	// }

	// TODO: 勝利条件
	// printf( "*************\n" );
	// printf( "* GAME OVER *\n" );
	// printf( "*************\n\n" );
	// if( rescuedPrincess )
	// {
	// 	printf( "Boss: You might have defeated me, but it's not the end.\n" );
	// 	printf( "You have defeated this dungeon boss and you managed to escape from this dungeon.\n" );
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

// Rendering map
void render() {
	int x, y;

	// 部屋を一つずつ表示する
	for( y = 1; y <= 8; y++ ) {

		// 1列目：北ドア
		for( x = 1; x <= 8; x++ ) {
			if( area[ player.c_area ][ x ][ y ].doorInfo[ D_UP ] == DC_NIL ) {
				printf( "*******" );
			}
			else if( area[ player.c_area ][ x ][ y ].doorInfo[ D_UP ] == DC_OPEN ) {
				printf( "***D***" );
			}
			else if( area[ player.c_area ][ x ][ y ].doorInfo[ D_UP ] == DC_LOCKED ) {
				printf( "***L***" );
			}
		}
		printf( "\n" );

		// 2列目：見やすくするための空きスペース
		for( x = 1; x <= 8; x++ ) {
			if( area[ player.c_area ][ x ][ y ].playerVisited ) {
				printf( "*     *" );
			} else {
				printf( "       " );
			}
		}
		printf( "\n" );

		// 3列目：鍵と健康ポーション
		for( x = 1; x <= 8; x++ )
		{
			if( area[ player.c_area ][ x ][ y ].playerVisited )
			{
				if( area[ player.c_area ][ x ][ y ].hasKey )
				{
					printf( "* K " );
				}
				else
				{
					printf( "*   " );
				}
				if( area[ player.c_area ][ x ][ y ].hasPotion )
				{
					printf( "H *" );
				}
				else
				{
					printf( "  *" );
				}
			}
			else
			{
				printf( "       " );
			}
		}
		printf( "\n" );
	}

	// 記号の説明
	printf( "P = Player, U = Hidden Boss, B = Boss\n" );
	printf( "K = Key, P! = Player defeated the hidden boss, H = Health potion\n" );
	printf( "D = Open Door, L = Locked door, * = Wall \n" );

	// プリンスの健康状況を表示
	// printf( "Player HP: %d\n", prince.healthPoints );
}
