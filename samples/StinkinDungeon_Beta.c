// StinkinDungeon_Beta.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 部屋の情報
typedef struct
{
	int hasStinker1;		// Stinker1がいる
	int hasStinker2;		// Stinker2がいる
	int hasSuperStinker;	// Super Stinkerがいる
	int hasPrince;			// プリンスがいる
	int princeVisited;		// 部屋にプリンスが訪問したか
	int doorInfo[ 4 ];		// ドアの情報
	int stinkerSmell1;		// Stinker1の匂いの情報
	int stinkerSmell2;		// Stinker2の匂いの情報
	int superStinkerSmell;	// Super Stinkerの匂いの情報
	int hasSword;			// 刀がある
	int healthPotion;		// 健康ポーションがある
} Room;

// ダンジョンの部屋は5x5のグリッドなので2時配列
// 紙プロトタイプは(0,0)からではなく，(1,1)からスタートので配列は6対6にする
Room dungeon[ 6 ][ 6 ];

// 主人公の情報
typedef struct
{
	int roomX;			// プリンスがいる部屋のX軸
	int roomY;			// プリンスがいる部屋のY軸
	int hasSword;		// 刀を持っているか
	int keyNumber;		// キーの数
	int healthPoints;	// プリンスのＨＰ
} GameHero;

// 主人公のプリンス
GameHero prince;

// プリンスとStinkerの最大ＨＰ
const int princeStartHP			= 20;
const int stinker1StartHP		= 25;
const int stinker2StartHP		= 25;
const int superStinkerStartHP	= 30;

// 攻撃のダメージを決める値	
const int princeAttackRange			= 8;
const double swordDamageRatio		= 2.6;
const int stinkerAttackRange		= 11;
const int superStinkerAttackRange	= 12;

// プリンスとStinkerの戦闘結果
const int princeWins		= 1;
const int princeLoses		= 2;

// ドアの状況
const int noDoor		= 0;
const int openDoor		= 1;
const int lockedDoor	= 2;

// 方向
const int North		= 0;
const int East		= 1;
const int South		= 2;
const int West		= 3;

// StinkerのＨＰを格納する変数
int stinker1HP;
int stinker2HP;
int superStinkerHP;

// 勝利と敗北のための変数
int rescuedPrincess;	// プリンセスはレスキューできたか
int princeDead;			// プリンスは亡くなったか

// 関数のプロトタイプ
void initialiseDungeon();
void initialisePrince();
void initialiseStinkers();
void initialiseGameEndingConditions();
void printGameExplanation();
void showDungeon();
void showRoomInfo();
int getUserMove();
void movePrince( int );
void tryPickUpSword( void );
void tryDrinkHealthPotion( void );
void checkStinkerFight( void );
int stinkerFight( int, int );
int superStinkerFight( int, int );
int princeAttack( int );
int stinkerAttack( void );
int superStinkerAttack( void );

int main( void )
{
	char c;
	int moveDirection;				// 移動方向

	srand( time( NULL ) );			// Stinker戦闘のため乱数を初期化

	// 初期化
	initialiseDungeon();					// ダンジョンの初期化
	initialisePrince();						// プリンスの情報を初期化
	initialiseStinkers();					// Stinkerの情報を初期化
	initialiseGameEndingConditions();		// ゲームの終了条件を初期化
	printGameExplanation();					// ゲームのルールを表示

	// ゲームループ：勝利条件と敗北条件が満たしていないまで続く
	while( 1 )
	{
		showDungeon();							// ダンジョンの情報を表示
		showRoomInfo();							// 部屋の情報を表示

		checkStinkerFight();					// Stinkerがいるなら戦闘
		if( princeDead )						// Stinkerに負けた（敗北）
		{
			break;
		}
		if( rescuedPrincess )					// Super Stinkerを倒した（勝利）
		{
			break;
		}
		tryPickUpSword();						// 刀があるなら獲得
		tryDrinkHealthPotion();					// 健康ポーションがあるか、使うかのチェック

		moveDirection = getUserMove();			// ユーザーから移動方向を入力してもらう
		movePrince( moveDirection );			// ユーザが選んだ方向にプリンスを移動させる

	}

	// 勝利か敗北のメッセージでゲーム終了する
	printf( "¥n" );
	printf( "*************¥n" );
	printf( "* GAME OVER *¥n" );
	printf( "*************¥n" );
	if( rescuedPrincess )
	{
		printf( "You have defeated the Stinkers and saved your princess.¥n" );
		printf( "Of course, you and your princess live happily ever after.¥n" );
	}
	else
	{
		printf( "You died in battle and the Stinkers dance happily on your grave.¥n" );
		printf( "Of course, they keep the princess in their dungeon forever.¥n" );
	}
	printf( "¥nPress any key to continue.¥n" );
	c = getchar();

	return 0;
}

// この関数でダンジョンを初期化する
// ダンジョン情報は紙プロトタイプでテストプレイしたものと同じ
// 出力の都合によって，(1,1)は画面の右上にする
void initialiseDungeon()
{
	int y;

	// プリンスは最初(1,1)の部屋にいる
	dungeon[ 1 ][ 1 ].hasPrince = 1;
	// プリンスは(1,1)の部屋を訪問している
	dungeon[ 1 ][ 1 ].princeVisited = 1;
	// Stinker1は(2,5)の部屋にいる
	dungeon[ 2 ][ 5 ].hasStinker1 = 1;
	// Stinker1の匂いの情報を隣の部屋に追加
	dungeon[ 1 ][ 5 ].stinkerSmell1 = 1;
	dungeon[ 3 ][ 5 ].stinkerSmell1 = 1;
	dungeon[ 2 ][ 4 ].stinkerSmell1 = 1;
	// Stinker2は(3,2)の部屋にいる
	dungeon[ 3 ][ 2 ].hasStinker2 = 1;
	// Stinker2の匂いの情報を隣の部屋に追加
	dungeon[ 2 ][ 2 ].stinkerSmell2 = 1;
	dungeon[ 4 ][ 2 ].stinkerSmell2 = 1;
	dungeon[ 3 ][ 3 ].stinkerSmell2 = 1;
	dungeon[ 3 ][ 1 ].stinkerSmell2 = 1;
	// Super Stinkerは(4,4)の部屋にいる
	dungeon[ 4 ][ 4 ].hasSuperStinker = 1;
	// Super Stinkerの匂いの情報を隣の部屋に追加
	dungeon[ 3 ][ 4 ].superStinkerSmell = 1;
	dungeon[ 5 ][ 4 ].superStinkerSmell = 1;
	dungeon[ 4 ][ 3 ].superStinkerSmell = 1;
	dungeon[ 4 ][ 5 ].superStinkerSmell = 1;
	// 刀は(1,4)の部屋にある
	dungeon[ 1 ][ 4 ].hasSword = 1;
	// 健康ポーションは(5,3)と(3,5)の部屋にある
	dungeon[ 5 ][ 3 ].healthPotion = 1;
	dungeon[ 3 ][ 5 ].healthPotion = 1;

	// ドアの情報

	// 1列目のドア情報
	dungeon[ 1 ][ 1 ].doorInfo[ East ] = openDoor;
	dungeon[ 1 ][ 1 ].doorInfo[ South ] = openDoor;

	dungeon[ 2 ][ 1 ].doorInfo[ East ] = openDoor;
	dungeon[ 2 ][ 1 ].doorInfo[ South ] = openDoor;
	dungeon[ 2 ][ 1 ].doorInfo[ West ] = openDoor;
	dungeon[ 3 ][ 1 ].doorInfo[ East ] = openDoor;
	dungeon[ 3 ][ 1 ].doorInfo[ South ] = openDoor;
	dungeon[ 3 ][ 1 ].doorInfo[ West ] = openDoor;
	dungeon[ 4 ][ 1 ].doorInfo[ East ] = openDoor;
	dungeon[ 4 ][ 1 ].doorInfo[ South ] = openDoor;
	dungeon[ 4 ][ 1 ].doorInfo[ West ] = openDoor;

	dungeon[ 5 ][ 1 ].doorInfo[ South ] = openDoor;
	dungeon[ 5 ][ 1 ].doorInfo[ West ] = openDoor;

	// 2列目から4列目までの情報は同じのでforループで初期化
	for( y = 2; y < 5; y++ )
	{
		dungeon[ 1 ][ y ].doorInfo[ North ] = openDoor;
		dungeon[ 1 ][ y ].doorInfo[ East ] = openDoor;
		dungeon[ 1 ][ y ].doorInfo[ South ] = openDoor;

		dungeon[ 2 ][ y ].doorInfo[ North ] = openDoor;
		dungeon[ 2 ][ y ].doorInfo[ East ] = openDoor;
		dungeon[ 2 ][ y ].doorInfo[ South ] = openDoor;
		dungeon[ 2 ][ y ].doorInfo[ West ] = openDoor;
		dungeon[ 3 ][ y ].doorInfo[ North ] = openDoor;
		dungeon[ 3 ][ y ].doorInfo[ East ] = openDoor;
		dungeon[ 3 ][ y ].doorInfo[ South ] = openDoor;
		dungeon[ 3 ][ y ].doorInfo[ West ] = openDoor;
		dungeon[ 4 ][ y ].doorInfo[ North ] = openDoor;
		dungeon[ 4 ][ y ].doorInfo[ East ] = openDoor;
		dungeon[ 4 ][ y ].doorInfo[ South ] = openDoor;
		dungeon[ 4 ][ y ].doorInfo[ West ] = openDoor;

		dungeon[ 5 ][ y ].doorInfo[ North ] = openDoor;
		dungeon[ 5 ][ y ].doorInfo[ South ] = openDoor;
		dungeon[ 5 ][ y ].doorInfo[ West ] = openDoor;
	}

	// 5列目のドア情報
	dungeon[ 1 ][ 5 ].doorInfo[ North ] = openDoor;
	dungeon[ 1 ][ 5 ].doorInfo[ East ] = openDoor;

	dungeon[ 2 ][ 5 ].doorInfo[ North ] = openDoor;
	dungeon[ 2 ][ 5 ].doorInfo[ East ] = openDoor;
	dungeon[ 2 ][ 5 ].doorInfo[ West ] = openDoor;
	dungeon[ 3 ][ 5 ].doorInfo[ North ] = openDoor;
	dungeon[ 3 ][ 5 ].doorInfo[ East ] = openDoor;
	dungeon[ 3 ][ 5 ].doorInfo[ West ] = openDoor;
	dungeon[ 4 ][ 5 ].doorInfo[ North ] = openDoor;
	dungeon[ 4 ][ 5 ].doorInfo[ East ] = openDoor;
	dungeon[ 4 ][ 5 ].doorInfo[ West ] = openDoor;

	dungeon[ 5 ][ 5 ].doorInfo[ North ] = openDoor;
	dungeon[ 5 ][ 5 ].doorInfo[ West ] = openDoor;

	// ドアがないところの情報を修正
	dungeon[ 4 ][ 4 ].doorInfo[ North ] = noDoor;
	dungeon[ 4 ][ 4 ].doorInfo[ South ] = noDoor;
	dungeon[ 4 ][ 4 ].doorInfo[ West ] = noDoor;
	dungeon[ 4 ][ 3 ].doorInfo[ South ] = noDoor;
	dungeon[ 4 ][ 5 ].doorInfo[ North ] = noDoor;
	dungeon[ 3 ][ 4 ].doorInfo[ East ] = noDoor;
	// ロックされているドアの情報を修正
	dungeon[ 4 ][ 4 ].doorInfo[ East ] = lockedDoor;
	dungeon[ 5 ][ 4 ].doorInfo[ West ] = lockedDoor;
}

// プリンスの情報を初期化
void initialisePrince()
{
	// プリンスが最初にいる部屋は(1,1)
	prince.roomX = 1;
	prince.roomY = 1;
	// プリンスは最初刀を持っていない
	prince.hasSword = 0;
	// プリンスはキーを持っていない
	prince.keyNumber = 0;
	// 最初は最大のＨＰに設定
	prince.healthPoints = princeStartHP;
}

// Stinkerの情報を初期化
void initialiseStinkers()
{
	stinker1HP = stinker1StartHP;			// Stinker1のＨＰ
	stinker2HP = stinker2StartHP;			// Stinker2のＨＰ
	superStinkerHP = superStinkerStartHP;	// Super StinkerのＨＰ
}

// ゲームの終了条件を初期化
void initialiseGameEndingConditions()
{
	rescuedPrincess = 0;					// プリンセスはまだレスキュー出来ていない
	princeDead = 0;							// プリンスはまだいきている
}

// ゲームのルールと目的を説明する
void printGameExplanation()
{
	char c, userSelection;

	printf( "****************************************¥n" );
	printf( "*                                      *¥n" );
	printf( "*      Welcome to Stinkin' Dungeon     *¥n" );
	printf( "*                                      *¥n" );
	printf( "*       A simple text-based RPG        *¥n" );
	printf( "*                                      *¥n" );
	printf( "*      Design: Reijer Grimbergen       *¥n" );
	printf( "*                                      *¥n" );
	printf( "****************************************¥n" );

	printf( "¥n" );
	printf( "1) Show the rules of the game¥n" );
	printf( "2) Start the game¥n" );
	printf( "Please enter your selection: " );

	// ユーザの選択を獲得
	c = getchar();
	userSelection = c;
	while( ( c = getchar() ) != '¥n' )
		;
	if( userSelection == '1' )
	{
		printf( "¥nRules of Stinkin' Dungeon:¥n");
		printf( "==========================¥n" );
		printf( "1) You are a prince and in room (1,1) of the Dungeon of the Stinkers¥n" );
		printf( "2) Somewhere in this dungeon there is a princess that you must rescue from the Stinkers¥n" );
		printf( "3) There are two Stinkers and one Super Stinker in this dungeon¥n" );
		printf( "4) When you enter a room with a Stinker, you must fight him¥n" );
		printf( "5) When fighting a Stinker, your health points will go down¥n" );
		printf( "6) To improve your chances of beating a Stinker, you need a sword that is somewhere in the dungeon¥n" );
		printf( "7) If you survive a Stinker fight, you can restore your health by drinking an health potion that is somewhere in the dungeon¥n" );
		printf( "8) You cannot carry a health potion with you. If you want to use it you must go back to the room you found it¥n" );
		printf( "9) The princess is in the room with the Super Stinker¥n" );
		printf( "10) To enter the room with the Super Stinker you need two keys¥n" );
		printf( "11) Each Stinker holds one of the keys. If you defeat a Stinker, you will get the key he carries.¥n" );
		printf( "12) Each room has a number of doors through which you can go to get to the other rooms¥n" );
		printf( "13) Only by visiting a room, you will get access to the information about this room¥n" );
		printf( "14) The Stinkers smell so bad that you can smell them in the neighboring room¥n" );
		printf( "¥nPress any key to start the game.¥n" );
		c = getchar();
	}
	printf( "Good luck with your quest to save the princess!¥n" );

}

// ダンジョンの情報を画面に表示する
// 一つの部屋は5x5の大きさにする
// 1列目：北ドア、2列目：見やすくするための空きスペース、3列目：匂い、
// 4列目：西ドア、プリンスとStinker、東ドア、5列目：刀と健康ポーション、6列目：南ドア
void showDungeon()
{
	int x, y;

	// 部屋を一つずつ表示する
	for( y = 1; y <= 5; y++ )
	{

		// 1列目：北ドア
		for( x = 1; x <= 5; x++ )
		{
			if( dungeon[ x ][ y ].princeVisited )
			{
				if( dungeon[ x ][ y ].doorInfo[ North ] == noDoor )
				{
					printf( "*******" );
				}
				else if( dungeon[ x ][ y ].doorInfo[ North ] == openDoor )
				{
					printf( "***D***" );
				}
				else if( dungeon[ x ][ y ].doorInfo[ North ] == lockedDoor )
				{
					printf( "***L***" );
				}
			}
			else
			{
				printf( "       " );
			}
		}
		printf( "¥n" );

		// 2列目：見やすくするための空きスペース
		for( x = 1; x <= 5; x++ )
		{
			if( dungeon[ x ][ y ].princeVisited )
			{
				printf( "*     *" );
			}
			else
			{
				printf( "       " );
			}
		}
		printf( "¥n" );

		// 3列目：匂い
		for( x = 1; x <= 5; x++ )
		{
			if( dungeon[ x ][ y ].princeVisited )
			{
				if( dungeon[ x ][ y ].stinkerSmell1 || dungeon[ x ][ y ].stinkerSmell2 )
				{
					printf( "*  &  *" );
				}
				else if( dungeon[ x ][ y ].superStinkerSmell )
				{
					printf( "*  #  *" );
				}
				else
				{
					printf( "*     *" );
				}
			}
			else
			{
				printf( "       " );
			}
		}
		printf( "¥n" );

		// 4列目：西ドア、プリンスとStinker、東ドア
		for( x = 1; x <= 5; x++ )
		{
			if( dungeon[ x ][ y ].princeVisited )
			{
				if( dungeon[ x ][ y ].doorInfo[ West ] == noDoor )
				{
					printf( "* " );
				}
				else if( dungeon[ x ][ y ].doorInfo[ West ] == openDoor )
				{
					printf( "D " );
				}
				else if( dungeon[ x ][ y ].doorInfo[ West ] == lockedDoor )
				{
					printf( "L " );
				}
				if( dungeon[ x ][ y ].hasPrince )
				{
					if( prince.hasSword )
					{
						printf( "P!" );
					}
					else
					{
						printf( "P " );
					}
				}
				else
				{
					printf( "  " );
				}
				if( dungeon[ x ][ y ].hasStinker1 || dungeon[ x ][ y ].hasStinker2 )
				{
					printf( "S " );
				}
				else if( dungeon[ x ][ y ].hasSuperStinker )
				{
					printf( "$ " );
				}
				else
				{
					printf( "  " );
				}
				if( dungeon[ x ][ y ].doorInfo[ East ] == noDoor )
				{
					printf( "*" );
				}
				else if( dungeon[ x ][ y ].doorInfo[ East ] == openDoor )
				{
					printf( "D" );
				}
				else if( dungeon[ x ][ y ].doorInfo[ East ] == lockedDoor )
				{
					printf( "L" );
				}
			}
			else {
				printf( "       " );
			}
		}
		printf( "¥n" );

		// 5列目：刀と健康ポーション
		for( x = 1; x <= 5; x++ )
		{
			if( dungeon[ x ][ y ].princeVisited )
			{
				if( dungeon[ x ][ y ].hasSword )
				{
					printf( "* K " );
				}
				else
				{
					printf( "*   " );
				}
				if( dungeon[ x ][ y ].healthPotion )
				{
					printf( "H *" );
				}
				else
				{
					printf( "  *" );
				}
			}
			else
			{
				printf( "       " );
			}
		}
		printf( "¥n" );

		// 6列目：南ドア
		for( x = 1; x <= 5; x++ )
		{
			if( dungeon[ x ][ y ].princeVisited )
			{
				if( dungeon[ x ][ y ].doorInfo[ South ] == noDoor )
				{
					printf( "*******" );
				}
				else if( dungeon[ x ][ y ].doorInfo[ South ] == openDoor )
				{
					printf( "***D***" );
				}
				else if( dungeon[ x ][ y ].doorInfo[ South ] == lockedDoor )
				{
					printf( "***L***" );
				}
			}
			else
			{
				printf( "       " );
			}
		}
		printf( "¥n" );

	}

	// 記号の説明
	printf( "P = Prince, S = Stinker, $ = Super Stinker¥n" );
	printf( "& = Stinker smell, # = Super Stinker smell¥n" );
	printf( "K = Sword, P! = Prince has sword, H = Health potion¥n" );
	printf( "D = Open Door, L = Locked door, * = Wall ¥n" );

	// プリンスの健康状況を表示
	printf( "¥nPrince HP: %d¥n", prince.healthPoints );
	// プリンスのキー情報を表示
	printf( "Current number of keys: %d¥n¥n", prince.keyNumber );
}

// 部屋の情報を表示する
void showRoomInfo()
{
	int x = prince.roomX;
	int y = prince.roomY;

	// この部屋にStinkerかSuper Stinkerがいることを表示
	if( dungeon[ x ][ y ].hasStinker1 || dungeon[ x ][ y ].hasStinker2 )
	{
		printf( "There is a Stinker in this room¥n" );
	}
	if( dungeon[ x ][ y ].hasSuperStinker )
	{
		printf( "There is a Super Stinker in this room¥n" );
	}
	// この部屋に刀があることを表示
	if( dungeon[ x ][ y ].hasSword )
	{
		printf( "There is a sword in this room¥n" );
	}
	// この部屋に健康ポーションがあることを表示
	if( dungeon[ x ][ y ].healthPotion )
	{
		printf( "There is a health potion in this room¥n" );
	}
	// この部屋の匂いを表示
	if( dungeon[ x ][ y ].stinkerSmell1 || dungeon[ x ][ y ].stinkerSmell2 )
	{
		printf( "There is a bad smell in this room¥n" );
	}
	if( dungeon[ x ][ y ].superStinkerSmell )
	{
		printf( "There is a very foul stench in this room¥n" );
	}
	if( !dungeon[ x ][ y ].stinkerSmell1 && !dungeon[ x ][ y ].stinkerSmell2 &&
		!dungeon[ x ][ y ].superStinkerSmell )
	{
		printf( "There is no smell in this room¥n" );
	}
	// この部屋のドア情報を表示
	if( dungeon[ x ][ y ].doorInfo[ North ] == openDoor )
	{
		printf( "There is a door to the North¥n" );
	}
	else if( dungeon[ x ][ y ].doorInfo[ North ] == lockedDoor )
	{
		printf( "There is a locked door to the North¥n" );
	}
	if( dungeon[ x ][ y ].doorInfo[ East ] == openDoor )
	{
		printf( "There is a door to the East¥n" );
	}
	else if( dungeon[ x ][ y ].doorInfo[ East ] == lockedDoor )
	{
		printf( "There is a locked door to the East¥n" );
	}
	if( dungeon[ x ][ y ].doorInfo[ South ] == openDoor )
	{
		printf( "There is a door to the South¥n" );
	}
	else if( dungeon[ x ][ y ].doorInfo[ South ] == lockedDoor )
	{
		printf( "There is a locked door to the South¥n" );
	}
	if( dungeon[ x ][ y ].doorInfo[ West ] == openDoor )
	{
		printf( "There is a door to the West¥n" );
	}
	else if( dungeon[ x ][ y ].doorInfo[ West ] == lockedDoor )
	{
		printf( "There is a locked door to the West¥n" );
	}
}

// ユーザーから移動方向を入力してもらう
int getUserMove()
{
	int direction = -1;
	int legalDirection = 0;
	char c;
	int x = prince.roomX;
	int y = prince.roomY;

	// 正しい方向が入力されてないまで繰り返す
	while( !legalDirection ) 
	{
		// ユーザーから方向を入力
		printf( "Enter door direction (N,E,S,W): " );
		c = getchar();
		// 改行文字をバッファーから削除
		scanf("%*c");

		// 入力は正しいかどうかを確認
		switch( c )
		{
		case 'N':
			// 北方向にドアがあれば方向決定
			if( dungeon[ x ][ y ].doorInfo[ North ] == openDoor )
			{
				direction = North;
				legalDirection = 1;
			}
			else if( dungeon[ x ][ y ].doorInfo[ North ] == lockedDoor )
			{
				if( prince.keyNumber == 2 )
				{
					direction = North;
					legalDirection = 1;
				}
				else
				{
					printf( "This door is locked. You need two keys to enter¥n" );
				}
			}
			else
			{
				printf( "You cannot move in this direction¥n" );
			}
			break;
		case 'E':
			// 東方向にドアがあれば方向決定
			if( dungeon[ x ][ y ].doorInfo[ East ] == openDoor )
			{
				direction = East;
				legalDirection = 1;
			}
			else if( dungeon[ x ][ y ].doorInfo[ East ] == lockedDoor )
			{
				if( prince.keyNumber == 2 )
				{
					direction = East;
					legalDirection = 1;
				}
				else
				{
					printf( "This door is locked. You need two keys to enter¥n" );
				}
			}
			else
			{
				printf( "You cannot move in this direction¥n" );
			}
			break;
		case 'S':
			// 南方向にドアがあれば方向決定
			if( dungeon[ x ][ y ].doorInfo[ South ] == openDoor )
			{
				direction = South;
				legalDirection = 1;
			}
			else if( dungeon[ x ][ y ].doorInfo[ South ] == lockedDoor )
			{
				if( prince.keyNumber == 2 )
				{
					direction = South;
					legalDirection = 1;
				}
				else
				{
					printf( "This door is locked. You need two keys to enter¥n" );
				}
			}
			else
			{
				printf( "You cannot move in this direction¥n" );
			}
			break;
		case 'W':
			// 西方向にドアがあれば方向決定
			if( dungeon[ x ][ y ].doorInfo[ West ] == openDoor )
			{
				direction = West;
				legalDirection = 1;
			}
			else if( dungeon[ x ][ y ].doorInfo[ West ] == lockedDoor )
			{
				if( prince.keyNumber == 2 )
				{
					direction = West;
					legalDirection = 1;
				}
				else
				{
					printf( "This door is locked. You need two keys to enter¥n" );
				}
			}
			else
			{
				printf( "You cannot move in this direction¥n" );
			}
			break;
		default:
			// 不正入力
			printf( "Illegal door direction¥n" );
			break;
		}
	}

	return direction;
}

// ユーザが選んだ方向にプリンスを移動させる
void movePrince( int direction )
{
	int currentX = prince.roomX;
	int currentY = prince.roomY;
	int newX, newY;

	//　プリンスを元の部屋から消す
	dungeon[ currentX ][ currentY ].hasPrince = 0;

	//　新しい部屋のX軸とY軸を方向から獲得
	if( direction == North )
	{
		newX = currentX;
		newY = currentY - 1;
	}
	else if( direction == East )
	{
		newX = currentX + 1;
		newY = currentY;
	}
	else if( direction == South )
	{
		newX = currentX;
		newY = currentY + 1;
	}
	else if( direction == West )
	{
		newX = currentX - 1;
		newY = currentY;
	}

	// 新しい場所の情報を追加
	prince.roomX = newX;
	prince.roomY = newY;
	dungeon[ newX ][ newY ].hasPrince = 1;
	dungeon[ newX ][ newY ].princeVisited = 1;

}

// 刀があるなら獲得
void tryPickUpSword( void )
{
	int x = prince.roomX;
	int y = prince.roomY;

	// 部屋に刀があれば，刀を獲得
	if( dungeon[ x ][ y ].hasSword )
	{
		prince.hasSword = 1;
		dungeon[ x ][ y ].hasSword = 0;
		printf( "===========================¥n" );
		printf( "You have picked up a sword!¥n" );
		printf( "===========================¥n" );
	}
}

// 健康ポーションがあるか、使うかのチェック
void tryDrinkHealthPotion( void )
{
	int x = prince.roomX;
	int y = prince.roomY;

	// 部屋に健康ポーションがあるとプリンスのＨＰが満点より低ければＨＰを満点にする
	if( dungeon[ x ][ y ].healthPotion && prince.healthPoints < princeStartHP )
	{
		prince.healthPoints = princeStartHP;
		dungeon[ x ][ y ].healthPotion = 0;		// 健康ポーションは一回しか使えない
		printf( "=========================================¥n" );
		printf( "You drink a health potion and feel great!¥n" );
		printf( "=========================================¥n" );
	}

}

// Stinkerがいるなら戦闘
void checkStinkerFight( void )
{
	int x = prince.roomX;
	int y = prince.roomY;
	int result;
	char c;

	if( dungeon[ x ][ y ].hasStinker1 )
	{
		// この部屋にStinkerがいるのでStinkerと戦う
		if( prince.hasSword )
		{
			// 刀ありの戦い
			printf( "¥n¥"I see you have a sword, but I am going to kill you anyway!!¥"¥n¥n" );
			printf( "Press any key to attack Stinker...¥n" );
			c = getchar();
			result = stinkerFight( stinker1HP, 1 );
		}
		else
		{
			// 刀なしの戦い
			printf( "¥n¥"You come to fight me with your bare hands? Prepare to die!!¥"¥n¥n" );
			printf( "Press any key to attack Stinker...¥n" );
			c = getchar();
			result = stinkerFight( stinker2HP, 0 );
		}
		if( result == princeWins )
		{
			// Stinkerを倒したのでキーを獲得
			printf( "¥nAfter a brave fight you have killed a Stinker. You get the key he holds!¥n¥n" );
			prince.keyNumber++;
			// Stinkerを削除
			dungeon[ x ][ y ].hasStinker1 = 0;
			// 匂いを削除
			if( x > 1 ) dungeon[ x - 1 ][ y ].stinkerSmell1 = 0;
			if( x < 4 ) dungeon[ x + 1 ][ y ].stinkerSmell1 = 0;
			if( y > 1 ) dungeon[ x ][ y - 1 ].stinkerSmell1 = 0;
			if( y < 4 ) dungeon[ x ][ y + 1 ].stinkerSmell1 = 0;
		}
		else {
			// Stinkerに負けたの敗北条件達成
			princeDead = 1;
		}
	}
	else if( dungeon[ x ][ y ].hasStinker2 )
	{
		// この部屋にStinkerがいるのでStinkerと戦う
		if( prince.hasSword )
		{
			// 刀ありの戦い
			printf( "¥n¥"I see you have a sword, but I am going to kill you anyway!!¥"¥n¥n" );
			printf( "Press any key to attack Stinker...¥n" );
			c = getchar();
			result = stinkerFight( stinker2HP, 1 );
		}
		else
		{
			// 刀なしの戦い
			printf( "¥n¥"You come to fight me with your bare hands? Prepare to die!!¥"¥n¥n" );
			printf( "Press any key to attack Stinker...¥n" );
			c = getchar();
			result = stinkerFight( stinker2HP, 0 );
		}
		if( result == princeWins )
		{
			// Stinkerを倒したのでキーを獲得
			printf( "¥nAfter a brave fight you have killed a Stinker. You get the key he holds!¥n¥n" );
			prince.keyNumber++;
			// Stinkerを削除
			dungeon[ x ][ y ].hasStinker2 = 0;
			// 匂いを削除
			if( x > 1 ) dungeon[ x - 1 ][ y ].stinkerSmell2 = 0;
			if( x < 4 ) dungeon[ x + 1 ][ y ].stinkerSmell2 = 0;
			if( y > 1 ) dungeon[ x ][ y - 1 ].stinkerSmell2 = 0;
			if( y < 4 ) dungeon[ x ][ y + 1 ].stinkerSmell2 = 0;
		}
		else {
			// Stinkerに負けたの敗北条件達成
			princeDead = 1;
		}
	}
	else if( dungeon[ x ][ y ].hasSuperStinker )
	{
		// この部屋にSuper StinkerがいるのでSuper Stinkerと戦う
		if( prince.hasSword )
		{
			// 刀ありの戦い
			printf( "¥n¥"I see you have a sword, but you never will get the Princess!!¥"¥n¥n" );
			printf( "Press any key to attack Super Stinker...¥n" );
			c = getchar();
			result = superStinkerFight( superStinkerHP, 1 );
		}
		else
		{
			// 刀なしの戦い
			printf( "¥n¥"No Weapons? HA HA HA HA HA!!¥n¥n¥"" );
			printf( "Press any key to attack Super Stinker...¥n" );
			c = getchar();
			result = superStinkerFight( superStinkerHP, 0 );
		}
		if( result == princeWins )
		{
			// Super Stinkerを倒したのでプリンセスを助けた
			rescuedPrincess = 1;
			printf( "¥n¥"You brave prince. Thank you for rescuing me from these awful Stinkers.¥"¥n¥n" );
			// Stinkerを削除
			dungeon[ x ][ y ].hasSuperStinker = 0;
			// 匂いを削除
			if( x > 1 ) dungeon[ x - 1 ][ y ].superStinkerSmell = 0;
			if( x < 4 ) dungeon[ x + 1 ][ y ].superStinkerSmell = 0;
			if( y > 1 ) dungeon[ x ][ y - 1 ].superStinkerSmell = 0;
			if( y < 4 ) dungeon[ x ][ y + 1 ].superStinkerSmell = 0;
		}
		else {
			// Super Stinkerに負けたの敗北条件達成
			princeDead = 1;
		}
	}
}

// １回のプリンスとStinkerの戦闘シミュレーション
int stinkerFight( int stinkerHP, int hasSword )
{
	char c;

	while( 1 )
	{
		// プリンスは攻撃する
		stinkerHP -= princeAttack( hasSword );
		printf( "Stinker HP: %d¥n", stinkerHP );
		// Stinkerを倒したかどうかのチェック
		if( stinkerHP <= 0 )
		{
			return princeWins;
		}
		// Stinkerは反撃する
		prince.healthPoints -= stinkerAttack();
		printf( "Prince HP: %d¥n", prince.healthPoints );
		// プリンスが死んだかどうかのチェック
		if( prince.healthPoints <= 0 )
		{
			return princeLoses;
		}

		// 攻撃と反撃の後に状況をチェック出来るように入力して貰う
		// 戦闘の流れが把握できると面白くなるか
		printf( "Press any key to continue..." );
		c = getchar();
		
	}
	return 0;
}

// １回のプリンスとStinkerの戦闘シミュレーション
int superStinkerFight( int stinkerHP, int hasSword )
{
	char c;

	while( 1 )
	{
		// プリンスは攻撃する
		stinkerHP -= princeAttack( hasSword );
		printf( "Super Stinker HP: %d¥n", stinkerHP );
		// Stinkerを倒したかどうかのチェック
		if( stinkerHP <= 0 )
		{
			return princeWins;
		}
		// Stinkerは反撃する
		prince.healthPoints -= superStinkerAttack();
		printf( "Prince HP: %d¥n", prince.healthPoints );
		// プリンスが死んだかどうかのチェック
		if( prince.healthPoints <= 0 )
		{
			return princeLoses;
		}

		// 攻撃と反撃の後に状況をチェック出来るように入力して貰う
		// 戦闘の流れが把握できると面白くなるか
		printf( "Press any key to continue..." );
		c = getchar();
		
	}
	return 0;
}

// プリンスの攻撃
int princeAttack( int hasSword )
{
	// 攻撃のダメージは乱数で決める
	int damage = rand() % princeAttackRange;
	// 刀があると攻撃力アップ
	if( hasSword )
	{
		damage *= swordDamageRatio;
	}
	printf( "Prince attacks, damage: %d¥n", damage );
	return damage;
}

// Stinkerの攻撃
int stinkerAttack( void )
{
	// 攻撃のダメージは乱数で決める
	int damage = rand() % stinkerAttackRange;
	printf( "Stinker attacks, damage: %d¥n", damage );
	return damage;
}

// Super Stinkerの攻撃
int superStinkerAttack( void )
{
	// 攻撃のダメージは乱数で決める
	int damage = rand() % superStinkerAttackRange;
	printf( "Super Stinker attacks, damage: %d¥n", damage );
	return damage;
}