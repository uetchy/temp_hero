#include "battle.hpp"

Monster monsters[PERSON_NUM] = {
  {"ボス　－　ドラゴン", 25, 3, "顔", "舌", "足", "尻尾", 4},
  {"裏ボス　―　ピッコロ", 20, 3, "アンテナ", "頬", "目", "耳", 1},
  {"ウサギ", 7, 1, "耳", "歯", "足", "尻尾", 2},
  {"コウモリ", 5, 2, "耳", "目", "鼻", "翼", 3},
  {"エイリアン", 3, 1, "アンテナ", "目", "腹", "足", 3},
  {"ゴキブリ", 10, 1, "踏む", "噛む", "燃やす", "殺す", 1},
  {"サソリ", 3, 4, "尻尾", "足", "体", "顔", 4},
  {"双子悪魔", 6, 2, "左悪魔の頭", "左悪魔の体", "右悪魔の頭", "右悪魔の体", 2},
  {"クモ", 4, 2, "足", "頭", "体", "尻", 4},
  {"鳥", 6, 1, "嘴", "目", "翼", "足", 1},
  {"ユニコーン", 7, 2, "角", "目", "胴体", "翼", 1},
  {"ピカチュウ", 1, 1, "ほっぺ", "目", "尻尾", "足", 3}
};

int weakpoint;
int input;
char c;
// int monsterHP;

void printChoices(Frame* frame) {
	frame->println("[a] 攻撃\n");
	frame->println("[s] ポーションを使う");
	frame->update();
}

// １回のPlayerとZakoの戦闘シミュレーション
// 戦闘の終了のＨＰを呼び出された関数に伝えるためにポインタplayer->hpを使用
int battle(Player* player, int uniqueBossId) {
	int monster_index;
	switch ( uniqueBossId ) {
		case 0: // Boss
		  monster_index = 0;
		  break;
		case 1: // Hidden boss
		  monster_index = 1;
		  break;
		default: // Zako
		  monster_index = rand() % 10 + 2;
		  break;
	}

	Monster monster = monsters[monster_index];
	// monsterHP = monster.hp;

	Frame battleFrame(COLS-2, LINES-2, RFOrientation::TOP_LEFT);
	Frame battleTextFrame(COLS-2, 4, RFOrientation::BOTTOM_LEFT);

	battleTextFrame.clear();
	wprintw(battleTextFrame.getView(), "%s があらわれた！ [HP: %d]\n\n", monster.name, monster.hp);
	printChoices(&battleTextFrame);

	while(1) {
		// Wait for input
	  c = getch();

	  if (c == 'a'){ // attack
			battleTextFrame.clear();
			int eob = attack(&battleTextFrame, &battleFrame, player, &monster, (int)(c - '0'));
			if (eob == EOB_PLAYER_WON) {
				if (uniqueBossId == 0) {
					return EOB_PLAYER_BEATEN_BOSS;
				} else if (uniqueBossId == 1) {
					player->beatenHBoss = 1;
				}
				return EOB_PLAYER_WON;
			} else if (eob == EOB_PLAYER_LOST) {
				return EOB_PLAYER_LOST;
			}
		} else if(c == 's'){ // Potion
			battleTextFrame.clear();
			usePotion(&battleTextFrame, player);
		}

		battleTextFrame.clear();
		wprintw(battleTextFrame.getView(), "%s [HP: %d]\n\n", monster.name, monster.hp);
		printChoices(&battleTextFrame);
		battleTextFrame.update();
	}

	return EXIT_SUCCESS;
}

void printPartChoices(Frame* frame, Monster* monster) {
	frame->println("どの部位を攻撃する？\n");
	wprintw(frame->getView(), "[1] %s   [2] %s", monster->point1, monster->point2);

	// 部位は最低2個なので3個以上は判定が必要
	if (1 != atoi(monster->point3)) {
		wprintw(frame->getView(), "   [3] %s", monster->point3);
	}
	if (1 != atoi(monster->point4)) {
		wprintw(frame->getView(), "   [4] %s\n", monster->point4);
	} else {
		frame->println("\n");
	}
}

int attack(Frame* textFrame, Frame* viewFrame, Player* player, Monster* monster, int input) {
	wprintw(textFrame->getView(), "%s [HP: %d]\n\n", monster->name, monster->hp);
	printPartChoices(textFrame, monster);
	textFrame->update();

	c = getch();
	input = (c - '0') % 48;

	// 入力された値が弱点か弱点ではないか判断
	if (input == monster->wp) {
		weakpoint = 1;
	} else if (input <= 4) {
		weakpoint = 0;
	}

	textFrame->clear();

	// Playerの攻撃
	int damage = computeDamage(player);
	int prevMonsterHP = monster->hp;
	monster->hp -= damage;
	wprintw(textFrame->getView(), "%s に %d のダメージを与えた! [モンスターHP: %d -> %d] \n", monster->name, damage, prevMonsterHP, monster->hp);
	textFrame->update();
	getch();

	// Enemyが死んだかどうかのチェック
	if (monster->hp <= 0) {
		wprintw(textFrame->getView(), "%s を打ち倒した!\n", monster->name);
		textFrame->update();
		getch();
		return EOB_PLAYER_WON;
	}

	// Enemyの反撃
	int prevHP = player->hp;
	player->hp -= monster->power;
	wprintw(textFrame->getView(), "勇者は %d のダメージを受けた... [HP: %d -> %d] \n", monster->power, prevHP, player->hp);

	// Playerが死んだかどうかのチェック
	if (player->hp <= 0) {
		textFrame->println("負けた...\n");
		textFrame->update();
		getch();
		return EOB_PLAYER_LOST;
	}

	textFrame->update();
	getch();

	textFrame->clear();
	wprintw(textFrame->getView(), "%s [HP: %d]\n\n", monster->name, monster->hp);
	printPartChoices(textFrame, monster);
	textFrame->update();

	return EOB_IN_BATTLE;
}

void usePotion(Frame* frame, Player* player) {
	if (player->hasPotion) {
		int prevHP = player->hp;
		player->hp += 10;
		if (player->hp >= MAX_PLAYER_HP) {
			player->hp = MAX_PLAYER_HP;
		}

		player->hasPotion = 0;

		wprintw(frame->getView(), "勇者はポーションを使った! [HP: %d -> %d]\n\n", prevHP, player->hp);
		frame->update();
		getch();
	} else {
		frame->println("ポーションを持ってない\n\n");
		frame->update();
		getch();
	}
}

int computeDamage(Player* player) {
	int damage = 1;

	// 刀があると攻撃力アップ
	if ( player->beatenHBoss ) {
		damage = damage * 2;
	}
	if ( weakpoint ) {
		damage = damage * 2;
	}

	return damage;
}
