#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define.h"
#include "map.h"
#include "player.h"
#include "image.h"
#include "../config.h"

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
		renderMap(area, &player);
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
}
void showRoomInfo()
{
	int x = prince.roomX;
	int y = prince.roomY;

	
	// この部屋に刀があることを表示
	if( dungeon[ x ][ y ].hasSword )
	{
		printf( "There is a sword in this room\n" );
	}
	// この部屋に健康ポーションがあることを表示
	if( dungeon[ x ][ y ].healthPotion )
	{
		printf( "There is a health potion in this room\n" );
	}
	// この部屋の匂いを表示
	if( dungeon[ x ][ y ].stinkerSmell1 || dungeon[ x ][ y ].stinkerSmell2 )
	{
		printf( "There is a bad smell in this room\n" );
	}
	if( dungeon[ x ][ y ].superStinkerSmell )
	{
		printf( "There is a very foul stench in this room\n" );
	}
	if( !dungeon[ x ][ y ].stinkerSmell1 && !dungeon[ x ][ y ].stinkerSmell2 &&
		!dungeon[ x ][ y ].superStinkerSmell )
	{
		printf( "There is no smell in this room\n" );
	}
	// この部屋のドア情報を表示
	if( dungeon[ x ][ y ].doorInfo[ North ] == openDoor )
	{
		printf( "There is a door to the North\n" );
	}
	else if( dungeon[ x ][ y ].doorInfo[ North ] == lockedDoor )
	{
		printf( "There is a locked door to the North\n" );
	}
	if( dungeon[ x ][ y ].doorInfo[ East ] == openDoor )
	{
		printf( "There is a door to the East\n" );
	}
	else if( dungeon[ x ][ y ].doorInfo[ East ] == lockedDoor )
	{
		printf( "There is a locked door to the East\n" );
	}
	if( dungeon[ x ][ y ].doorInfo[ South ] == openDoor )
	{
		printf( "There is a door to the South\n" );
	}
	else if( dungeon[ x ][ y ].doorInfo[ South ] == lockedDoor )
	{
		printf( "There is a locked door to the South\n" );
	}
	if( dungeon[ x ][ y ].doorInfo[ West ] == openDoor )
	{
		printf( "There is a door to the West\n" );
	}
	else if( dungeon[ x ][ y ].doorInfo[ West ] == lockedDoor )
	{
		printf( "There is a locked door to the West\n" );
	}
}
	// ユーザーから移動方向を入力してもらう
int getUserMove() {
	int direction = -1;
	int current_area = player.c_area;
	int legalDirection = 0;
	char c;
	int x = player.x;
	int y = player.y;

	// 正しい方向が入力されてないまで繰り返す
	while( !legalDirection ) {
		// ユーザーから方向を入力
		printf( "Enter door direction (N,E,S,W): " );
		c = getchar();
		// 改行文字をバッファーから削除
		scanf("%*c");

		// 入力は正しいかどうかを確認
		switch( c ){
		case 'N':
			// 北方向にドアがあれば方向決定
			if( area[ current_area ][ x ][ y ].doorInfo[ D_UP ] == DC_OPEN ){
				direction = D_UP;
				legalDirection = 1;
			}else if( area[ current_area ][ x ][ y ].doorInfo[ D_UP ] == DC_LOCKED ){
				if( player.hasKey ){
					direction = D_UP;
					legalDirection = 1;
				}else{
					printf( "This door is locked. You need two keys to enter¥n" );
				}
			}else{
				printf( "You cannot move in this direction¥n" );
			}
			break;
		case 'E':
			// 東方向にドアがあれば方向決定
			if( area[ current_area ][ x ][ y ].doorInfo[ D_RIGHT ] == DC_OPEN ){
				direction = D_RIGHT;
				legalDirection = 1;
			}else if( area[ current_area ][ x ][ y ].doorInfo[ D_RIGHT ] == DC_LOCKED ){
				if( player.hasKey ){
					direction = D_RIGHT;
					legalDirection = 1;
				}else{
					printf( "This door is locked. You need two keys to enter¥n" );
				}
			}else{
				printf( "You cannot move in this direction¥n" );
			}
			break;
		case 'S':
			// 南方向にドアがあれば方向決定
			if( area[ current_area ][ x ][ y ].doorInfo[ D_DOWN ] == DC_OPEN ){
				direction = D_DOWN;
				legalDirection = 1;
			}else if( area[ current_area ][ x ][ y ].doorInfo[ D_DOWN ] == DC_LOCKED ){
				if( player.hasKey ){
					direction = D_DOWN;
					legalDirection = 1;
				}else{
					printf( "This door is locked. You need two keys to enter¥n" );
				}
			}else{
				printf( "You cannot move in this direction¥n" );
			}
			break;
		case 'W':
			// 西方向にドアがあれば方向決定
			if( area[ current_area ][ x ][ y ].doorInfo[ D_LEFT ] == DC_OPEN ){
				direction = D_LEFT;
				legalDirection = 1;
			}else if( area[ current_area ][ x ][ y ].doorInfo[ D_LEFT ] == DC_LOCKED ){
				if( player.hasKey ){
					direction = D_LEFT;
					legalDirection = 1;
				}else{
					printf( "This door is locked. You need two keys to enter¥n" );
				}
			}else{
				printf( "You cannot move in this direction¥n" );
			}
			break;
		default:
			// 不正入力
			printf( "Illegal door direction¥n" );
			break;
		}
	}

	return direction;
}

// ユーザが選んだ方向にプリンスを移動させる
void movePlayer( int direction ){
	int currentArea = player.c_area;
	int currentX = player.x;
	int currentY = player.y;
	int newX, newY;

	//　新しい部屋のX軸とY軸を方向から獲得
	if( direction == D_UP ){
		newX = currentX;
		newY = currentY - 1;
	}else if( direction == D_RIGHT ){
		newX = currentX + 1;
		newY = currentY;
	}else if( direction == D_DOWN ){
		newX = currentX;
		newY = currentY + 1;
	}else if( direction == D_LEFT ){
		newX = currentX - 1;
		newY = currentY;
	}

	// Apply new location
	player.x = newX;
	player.y = newY;
	area[ currentArea ][ newX ][ newY ].playerVisited = 1;

	// TODO: Battle
	// doBattle();

	// TODO: 勝利条件
	printf( "*************\n" );
	printf( "* GAME OVER *\n" );
	printf( "*************\n\n" );

	// TODO: ちゃんと判定させる
	if( player.beatenBoss ){
		printf( "Boss: You might have defeated me, but it's not the end.\n" );
		printf( "You have defeated this area[ player.c_area ] boss and you managed to escape from this area[ player.c_area ].\n" );
		printf( "But the Hero's tale is just begin.\n" );
	}else{
		printf( "You died in battle and your body is eaten by the monsters.\n" );
		printf( "Of course, the world is destroyed.\n" );
	}
}
