#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "battle.h"

// Max player hp
#define PERSON_NUM 100
#define MAX_PLAYER_HP 15

Monster monsters[PERSON_NUM] = {
	{"Andy", 3, 2, "EEEE", "??E", "1", "1", 1},
	{"Ue-sama", 4, 2, "Eye", "Throat", "Armpit", "Feet", 2},
	{"Yazaki", 3, 3, "Right Hand", "Right Feet", "1", "1", 2},
	{"Iida", 8, 1, "Laptop", "Mobile Phone", "Hoodies", "1", 3},
	{"Yoshioka", 6, 2, "Hair", "Throat", "Pelvis", "Nose", 4},
	{"Muramatsu", 2, 8, "Hair", "Keyboard", "Mobile Phone", "Mouse", 2},
	{"とらえモン", 5, 1, "Pocket", "Dorayaki", "Tail", "Rat", 2},
	{"ビカチュウ", 2, 4, "Ear", "Eye", "Tail", "Cheek", 4},
	{"ぷにょよ", 3, 2, "邪魔ぷよ", "１れんさ", "５れんさ", "１０れんさ", 4},
	{"matsuko", 10, 1, "Eye", "Throat", "Jaw", "Hair", 3},
	{"ボス", 25, 3, "頭", "腕", "おなか", "えんだ―", 4},
	{"裏ボス", 20, 3, "頭", "顎", "脇腹", "足", 1}
};

// 調整する値はここまで
//==========================================

// PlayerとZakoの戦闘結果
const int princeWins  = 1;
const int princeLoses = 2;

int weakpoint;

int playerAttack( int, int );
int enemyAttack( int );
void initMonsters();

void initMonsters() {

}

// １回のPlayerとZakoの戦闘シミュレーション
// 戦闘の終了のＨＰを呼び出された関数に伝えるためにポインタplayer->hpを使用
int battle(struct Player* player, int uniqueBossId) {
	int mo;

	switch ( uniqueBossId ) {
		case 1: // Boss
		  mo = 10;
		  break;
		case 2: // Hidden boss
		  mo = 11;
		  break;
		default:
		  mo = rand() % 10;
		  break;
	}

	Monster monster = monsters[mo];
	int enemyHP = monster.hp;

	printf( "\nPrince HP: %d\n", player->hp );
	printf( "%s HP: %d\n", monster.name, enemyHP );

	while( 1 ) {
		if ( player->hasPotion ) {
			//プレイヤーのできる行動を指示
			printf("ポーションを使う：0 \n");
		}

		printf("どの部位を攻撃しますか？ \n");
		printf("%s :1 \n", monster.point1);
		printf("%s :2 \n", monster.point2);

		// 部位は最低2個なので3個以上は判定が必要
		// atoi: char -> int converter
		if (1 != atoi(monster.point3)) {
			printf("%s :3 \n", monster.point3);
		}
		if (1 != atoi(monster.point4)) {
			printf("%s :4 \n", monster.point4);
		}

		//入力される値を保持するための変数
		int input;
		char tmp[80];

		//プレイヤーがどこを攻撃するか決める　数字が入力される。
		printf("数値を入力して下さい：");
		gets(tmp);
		input = atoi(tmp);
		printf("入力された数値は %d です\n", input);

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
			printf("へーローHP %d \n", player->hp);
			player->hp -= enemyAttack( mo );
			printf("へーローHP %d \n", player->hp);
			// Playerが死んだかどうかのチェック
			if ( player->hp <= 0 ) {
				printf("%s 勝利 \n", monster.name);
				return princeLoses;
			}

		} else if (input <= 4) {//攻撃すると宣言
			// Playerは攻撃する
			enemyHP -= playerAttack( player->beatenHBoss , weakpoint);
			printf("雑魚HP %d \n", enemyHP);
			// Zakoを倒したかどうかのチェック
			if ( enemyHP <= 0 ) {
				printf("ヒーロー勝利 \n");
				player->hp =player->hp;
				return princeWins;
			}

			// Zakoは反撃する
			player->hp -= enemyAttack( mo );
			printf("へーローHP %d \n",player->hp);
			// Playerが死んだかどうかのチェック
			if ( player->hp <= 0 ) {
				printf("雑魚勝利 \n");
				return princeLoses;
			}
		} else if (input > 4) {//それ以外の数字が入力された
			printf("入力の数字が間違っています。 \n");
		}

	}
	return 0;
}

// Player attack func
int playerAttack( int beatenHBoss, int weakpoint ) {
	// 攻撃のダメージ
	int damage = 1;

	// 刀があると攻撃力アップ
	if ( beatenHBoss ) {
		damage = damage * 2;
	}
	if ( weakpoint ) {
		damage = damage * 2;
	}

	printf("へーローの攻撃  %dダメージ \n", damage);

	return damage;
}

// Enemy attack func
int enemyAttack( int mo ) {
	printf("mo: %d", monsters[mo]);
	int damage = monsters[mo].power;
	printf("%s の攻撃  %dダメージ \n", monsters[mo].name, damage);
	return damage;
}
