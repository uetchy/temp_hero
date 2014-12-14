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
void gameOver();

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
	title_f.print( centerizedStrings(getTitle()) );

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
			title_f.destroy();
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
		}

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
	int c;
	Frame viewFrame(LINES-2, RFOrientation::TOP);
	Frame textFrame(4, RFOrientation::BOTTOM);

	while(1) {
		renderMap(viewFrame, area, &player);
		viewFrame.bringToFront();

		c = getch();

		// Move
		if (c == KEY_UP){
			if ( isValid(area, player.c_area, player.x, player.y - 1) && area[player.c_area][player.x][player.y].doorInfo[D_UP] == DC_OPEN ) {
				if (player.direction == D_UP) {
					player.y = player.y - 1;
				}
			}
			player.direction = D_UP;
		} else if (c == KEY_RIGHT){
			if ( isValid(area, player.c_area, player.x + 1, player.y) && area[player.c_area][player.x][player.y].doorInfo[D_RIGHT] == DC_OPEN ) {
				if (player.direction == D_RIGHT) {
					player.x = player.x + 1;
				}
			}
			player.direction = D_RIGHT;
		}else if (c == KEY_DOWN){
			if ( isValid(area, player.c_area, player.x, player.y + 1) && area[player.c_area][player.x][player.y].doorInfo[D_DOWN] == DC_OPEN ) {
				if (player.direction == D_DOWN) {
					player.y = player.y + 1;
				}
			}
			player.direction = D_DOWN;
		} else if (c == KEY_LEFT){
			if ( isValid(area, player.c_area, player.x - 1, player.y) && area[player.c_area][player.x][player.y].doorInfo[D_LEFT] == DC_OPEN ) {
				if (player.direction == D_LEFT) {
					player.x = player.x - 1;
				}
			}
			player.direction = D_LEFT;
		} else if (c == 'b') {
			battle(&player, area[ player.c_area ][ player.x ][ player.y ].uniqueBossId);
		}

		area[player.c_area][player.x][player.y].playerVisited = 1;
		// checkEncountGauge(); // Zakoがいるなら戦闘
		// tryDrinkPotion(); // ポーションがあるか、使うかのチェック
		// tryReadHint(); // ヒントあるかどうか
		// tryTakeKey(); // 鍵があるかどうか
	}
}

// Gameover
void gameOver() {
	printf( "*************\n" );
	printf( "* GAME OVER *\n" );
	printf( "*************\n\n" );
}

void signal_handler(int SIG){
  endwin();
  exit(EXIT_FAILURE);
}
