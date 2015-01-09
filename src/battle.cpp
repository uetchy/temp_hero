#include "battle.hpp"

// PlayerとZakoの戦闘結果
#define EOB_PLAYER_WON 1
#define EOB_PLAYER_LOST 2

Monster monsters[PERSON_NUM] = {
  {"ボス", 25, 3, "アンテナ", "頬", "目", "耳", 1},
  {"裏ボス", 20, 3, "顔", "腹", "尻", "尻尾", 4},
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
		  monster_index = rand() * 10 + 2;
		  break;
	}

	Monster monster = monsters[monster_index];

	int monsterHP = monster.hp;

	while(1) {
		clear();

		if ( player->hasPotion ) {
			// printw("ポーションを保持している\n");
		}

		// printw("どの部位を攻撃しますか？ \n");
		// printw("%s :1 \n", monster.point1);
		// printw("%s :2 \n", monster.point2);

		// 部位は最低2個なので3個以上は判定が必要
		// atoi: char -> int converter
		if (1 != atoi(monster.point3)) {
			printw("%s :3 \n", monster.point3);
		}
		if (1 != atoi(monster.point4)) {
			printw("%s :4 \n", monster.point4);
		}

		//入力される値を保持するための変数
		int input;
		char tmp[80];

		//プレイヤーがどこを攻撃するか決める　数字が入力される。
		printw("数値を入力して下さい：");
		getnstr(tmp, 1);
		input = atoi(tmp);
		printw("入力された数値は %d です\n", input);

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
			printw("へーローHP %d \n", player->hp);
			player->hp -= enemyAttack(&monster);
			printw("へーローHP %d \n", player->hp);
			// Playerが死んだかどうかのチェック
			if ( player->hp <= 0 ) {
				printw("%s 勝利 \n", monster.name);
				return EOB_PLAYER_LOST;
			}

		} else if (input <= 4) {//攻撃すると宣言
			// Playerは攻撃する
			monsterHP -= playerAttack( player, &monster);
			printw("雑魚HP %d \n", monsterHP);
			// Zakoを倒したかどうかのチェック
			if ( monsterHP <= 0 ) {
				printw("ヒーロー勝利 \n");
				player->hp =player->hp;
				return EOB_PLAYER_WON;
			}

			// Zakoは反撃する
			player->hp -= enemyAttack(&monster);
			printw("へーローHP %d \n",player->hp);
			// Playerが死んだかどうかのチェック
			if ( player->hp <= 0 ) {
				printw("雑魚勝利 \n");
				return EOB_PLAYER_LOST;
			}
		} else if (input > 4) {//それ以外の数字が入力された
			printw("入力の数字が間違っています。 \n");
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
