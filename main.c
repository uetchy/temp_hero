#include <stdio.h>

/*
[00][01][02][03]
[10][11][12][13]
[20][21][22][23]
[30][31][32][33]

monsters = [
    [
        "Iida monster", // Monster name
        10000, // HP
        10000, // Attack power
        "---", // Ascii art
        [ // Parts
            ["Head", true],
            ["Stomach", false],
            ["Tail", false]
        ]
    ],
    [
        "Iida monster", // Monster name
        10000, // HP
        10000, // Attack power
        "---", // Ascii art
        [ // Weakpoint
            ["Head", true],
            ["Stomach", false],
            ["Tail", false]
        ]
    ]
]

*/

#define M_NAME 0
#define M_HP 1
#define M_POWER 2
#define M_AA 3
#define M_PARTS 4

typedef struct
{
    int uniqueBossId,  // 固有敵のインデックス（nullならいない）
    int hasPotion,     // ポーションが落ちているか
    int hasKey,        // 鍵が落ちているか？
    String hint,       // ヒント内容（nullならヒント無し）
    int doorLocked,    // ドアに鍵がかかっているか？
    int canJump,       // ジャンプ出来るか
} Room;

typedef struct
{
    int hasKey,           // 鍵を持っているか？
    int hasPotion,        // ポーションを持っているか？
    int beatenHiddenBoss, // 裏ボスを倒したか？
    int x,                // 現在地X
    int y                 // 現在地Y
} Player

Room areaList = [
    Room area1[8][8],
    Room area2[8][8]
]

// 道の状況
const int noPath		= 0;
const int openPath		= 1;
const int lockedDoor	= 2;

// 方向
const int Up		= 0;
const int Right		= 1;
const int Down		= 2;
const int Left		= 3;

// 関数のプロトタイプ
void initialiseareaList();
void initialisePlayer();
void initialiseGameEndingConditions();
void printGameExplanation();
void showarealist();
void showRoomInfo();
int getUserMove();
void movePlayer( int );
void checkEncountGauge( void );
void tryReadHint( void );
void tryDrinkPotion( void );
void tryTakeKey( void );

int main( void )
{
	char c;
	int moveDirection;				// 移動方向

	// 初期化
	initialisearealist();					// ダンジョンの初期化
	initialisePlayer();						// プリンスの情報を初期化
	initialiseGameEndingConditions();		// ゲームの終了条件を初期化
	printGameExplanation();					// ゲームのルールを表示

	// ゲームループ：勝利条件と敗北条件が満たしていないまで続く
	while( 1 )
	{
		showareaList();							// ダンジョンの情報を表示
		showRoomInfo();							// 部屋の情報を表示

		checkEncountGauge();					// Stinkerがいるなら戦闘
		if( PlayerDead )						// Stinkerに負けた（敗北）
		{
			break;
		}
		if( BossDead )					// Super Stinkerを倒した（勝利）
		{
			break;
		}
		tryDrinkPotion();						// ポーションがあるか、使うかのチェック
		tryReadHint();							// ヒントあるかどうか
		tryTakeKey								// 鍵があるかどうか
		moveDirection = getUserMove();			// ユーザーから移動方向を入力してもらう
		movePlayer( moveDirection );			// ユーザが選んだ方向にプリンスを移動させる

	}

	// 勝利か敗北のメッセージでゲーム終了する
	printf( "*************\n" );
	printf( "* GAME OVER *\n" );
	printf( "*************\n\n" );
	if( rescuedPrincess )
	{
		printf( "Boss: You might have defeated me, but it's not the end.\n" );
		printf( "You have defeated this dungeon boss and you managed to escape from this dungeon.\n" );
		printf( "But the Hero's tale is just begin.\n" );
	}
	else
	{
		printf( "You died in battle and your body is eaten by the monsters.\n" );
		printf( "Of course, the world is destroyed.\n" );
	}
	printf( "\nPress any key to continue.\n" );
	c = getchar();

	return 0;
}

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

	// エリア１ドアの情報
	//Right 右、　Doun　下、　Left　左、　Up　上、
	// 1列目のドア情報
	area1[ 7 ][ 1 ].doorInfo[ Up ] = openPath;
	area1[ 7 ][ 1 ].doorInfo[ Left ] = noPath;
	area1[ 7 ][ 1 ].doorInfo[ Right ] = noPath;
	area1[ 7 ][ 1 ].doorInfo[ Down ] = noPath;
	// 2列目のドア情報
	area1[ 3 ][ 2 ].doorInfo[ Up ] = noPath;
	area1[ 3 ][ 2 ].doorInfo[ Left ] = noPath;
	area1[ 3 ][ 2 ].doorInfo[ Right ] = noPath;
	area1[ 3 ][ 2 ].doorInfo[ Down ] = openPath;
	
	area1[ 4 ][ 2 ].doorInfo[ Up ] = openPath;
	area1[ 4 ][ 2 ].doorInfo[ Left ] = noPath;
	area1[ 4 ][ 2 ].doorInfo[ Right ] = noPath;
	area1[ 4 ][ 2 ].doorInfo[ Down ] = openPath;
	
	area1[ 5 ][ 2 ].doorInfo[ Up ] = openPath;
	area1[ 5 ][ 2 ].doorInfo[ Left ] = noPath;
	area1[ 5 ][ 2 ].doorInfo[ Right ] = openPath
	area1[ 5 ][ 2 ].doorInfo[ Down ] = noPath;
	
	area1[ 7 ][ 2 ].doorInfo[ Up ] = noPath;
	area1[ 7 ][ 2 ].doorInfo[ Left ] = openPath;
	area1[ 7 ][ 2 ].doorInfo[ Right ] = openPath;
	area1[ 7 ][ 2 ].doorInfo[ Down ] = noPath;
	//3列目の道情報
	area1[ 5 ][ 3 ].doorInfo[ Up ] = noPath;
	area1[ 5 ][ 3 ].doorInfo[ Left ] = openPath;
	area1[ 5 ][ 3 ].doorInfo[ Right ] = openPath
	area1[ 5 ][ 3 ].doorInfo[ Down ] = openPath;
	
	area1[ 6 ][ 3 ].doorInfo[ Up ] = openPath;
	area1[ 6 ][ 3 ].doorInfo[ Left ] = noPath;
	area1[ 6 ][ 3 ].doorInfo[ Right ] = noPath;
	area1[ 6 ][ 3 ].doorInfo[ Down ] = openPath;
	
	area1[ 7 ][ 3 ].doorInfo[ Up ] = openPath;
	area1[ 7 ][ 3 ].doorInfo[ Left ] = openPath;
	area1[ 7 ][ 3 ].doorInfo[ Right ] = openPath;
	area1[ 7 ][ 3 ].doorInfo[ Down ] = noPath;
	// 4列目のドア情報
	area1[ 3 ][ 4 ].doorInfo[ Up ] = noPath;
	area1[ 3 ][ 4 ].doorInfo[ Left ] = noPath;
	area1[ 3 ][ 4 ].doorInfo[ Right ] = noPath;
	area1[ 3 ][ 4 ].doorInfo[ Down ] = openPath;
	
	area1[ 4 ][ 4 ].doorInfo[ Up ] = openPath;
	area1[ 4 ][ 4 ].doorInfo[ Left ] = noPath;
	area1[ 4 ][ 4 ].doorInfo[ Right ] = noPath;
	area1[ 4 ][ 4 ].doorInfo[ Down ] = openPath;
	
	area1[ 5 ][ 4 ].doorInfo[ Up ] = openPath;
	area1[ 5 ][ 4 ].doorInfo[ Left ] = openPath;
	area1[ 5 ][ 4 ].doorInfo[ Right ] = noPath;
	area1[ 5 ][ 4 ].doorInfo[ Down ] = noPath;
	
	area1[ 7 ][ 4 ].doorInfo[ Up ] = noPath;
	area1[ 7 ][ 4 ].doorInfo[ Left ] = openPath;
	area1[ 7 ][ 4 ].doorInfo[ Right ] = openPath;
	area1[ 7 ][ 4 ].doorInfo[ Down ] = openPath;
	
	area1[ 8 ][ 4 ].doorInfo[ Up ] = openPath;
	area1[ 8 ][ 4 ].doorInfo[ Left ] = noPath;
	area1[ 8 ][ 4 ].doorInfo[ Right ] = noPath;

	// 5列目のドア情報
	area1[ 5 ][ 5 ].doorInfo[ Up ] = noPath;
	area1[ 5 ][ 5 ].doorInfo[ Left ] = noPath;
	area1[ 5 ][ 5 ].doorInfo[ Right ] = openPath;
	area1[ 5 ][ 5 ].doorInfo[ Down ] = noPath;
	
	area1[ 7 ][ 5 ].doorInfo[ Up ] = noPath;
	area1[ 7 ][ 5 ].doorInfo[ Left ] = openPath;
	area1[ 7 ][ 5 ].doorInfo[ Right ] = openPath;
	area1[ 7 ][ 5 ].doorInfo[ Down ] = noPath;
	// 6列目のドア情報
	area1[ 3 ][ 6 ].doorInfo[ Up ] = noPath;
	area1[ 3 ][ 6 ].doorInfo[ Left ] = noPath;
	area1[ 3 ][ 6 ].doorInfo[ Right ] = noPath;
	area1[ 3 ][ 6 ].doorInfo[ Down ] = openPath;
	
	area1[ 4 ][ 6 ].doorInfo[ Up ] = noPath;
	area1[ 4 ][ 6 ].doorInfo[ Left ] = noPath;
	area1[ 4 ][ 6 ].doorInfo[ Right ] = openPath;
	area1[ 4 ][ 6 ].doorInfo[ Down ] = openPath;
	
	area1[ 5 ][ 6 ].doorInfo[ Up ] = openPath;
	area1[ 5 ][ 6 ].doorInfo[ Left ] = openPath;
	area1[ 5 ][ 6 ].doorInfo[ Right ] = noPath;
	area1[ 5 ][ 6 ].doorInfo[ Down ] = openPath;
	
	area1[ 6 ][ 6 ].doorInfo[ Up ] = openPath;
	area1[ 6 ][ 6 ].doorInfo[ Left ] = noPath;
	area1[ 6 ][ 6 ].doorInfo[ Right ] = noPath;
	area1[ 6 ][ 6 ].doorInfo[ Down ] = openPath;
	
	area1[ 7 ][ 6 ].doorInfo[ Up ] = openPath;
	area1[ 7 ][ 6 ].doorInfo[ Left ] = noPath;
	area1[ 7 ][ 6 ].doorInfo[ Right ] = openPath;
	area1[ 7 ][ 6 ].doorInfo[ Down ] = openPath;
	
	area1[ 8 ][ 6 ].doorInfo[ Up ] = openPath;
	area1[ 8 ][ 6 ].doorInfo[ Left ] = openPath;
	area1[ 8 ][ 6 ].doorInfo[ Right ] = noPath;
	// 7列目のドア情報
	area1[ 4 ][ 7 ].doorInfo[ Up ] = noPath;
	area1[ 4 ][ 7 ].doorInfo[ Left ] = openPath;
	area1[ 4 ][ 7 ].doorInfo[ Right ] = openPath;
	area1[ 4 ][ 7 ].doorInfo[ Down ] = noPath;

	area1[ 8 ][ 7 ].doorInfo[ Up ] = noPath;
	area1[ 8 ][ 7 ].doorInfo[ Left ] = openPath;
	area1[ 8 ][ 7 ].doorInfo[ Right ] = openPath;
	// 8列目のドア情報
	area1[ 4 ][ 8 ].doorInfo[ Up ] = noPath;
	area1[ 4 ][ 8 ].doorInfo[ Left ] = noPath;
	area1[ 4 ][ 8 ].doorInfo[ Right ] = openPath;
	area1[ 4 ][ 8 ].doorInfo[ Down ] = noPath;

	area1[ 8 ][ 8 ].doorInfo[ Up ] = noPath;
	area1[ 8 ][ 8 ].doorInfo[ Left ] = noPath;
	area1[ 8 ][ 8 ].doorInfo[ Right ] = openPath;
	
	

	// ドアがないところの情報を修正
	dungeon[ 4 ][ 4 ].doorInfo[ North ] = noDoor;
	dungeon[ 4 ][ 4 ].doorInfo[ South ] = noDoor;
	dungeon[ 4 ][ 4 ].doorInfo[ West ] = noDoor;
	dungeon[ 4 ][ 3 ].doorInfo[ South ] = noDoor;
	dungeon[ 4 ][ 5 ].doorInfo[ North ] = noDoor;
	dungeon[ 3 ][ 4 ].doorInfo[ East ] = noDoor;
	// ロックされているドアの情報を修正
	dungeon[ 4 ][ 8 ].doorInfo[ East ] = lockedDoor;
	dungeon[ 5 ][ 4 ].doorInfo[ West ] = lockedDoor;
}

// ダンジョンの情報を画面に表示する
// 一つの部屋は5x5の大きさにする
// 1列目：北ドア、2列目：見やすくするための空きスペース、3列目：匂い、
// 4列目：西ドア、プリンスとStinker、東ドア、5列目：刀と健康ポーション、6列目：南ドア
void showDungeon()
{
	int x, y;

	// 部屋を一つずつ表示する
	for( y = 1; y <= 8; y++ )
	{

		// 1列目：北ドア
		for( x = 1; x <= 8; x++ )
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
		printf( "\n" );

		// 2列目：見やすくするための空きスペース
		for( x = 1; x <= 8; x++ )
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
		printf( "\n" );

		// 3列目：匂い
		for( x = 1; x <= 8; x++ )
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
		printf( "\n" );

		// 4列目：西ドア、プリンスとStinker、東ドア
		for( x = 1; x <= 8; x++ )
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
		printf( "\n" );

		// 5列目：刀と健康ポーション
		for( x = 1; x <= 8; x++ )
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
		printf( "\n" );

		// 6列目：南ドア
		for( x = 1; x <= 8; x++ )
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
		printf( "\n" );

	}

	// 記号の説明
	printf( "P = Prince, S = Stinker, $ = Super Stinker\n" );
	printf( "& = Stinker smell, # = Super Stinker smell\n" );
	printf( "K = Sword, P! = Prince has sword, H = Health potion\n" );
	printf( "D = Open Door, L = Locked door, * = Wall \n" );

	// プリンスの健康状況を表示
	printf( "Prince HP: %d\n", prince.healthPoints );
}
