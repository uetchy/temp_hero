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
void initialisearealist();
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
		showarealist();							// ダンジョンの情報を表示
		showRoomInfo();							// 部屋の情報を表示

		checkEncountGauge();					// Stinkerがいるなら戦闘
		if( PlayerDead )						// Stinkerに負けた（敗北）
		{
			break;
		}
		if( rescuedPrincess )					// Super Stinkerを倒した（勝利）
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
