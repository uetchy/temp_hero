#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PERSON_NUM 100
#include "battle.h"

// Max player hp
#define MAX_PLAYER_HP 15

//モンスター雑魚定義
struct Monster {  // _person がタグ名
  char name[20];    // 文字配列型のメンバ name
  int hp;					  // HP
	int power;				//パワー
	char point1[256]; //wpは攻撃部位
	char point2[256];
	char point3[256];
	char point4[256];
  int wp;         	//wpは弱点部位を示す　
	//弱点部位は攻撃部位を選択するときにいれる数字とれらし合わせて判断する
};
//モンスター雑魚ステータス

// monster[] = { name, HP, atk, part1, part2, part3, part4, weakpart };
Monster monsters[PERSON_NUM] = {
	{"Andy",3 , 2, "EEEE", "??E", "1", "1", 1},
	{"Ue-sama", 4 , 2, "Eye", "Throat", "Armpit", "Feet", 2},
	{"Yazaki", 3 , 3, "Right Hand", "Right Feet", "1", "1", 2},
	{"Iida", 8 , 1, "Laptop", "Mobile Phone", "Hoodies", "1", 3},
	{"Yoshioka", 6 , 2, "Hair", "Throat", "Pelvis", "Nose", 4},
	{"Muramatsu", 2 , 8, "Hair", "Keyboard", "Mobile Phone", "Mouse", 2},
	{"とらえモン", 5 , 1, "Pocket", "Dorayaki", "Tail", "Rat", 2},
	{"ビカチュウ", 2 , 4, "Ear", "Eye", "Tail", "Cheek", 4},
	{"ぷにょよ", 3 , 2, "邪魔ぷよ", "１れんさ", "５れんさ", "１０れんさ", 4},
	{"matsuko", 10 , 1, "Eye", "Throat", "Jaw", "Hair", 3},
	{"ボス", 25 , 3, "頭", "腕", "おなか", "えんだ―", 4},
	{"裏ボス", 20 , 3, "頭", "顎", "脇腹", "足", 1}
};

// 調整する値はここまで
//==========================================

// PlayerとZakoの戦闘結果
const int princeWins  = 1;
const int princeLoses = 2;

int weakpoint;

// Prototype
// void test_fight();
// void test_fightLoop( int,  int, int, int );

int playerAttack( int , int );
int enemyAttack( int );

// int main( void ) {
// 	char c;
// 	initializePlayer(&player);
// 	player->hp = 15;
// 	srand( time(NULL) ); // Zako戦闘のため乱数を初期化

// 	printf( "- T e m p o r a r y  H e r o -\n" );
//   printf(" ___ ___         __                _____.___.                  .__\n");
//   printf(" /   |   \\_____  |  | __ ____   ____\\__  |   |__ __ __ __  _____|  |__ __\n");
//   printf("/    ~    \\__  \\ |  |/ // __ \\ /    \\/   |   |  |  \\  |  \\/  ___/  |  \\__\\\n");
//   printf("\\    Y    // __ \\|    <\\  ___/|   |  \\____   |  |  /  |  /\\___ \\|   Y  \\/ __ \\_\n");
//   printf(" \\___|_  /(____  /__|_ \\___  >___|  / ______|____/|____//____  >___|  (____  /\n");
//   printf( "Alpha version\n" );
// 	test_fight(); // Zakoがいるなら戦闘

// 	printf( "\nPress any key to continue.\n" );
// 	c = getchar();

// 	return 0;
// }

// // Testing function
// void test_fight() {
// 	char c, userSelection;
// 	int endTestSession = 0;

// 	while( !endTestSession ) {

// 		printf( "1) Fight Zako without sword\n" );
// 		printf( "2) Fight Zako with sword\n" );
// 		printf( "3) Fight Super Zako without sword\n" );
// 		printf( "4) Fight Super Zako with sword\n" );
// 		printf( "Q) Stop test session\n" );
// 		printf( "Please enter your selection: " );

// 		// ユーザの選択を獲得
// 		c = getchar();
// 		userSelection = c;
// 		while( ( c = getchar() ) != '\n' );

// 		switch( userSelection ) {
// 		case '1':
// 			// 刀なしのZako戦闘
// 			test_fightLoop( MAX_PLAYER_HP, 0, 0 ,0);
// 			break;
// 		case '2':
// 			// 刀ありのZako戦闘
// 			test_fightLoop( MAX_PLAYER_HP, 0, 1 ,0);
// 			break;
// 		case '3':
// 			// 刀なしのSuper Zako戦闘
// 			test_fightLoop( MAX_PLAYER_HP, 0, 1 ,1 );
// 			break;
// 		case '4':
// 			// 刀なしのSuper Zako戦闘
// 			test_fightLoop( MAX_PLAYER_HP, 1, 0 ,1);
// 			break;
// 		case '5':
// 			// 刀ありのSuper Zako戦闘
// 			test_fightLoop( MAX_PLAYER_HP, 2, 1 ,1);
// 			break;
// 		case 'Q':
// 			endTestSession = 1;
// 			break;
// 		default:
// 			printf( "Illegal input\n" );
// 			break;
// 		}
// 	}

// }

// // 複数のZako戦闘をシミュレーションして、総合結果を表示する
// // 戦闘終了のPlayerに残っているＨＰの平均も計算する
// void test_fightLoop( int princeHP, int enemyHP, int beatenHBoss ,int weakpoint) {
// 	int result, i;
// 	int fightNumber   = 2;
// 	int princeWinNo   = 0;
// 	int startHP       = princeHP;
// 	int totalPrinceHP = 0;


// 	for( i = 1; i <= fightNumber; i++ )
// 	{
// 		result = battle( &princeHP, enemyHP, beatenHBoss ,weakpoint);
// 		if ( result == princeWins )
// 		{
// 			princeWinNo++;
// 			totalPrinceHP += princeHP; // 残りＨＰの平均計算のためＨＰ合計を更新
// 		}
// 		princeHP = startHP; // 次の戦闘のためにPlayerのＨＰを初期値に戻す
// 	}

// 	// Playerの勝利数を表示yer
// 	printf( "Prince number of wins: %d ( %f%% )\n", princeWinNo, ( princeWinNo / (double) fightNumber ) * 100.0 );
// 	// Playerの残りＨＰの平均を表示
// 	printf( "Average remaining prince HP: %f\n\n", ( totalPrinceHP / (double) fightNumber ) );

// }

// １回のPlayerとZakoの戦闘シミュレーション
// 戦闘の終了のＨＰを呼び出された関数に伝えるためにポインタplayer->hpを使用
int battle(struct Player* player, int monster_index) {

	// 雑魚かボスかを決定
	int mo;

	switch ( monster_index ) {
		case 0: // Zako
		  mo = rand() % 10;
		  break;
		case 1: // Boss
		  mo = 10;
		  break;
		case 2: // Hidden boss
		  mo = 11;
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
			printf("雑魚HP %d \n",enemyHP);
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
int playerAttack( int beatenHBoss ,int weakpoint ) {
	// 攻撃のダメージ
	int damage = 1;

	// 刀があると攻撃力アップ
	if ( beatenHBoss ) {
		damage = damage * 2;
	}
	if ( weakpoint ) {
		damage = damage * 2;
	}

	printf("へーローの攻撃  %dダメージ \n",damage);

	return damage;
}

// Enemy attack func
int enemyAttack( int mo ) {
	int damage = monsters[mo].power;
	printf("%s の攻撃  %dダメージ \n",monsters[mo].name ,damage);
	return damage;
}
