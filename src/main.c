#include <stdio.h>
#include <string.h>

#include "define.h"
#include "map.h"
#include "player.h"
#include "image.h"

// Initializer variables
struct Room area[2][MAX_WIDTH][MAX_HEIGHT];
struct Player player;

int main( void ) {
	// Temporary variables
	char c; // Input

	// Initialize
	initMap(area);
	initPlayer(&player);

	area[ player.c_area ][ player.x ][ player.y ].playerVisited = 1;

	printTitle();

	// Game loop
	while( 1 ) {
		// renderMap(area, &player);
		// checkEncountGauge(); // Zakoがいるなら戦闘

		// tryDrinkPotion();						// ポーションがあるか、使うかのチェック
		// tryReadHint();							// ヒントあるかどうか
		// tryTakeKey();								// 鍵があるかどうか
		// moveDirection = getUserMove();			// ユーザーから移動方向を入力してもらう
		// movePlayer( moveDirection );			// ユーザが選んだ方向にプリンスを移動させる

		// Await user input
		printf( "\nPress any key to continue.\n" );
		c = getchar();
	}

	// ユーザーから移動方向を入力してもらう
// int getUserMove() {
// 	int direction = -1;
// 	int legalDirection = 0;
// 	char c;
// 	int x = prince.roomX;
// 	int y = prince.roomY;

// 	// 正しい方向が入力されてないまで繰り返す
// 	while( !legalDirection ) {
// 		// ユーザーから方向を入力
// 		printf( "Enter door direction (N,E,S,W): " );
// 		c = getchar();
// 		// 改行文字をバッファーから削除
// 		scanf("%*c");

// 		// 入力は正しいかどうかを確認
// 		switch( c )
// 		{
// 		case 'N':
// 			// 北方向にドアがあれば方向決定
// 			if( dungeon[ x ][ y ].doorInfo[ North ] == openDoor )
// 			{
// 				direction = North;
// 				legalDirection = 1;
// 			}
// 			else if( dungeon[ x ][ y ].doorInfo[ North ] == lockedDoor )
// 			{
// 				if( prince.keyNumber == 2 )
// 				{
// 					direction = North;
// 					legalDirection = 1;
// 				}
// 				else
// 				{
// 					printf( "This door is locked. You need two keys to enter¥n" );
// 				}
// 			}
// 			else
// 			{
// 				printf( "You cannot move in this direction¥n" );
// 			}
// 			break;
// 		case 'E':
// 			// 東方向にドアがあれば方向決定
// 			if( dungeon[ x ][ y ].doorInfo[ East ] == openDoor )
// 			{
// 				direction = East;
// 				legalDirection = 1;
// 			}
// 			else if( dungeon[ x ][ y ].doorInfo[ East ] == lockedDoor )
// 			{
// 				if( prince.keyNumber == 2 )
// 				{
// 					direction = East;
// 					legalDirection = 1;
// 				}
// 				else
// 				{
// 					printf( "This door is locked. You need two keys to enter¥n" );
// 				}
// 			}
// 			else
// 			{
// 				printf( "You cannot move in this direction¥n" );
// 			}
// 			break;
// 		case 'S':
// 			// 南方向にドアがあれば方向決定
// 			if( dungeon[ x ][ y ].doorInfo[ South ] == openDoor )
// 			{
// 				direction = South;
// 				legalDirection = 1;
// 			}
// 			else if( dungeon[ x ][ y ].doorInfo[ South ] == lockedDoor )
// 			{
// 				if( prince.keyNumber == 2 )
// 				{
// 					direction = South;
// 					legalDirection = 1;
// 				}
// 				else
// 				{
// 					printf( "This door is locked. You need two keys to enter¥n" );
// 				}
// 			}
// 			else
// 			{
// 				printf( "You cannot move in this direction¥n" );
// 			}
// 			break;
// 		case 'W':
// 			// 西方向にドアがあれば方向決定
// 			if( dungeon[ x ][ y ].doorInfo[ West ] == openDoor )
// 			{
// 				direction = West;
// 				legalDirection = 1;
// 			}
// 			else if( dungeon[ x ][ y ].doorInfo[ West ] == lockedDoor )
// 			{
// 				if( prince.keyNumber == 2 )
// 				{
// 					direction = West;
// 					legalDirection = 1;
// 				}
// 				else
// 				{
// 					printf( "This door is locked. You need two keys to enter¥n" );
// 				}
// 			}
// 			else
// 			{
// 				printf( "You cannot move in this direction¥n" );
// 			}
// 			break;
// 		default:
// 			// 不正入力
// 			printf( "Illegal door direction¥n" );
// 			break;
// 		}
// 	}

// 	return direction;
// }

// // ユーザが選んだ方向にプリンスを移動させる
// void movePrince( int direction )
// {
// 	int currentX = prince.roomX;
// 	int currentY = prince.roomY;
// 	int newX, newY;

// 	//　プリンスを元の部屋から消す
// 	dungeon[ currentX ][ currentY ].hasPrince = 0;

// 	//　新しい部屋のX軸とY軸を方向から獲得
// 	if( direction == North )
// 	{
// 		newX = currentX;
// 		newY = currentY - 1;
// 	}
// 	else if( direction == East )
// 	{
// 		newX = currentX + 1;
// 		newY = currentY;
// 	}
// 	else if( direction == South )
// 	{
// 		newX = currentX;
// 		newY = currentY + 1;
// 	}
// 	else if( direction == West )
// 	{
// 		newX = currentX - 1;
// 		newY = currentY;
// 	}

// 	// 新しい場所の情報を追加
// 	prince.roomX = newX;
// 	prince.roomY = newY;
// 	dungeon[ newX ][ newY ].hasPrince = 1;
// 	dungeon[ newX ][ newY ].princeVisited = 1;

// }

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

	return 0;
}
