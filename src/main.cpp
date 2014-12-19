#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include <unistd.h>

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

	refresh();

	Frame title_f(LINES-8, RFOrientation::TOP);
	title_f.filledWith("□");
	title_f.print( centerizedStrings(getTitle()), 50 );

	// Prepare selection frame
	Frame choices_f(4, RFOrientation::BOTTOM);
	choices_f.println( "Press key to select menu.\n");
	choices_f.println("[1] START GAME\n");
	choices_f.println("[2] SHOW RULES\n");
	choices_f.println("[3] ルールを見る\n");

	player.hasKey = 1;

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

		choices_f.update();
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
	Frame inventoryFrame(2, RFOrientation::TOP);

	int hasText = 0;

	renderMap(viewFrame, area, &player);
	viewFrame.update();

	while(1) {
		c = getch();
		if (c == KEY_UP){
			if (isValid(area, player.c_area, player.x, player.y - 1) &&
					area[player.c_area][player.x][player.y].doorInfo[D_UP] == DC_OPEN &&
					player.direction == D_UP) {
				player.y = player.y - 1;
			}
			player.direction = D_UP;
		} else if (c == KEY_RIGHT){
			if (isValid(area, player.c_area, player.x + 1, player.y) &&
					area[player.c_area][player.x][player.y].doorInfo[D_RIGHT] == DC_OPEN &&
					player.direction == D_RIGHT) {
				player.x = player.x + 1;
			} else if (isValid(area, player.c_area, player.x + 1, player.y) &&
								 area[player.c_area][player.x][player.y].doorInfo[D_RIGHT] == DC_LOCKED &&
								 player.hasKey) {
				area[player.c_area][player.x][player.y].doorInfo[D_RIGHT] = DC_OPEN;
				player.hasKey = 0;
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
		}

		hasText = 0;

		// Render view
		if (c == 'b') {
			battle(&player, area[player.c_area][player.x][player.y].uniqueBossId);
		} else if (c == 'z') {
			textFrame.clear();
			if (area[player.c_area][player.x][player.y].hasKey) {
				textFrame.println("キーを見つけた...!");
				hasText = 1;
				player.hasKey = 1;
				area[player.c_area][player.x][player.y].hasKey = 0;
			} else if (area[player.c_area][player.x][player.y].hint != "") {
				textFrame.println("ヒントを見つけた...\n");
				textFrame.println(area[player.c_area][player.x][player.y].hint.c_str());
				hasText = 1;
			}else if (area[player.c_area][player.x][player.y].canJump) {
				viewFrame.move(0, 0);
				viewFrame.print(filledWith(viewFrame, "□"), 10);
				player.c_area = 1;
				player.x = 7;
				player.y = 2;
			} else {
				textFrame.println("何も無いようだ...");
				hasText = 1;
			}
		}

		area[player.c_area][player.x][player.y].playerVisited = 1;

		renderMap(viewFrame, area, &player);
		viewFrame.update();
		if (hasText) textFrame.update();

		if (player.hasKey) {
			inventoryFrame.clear();
			inventoryFrame.println("🔑");
			inventoryFrame.update();
		}

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
