#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include "define.h"
#include "main.h"
#include "renderer.h"
#include "map.h"
#include "player.h"
#include "screenplay.h"
#include "battle.h"

#define ES_NEXT_LINE_IN_FRAME "\x1b[1B\r\x1b[2C"

// Prototypes
void gameLoop();
int  getUserMove();
void movePlayer(int);

// Initializer variables
Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT];
Player player;

int main( void ) {
	// Set un-canonical mode
	struct termios term, default_term;
	tcgetattr(fileno(stdin), &term);
	default_term = term;
	term.c_lflag &= ~ICANON;
	tcsetattr(fileno(stdin), TCSANOW, &term);

	// Temporary variables
	char c; // Input

	// Initialize
	disableCursor();
	initMap(area);
	initPlayer(&player);

	area[ player.c_area ][ player.x ][ player.y ].playerVisited = 1;

	// Print title menu
	clearScreen();
	printTitle();

	while(1) {
		renderFrame(5);
		printf( "Press key to select menu.%s", ES_NEXT_LINE_IN_FRAME );
		printf( "[1] START GAME%s", ES_NEXT_LINE_IN_FRAME );
		printf( "[2] SHOW RULES%s", ES_NEXT_LINE_IN_FRAME );
		printf( "[3] ルールを見る%s", ES_NEXT_LINE_IN_FRAME );
		printf( ">> " );
		c = getchar();

		if (c == '1'){ // Start game
			clearScreen();
			gameLoop();
		  break;
		} else if(c == '2'){ // Show rules
			clearScreen();
			printRulesEN();
		} else if(c == '3'){ // Show rules
			clearScreen();
			printRulesJP();
		} else {
			clearLines(4);
		}
	}

	tcsetattr(fileno(stdin), TCSANOW, &default_term);
	return 0;
}

// Game loop
void gameLoop() {
	while(1) {
		renderMap(area, &player);
		// checkEncountGauge(); // Zakoがいるなら戦闘
		// tryDrinkPotion(); // ポーションがあるか、使うかのチェック
		// tryReadHint(); // ヒントあるかどうか
		// tryTakeKey(); // 鍵があるかどうか
		// int moveDirection = getUserMove(); // ユーザーから移動方向を入力してもらう
		// movePlayer( moveDirection );
		battle(&player, area[ player.c_area ][ player.x ][ player.y ].uniqueBossId);
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
					printf( "This door is locked. You need two keys to enter\n" );
				}
			}else{
				printf( "You cannot move in this direction\n" );
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
					printf( "This door is locked. You need two keys to enter\n" );
				}
			}else{
				printf( "You cannot move in this direction\n" );
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
					printf( "This door is locked. You need two keys to enter\n" );
				}
			}else{
				printf( "You cannot move in this direction\n" );
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
					printf( "This door is locked. You need two keys to enter\n" );
				}
			}else{
				printf( "You cannot move in this direction\n" );
			}
			break;
		default:
			// 不正入力
			printf( "Illegal door direction\n" );
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
	int victory_status = battle(&player, area[ currentArea ][ newX ][ newY ].uniqueBossId);

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
