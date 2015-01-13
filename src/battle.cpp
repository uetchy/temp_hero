#include "battle.hpp"

// PlayerとZakoの戦闘結果
#define EOB_PLAYER_WON 1
#define EOB_PLAYER_LOST 2

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

// Prototypes
int playerAttack( Player*, Monster* );
int enemyAttack( Monster* );

// １回のPlayerとZakoの戦闘シミュレーション
// 戦闘の終了のＨＰを呼び出された関数に伝えるためにポインタplayer->hpを使用
int battle(Player* player, int uniqueBossId) {
	Frame battleFrame(COLS-2, LINES-2, RFOrientation::TOP_LEFT);

	int monster_index;
	switch ( uniqueBossId ) {
		case 1: // Boss
		  monster_index = 0;
		  break;
		case 2: // Hidden boss
		  monster_index = 1;
		  break;
		default: // Zako
		  monster_index = rand() % 10 + 2;
		  break;
	}

	Monster monster = monsters[monster_index];

	int monsterHP = monster.hp;
	int input;
	char c;

	while(1) {
		battleFrame.clear();

		if ( player->hasPotion ) {
			battleFrame.println("ポーションを保持している\n");
		}

		battleFrame.println("どの部位を攻撃しますか？ \n");
		wprintw(battleFrame.getView(), "%s :1 \n", monster.point1);
		wprintw(battleFrame.getView(), "%s :2 \n", monster.point2);

		// 部位は最低2個なので3個以上は判定が必要
		// atoi: char -> int converter
		if (1 != atoi(monster.point3)) {
			wprintw(battleFrame.getView(), "%s :3 \n", monster.point3);
		}
		if (1 != atoi(monster.point4)) {
			wprintw(battleFrame.getView(), "%s :4 \n", monster.point4);
		}

		//プレイヤーがどこを攻撃するか決める　数字が入力される。
		battleFrame.println("数値を入力して下さい：");
		c = getch();
		input = (int)(c - '0');
		battleFrame.println("入力された数値は %d です\n", input);

		// 入力された値が弱点か弱点ではないか判断
		if (input == monster.wp) {
			weakpoint = 1;
		} else if (input <= 4) {
			weakpoint = 0;
		}

		// ポーションを使うと宣言
		if ( !input && player->hasPotion) {
			player->hp += 10;
			player->hasPotion = 0;
			if (player->hp >= MAX_PLAYER_HP) {
				player->hp = MAX_PLAYER_HP;
			}
			battleFrame.println("へーローHP %d \n", player->hp);
			player->hp -= enemyAttack(&monster);
			battleFrame.println("へーローHP %d \n", player->hp);
			// Playerが死んだかどうかのチェック
			if ( player->hp <= 0 ) {
				battleFrame.println("%s 勝利 \n", monster.name);
				return EOB_PLAYER_LOST;
			}

		} else if (input <= 4) {//攻撃すると宣言
			// Playerは攻撃する
			monsterHP -= playerAttack( player, &monster);
			battleFrame.println("雑魚HP %d \n", monsterHP);
			// Zakoを倒したかどうかのチェック
			if ( monsterHP <= 0 ) {
				battleFrame.println("ヒーロー勝利 \n");
				player->hp =player->hp;
				return EOB_PLAYER_WON;
			}

			// Zakoは反撃する
			player->hp -= enemyAttack(&monster);
			battleFrame.println("へーローHP %d \n",player->hp);
			// Playerが死んだかどうかのチェック
			if ( player->hp <= 0 ) {
				battleFrame.println("雑魚勝利 \n");
				return EOB_PLAYER_LOST;
			}
		} else if (input > 4) {//それ以外の数字が入力された
			battleFrame.println("入力の数字が間違っています。 \n");
		}

		refresh();
	}

	return EXIT_SUCCESS;
}

// Player attack func
int playerAttack(Player* player, Monster* monster){
	// 攻撃のダメージ
	int damage = 1;

	// 刀があると攻撃力アップ
	if ( player->beatenHBoss ) {
		damage = damage * 2;
	}
	if ( weakpoint ) {
		damage = damage * 2;
	}

	printw("へーローの攻撃  %dダメージ \n", damage);

	return damage;
}

// Enemy attack func
int enemyAttack(Monster* monster) {
	int damage = monster->power;
	printw("%s の攻撃  %dダメージ \n", monster->name, damage);
	return damage;
}
