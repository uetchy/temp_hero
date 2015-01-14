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
void gameOver(Frame* frame);
void gameWon(Frame* frame);

void renderInventory(Frame* inventoryFrame, Player* player);
void renderStatus(Frame* frame, Player* player);
int checkEncountGauge(Frame* viewFrame, Frame* inventoryFrame, Frame* statusFrame);

// Initialize variables
Room area[MAX_AREA][MAX_WIDTH][MAX_HEIGHT];
Player player;

int encountGauge;
int plA;
int plX;
int plY;

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

	encountGauge = 0;

	refresh();

	// Prepare title frame
	Frame title_f(COLS-2, LINES-8, RFOrientation::TOP_LEFT);
	title_f.filledWith("□");
	title_f.print( centerizedStrings(getTitle()), 50 );

	// Prepare selection frame
	Frame choices_f(COLS-2, 4, RFOrientation::BOTTOM_LEFT);
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
			title_f.clear();
			title_f.filledWith("□");
			title_f.print( centerizedStrings(getTitle()), 50 );
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

int battleSequence(Frame* frame) {
	frame->move(0, 0);
	frame->print(filledWith(*frame, "□"), 15);
	int eob = battle(&player, area[player.c_area][player.x][player.y].uniqueBossId);
	return eob;
}

int checkEncountGauge(Frame* frame, Frame* inventoryFrame, Frame* statusFrame) {
	encountGauge += 1;

	if (encountGauge > 8) {
		int eob = battleSequence(frame);
		encountGauge = 0;
		renderMap(*frame, area, &player);
		frame->update();
		renderInventory(inventoryFrame, &player);
		renderStatus(statusFrame, &player);
		return eob;
	}

	return -1;
}

void renderInventory(Frame* frame, Player* player) {
	frame->clear();
	frame->println("持ち物\n");
	frame->println("=============\n");
	if (player->hasKey) {
		frame->println("🔑   キー\n");
	}
	if (player->hasPotion) {
		frame->println("💉   ポーション");
	}
	frame->update();
}

void renderStatus(Frame* frame, Player* player) {
	frame->clear();
	wprintw(frame->getView(), "HP: %d/15", player->hp);
	frame->update();
}

// Game loop
void gameLoop() {
	int c; // char

	// Init frames
	Frame viewFrame(COLS-2, LINES-2, RFOrientation::TOP_LEFT);
	Frame textFrame(COLS-2, 4, RFOrientation::BOTTOM_LEFT);
	Frame inventoryFrame(18, 4, RFOrientation::BOTTOM_RIGHT);
	Frame statusFrame(15, 4, RFOrientation::TOP_RIGHT);

	int hasText = 0;
	int showedHint = 0;
	int showedNothingMessage = 0;
	plA = player.c_area;
	plX = player.x;
	plY = player.y;

	renderMap(viewFrame, area, &player);
	viewFrame.update();
	renderInventory(&inventoryFrame, &player);
	renderStatus(&statusFrame, &player);

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
			} else if (isValid(area, player.c_area, player.y + 1, player.y) &&
								 area[player.c_area][player.x][player.y].doorInfo[D_DOWN] == DC_LOCKED &&
								 player.hasKey) {
				area[player.c_area][player.x][player.y].doorInfo[D_DOWN] = DC_OPEN;
				player.hasKey = 0;
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
		if (c == 'z') {
			textFrame.clear();
			if (area[player.c_area][player.x][player.y].hasKey) {
				textFrame.println("キーを見つけた...!");
				hasText = 1;
				player.hasKey = 1;
				area[player.c_area][player.x][player.y].hasKey = 0;
			} else if (area[player.c_area][player.x][player.y].hint != "" && !showedHint) {
				textFrame.println("ヒントを見つけた...\n");
				textFrame.println(area[player.c_area][player.x][player.y].hint.c_str());
				showedHint = 1;
				showedNothingMessage = 1;
				hasText = 1;
			} else if (area[player.c_area][player.x][player.y].hasPotion && player.hasPotion) {
				textFrame.println("ポーション見つけたが、持てない...");
				hasText = 1;
			} else if (area[player.c_area][player.x][player.y].hasPotion) {
				textFrame.println("ポーション見つけた...!");
				hasText = 1;
				player.hasPotion = 1;
				area[player.c_area][player.x][player.y].hasPotion = 0;
			} else if (area[player.c_area][player.x][player.y].canJump) {
				viewFrame.move(0, 0);
				viewFrame.print(filledWith(viewFrame, "□"), 10);
				player.c_area = 1;
				player.x = 7;
				player.y = 2;
			} else if (!showedNothingMessage) {
				textFrame.println("何も無いようだ...");
				showedNothingMessage = 1;
				hasText = 1;
			} else {
				showedNothingMessage = 0;
				hasText = 0;
				showedHint = 0;
			}
		} else if (c == 's') {
			textFrame.clear();
			if (player.hasPotion) {
				textFrame.println("ポーション使う...?");
				textFrame.println("z = はい");
				textFrame.println("x = いいえ");
				while(1) {
					c = getch();
					if (c == 'z') {
						textFrame.clear();
						textFrame.println("ポーション使いました...");
						textFrame.println("HP全回しました");
						player.hp = 15;
						hasText = 1;
						player.hasPotion = 0;
						break;
					} else if (c == 'x'){
						textFrame.clear();
						textFrame.println("ポーション使うのをやめた...");
						textFrame.println("HP全回しました、なんてウソです");
						hasText = 1;
						break;
					}
				}
			} else if (!player.hasPotion) {
				textFrame.println("ポーションない...");
				hasText = 1;
			}
		}

		area[player.c_area][player.x][player.y].playerVisited = 1;

		renderMap(viewFrame, area, &player);
		viewFrame.update();
		if (hasText) textFrame.update();

		renderInventory(&inventoryFrame, &player);
		renderStatus(&statusFrame, &player);

		// 前回描画した時からプレイヤーは移動したか？
		if (isPlayerMoved(plA, plX, plY, player.c_area, player.x, player.y)) {
			// Zakoがいるなら戦闘
			int eob = checkEncountGauge(&viewFrame, &inventoryFrame, &statusFrame);
			if (eob == EOB_PLAYER_LOST) {
				gameOver(&viewFrame);
				return;
			}
		}

		// 特殊ボス会敵
		if (area[player.c_area][player.x][player.y].uniqueBossId > -1) {
			int eob = battleSequence(&viewFrame);
			if (eob == EOB_PLAYER_LOST) {
				gameOver(&viewFrame);
				return;
			} else if (eob == EOB_PLAYER_BEATEN_BOSS) {
				gameWon(&viewFrame);
				return;
			}
		}

		plA = player.c_area;
		plX = player.x;
		plY = player.y;
	}
}

// Gameover
void gameOver(Frame* frame) {
	frame->clear();
	std::vector<std::string> str = {
		"\n",
		"\n",
		"\n",
		"*************\n",
		"* GAME OVER *\n",
		"*************\n"
	};
	frame->print(centerizedStrings(str));
	frame->update();
	getch();
}

void gameWon(Frame* frame) {
	frame->clear();
	std::vector<std::string> str = {
		"\n",
		"\n",
		"\n",
		"*************\n",
		"* GAME WON! *\n",
		"*************\n"
	};
	frame->print(centerizedStrings(str));
	frame->update();
	getch();
}

void signal_handler(int SIG){
  endwin();
  exit(EXIT_FAILURE);
}
