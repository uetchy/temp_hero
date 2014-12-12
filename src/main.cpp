#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

#include "define.hpp"
#include "main.hpp"
#include "renderer.hpp"
#include "map.hpp"
#include "player.hpp"
#include "screenplay.hpp"
#include "battle.hpp"

// Prototypes
void gameLoop();
int  getUserMove();
void movePlayer(int);

// Initialize variables
Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT];
Player player;

int main( void ) {
	// Set locale
	// - これを指定しないとncursesが文字化けを引き起こす
	setlocale(LC_ALL, "");

	// Initialize ncurses
	initscr();            // Init window
  noecho();             // Disable input echo
  cbreak();             // Turn into Non-Canonical mode
  clear();              // Clear whole screen
  curs_set(0);          // Set the cursor invisible
  keypad(stdscr, true); // Enable support for special chars
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_WHITE);

	 // Input
	char c;

	// Initialize
	initMap(area);
	initPlayer(&player);

	area[ player.c_area ][ player.x ][ player.y ].playerVisited = 1;



	// Print title menu
	//
	// print( getTitle(), 100 );

	refresh();

	Frame title_f(LINES-8, RFOrientation::TOP);
	title_f.filledWith("□");
	title_f.print( getTitle(), 50 );

	// Prepare selection frame
	Frame choices_f(4, RFOrientation::BOTTOM);
	choices_f.println( "Press key to select menu.\n");
	choices_f.println("[1] START GAME\n");
	choices_f.println("[2] SHOW RULES\n");
	choices_f.println("[3] ルールを見る\n");

  while (1) {
		// Wait for input
	  c = getch();

		if (c == '1'){ // Start game
			clear();
			refresh();
			gameLoop();
		  break;
		} else if(c == '2'){ // Show rules
			title_f.clear();
			title_f.print( getRulesEN(), 70 );
		} else if(c == '3'){ // Show rules
			title_f.clear();
			title_f.print( getRulesJP(), 70 );
		} else {
			// clearLines(4);
		}

		refresh();
		choices_f.bringToFront();
	}

	// Clear ncurses data structures
	endwin();
	refresh();

	return 0;
}

void checkEncountGauge() {

}

// Game loop
void gameLoop() {
	char c;
	while(1) {

		renderMap(stdscr, area, &player);
		c = getch();
		// checkEncountGauge(); // Zakoがいるなら戦闘
		// tryDrinkPotion(); // ポーションがあるか、使うかのチェック
		// tryReadHint(); // ヒントあるかどうか
		// tryTakeKey(); // 鍵があるかどうか
		// int moveDirection = getUserMove(); // ユーザーから移動方向を入力してもらう
		// movePlayer( moveDirection );
		// battle(&player, area[ player.c_area ][ player.x ][ player.y ].uniqueBossId);
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
		Frame choices_f(4, RFOrientation::BOTTOM);
		choices_f.println( "Enter direction: .\n");
		choices_f.println("[w] Up\n");
		choices_f.println("[a] Left\n");
		choices_f.println("[d] right\n");
		choices_f.println("[s] down\n");
		//printf( "Enter door direction (N,E,S,W): " );
		c = getchar();
		// 改行文字をバッファーから削除
		scanf("%*c");

		// 入力は正しいかどうかを確認
		switch( c ){
		case 'w':
			// 北方向にドアがあれば方向決定
			if( area[ current_area ][ x ][ y ].doorInfo[ D_UP ] == DC_OPEN ){
				direction = D_UP;
				legalDirection = 1;
			}else if( area[ current_area ][ x ][ y ].doorInfo[ D_UP ] == DC_LOCKED ){
				if( player.hasKey ){
					direction = D_UP;
					legalDirection = 1;
				}else{
					printf( "This door is locked. You need key to unlock it\n" );
				}
			}else{
				printf( "You cannot move in this direction\n" );
			}
			break;
		case 'd':
			// 東方向にドアがあれば方向決定
			if( area[ current_area ][ x ][ y ].doorInfo[ D_RIGHT ] == DC_OPEN ){
				direction = D_RIGHT;
				legalDirection = 1;
			}else if( area[ current_area ][ x ][ y ].doorInfo[ D_RIGHT ] == DC_LOCKED ){
				if( player.hasKey ){
					direction = D_RIGHT;
					legalDirection = 1;
				}else{
					printf( "This door is locked. You need key to unlock it\n" );
				}
			}else{
				printf( "You cannot move in this direction\n" );
			}
			break;
		case 's':
			// 南方向にドアがあれば方向決定
			if( area[ current_area ][ x ][ y ].doorInfo[ D_DOWN ] == DC_OPEN ){
				direction = D_DOWN;
				legalDirection = 1;
			}else if( area[ current_area ][ x ][ y ].doorInfo[ D_DOWN ] == DC_LOCKED ){
				if( player.hasKey ){
					direction = D_DOWN;
					legalDirection = 1;
				}else{
					printf( "This door is locked. You need key to unlock it\n" );
				}
			}else{
				printf( "You cannot move in this direction\n" );
			}
			break;
		case 'a':
			// 西方向にドアがあれば方向決定
			if( area[ current_area ][ x ][ y ].doorInfo[ D_LEFT ] == DC_OPEN ){
				direction = D_LEFT;
				legalDirection = 1;
			}else if( area[ current_area ][ x ][ y ].doorInfo[ D_LEFT ] == DC_LOCKED ){
				if( player.hasKey ){
					direction = D_LEFT;
					legalDirection = 1;
				}else{
					printf( "This door is locked. You need key to unlock it\n" );
				}
			}else{
				printf( "You cannot move in this direction\n" );
			}
			break;
		default:
			// 不正入力
			printf( "Illegal input\n" );
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

void signal_handler(int SIG){
  endwin();
  exit(EXIT_FAILURE);
}
