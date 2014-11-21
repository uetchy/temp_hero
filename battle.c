#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//==========================================
// 以下の値を調整して，ゲームバランスを決める
// 調整の目標：プリンスの勝率は次のようにする
// 対Stinker(刀なし）：10%
// 対Stinker(刀あり）：85%
// 対Super Stinker(刀なし）：5%
// 対Super Stinker(刀あり）：67%

// プリンスとStinkerの最大ＨＰ
const int heroHP			= 15;
const int stinker1StartHP		= 12;
const int stinker2StartHP		= 12;
const int superStinkerStartHP	= 18;

// 攻撃のダメージを決める値
const int princeAttackRange			= 1;
const int stinkerAttackRange		= 2;
const int superStinkerAttackRange	= 3;

// 調整する値はここまで
//==========================================

// プリンスとStinkerの戦闘結果
const int princeWins		= 1;
const int princeLoses		= 2;

// StinkerのＨＰを格納する変数
int stinker1HP;
int stinker2HP;
int weakpoint;
char a[10][4][100];
//モンスター（^－^）の部位　プラス弱点


// 関数のプロトタイプ
void testStinkerFight( void );
void stinkerFightLoop( int, int, int, int );
int stinkerFight( int *, int, int, int );
int princeAttack( int , int );
int stinkerAttack( void );


int main( void )
{
	char c;

	srand( time( NULL ) );			// Stinker戦闘のため乱数を初期化

	printf( "**********************************************************\n" );
	printf( "* Alfa version to test the balance of the Stinker fights *\n" );
	printf( "**********************************************************\n\n" );
	testStinkerFight();					// Stinkerがいるなら戦闘

	printf( "\nPress any key to continue.\n" );
	c = getchar();

	return 0;
}

// Stinkerがいるなら戦闘
void testStinkerFight( void )
{
	char c, userSelection;
	int endTestSession = 0;

	while( !endTestSession )
	{

		printf( "1) Fight Stinker without sword\n" );
		printf( "2) Fight Stinker with sword\n" );
		printf( "3) Fight Super Stinker without sword\n" );
		printf( "4) Fight Super Stinker with sword\n" );
		printf( "Q) Stop test session\n" );
		printf( "Please enter your selection: " );

		// ユーザの選択を獲得
		c = getchar();
		userSelection = c;
		while( ( c = getchar() ) != '\n' );
		// TODO: ここを変えれば入力方法換えられそう

		switch( userSelection )
		{
		case '1':
			// 刀なしのStinker戦闘
			stinkerFightLoop( heroHP, stinker1StartHP, 0 ,0);
			break;
		case '2':
			// 刀ありのStinker戦闘
			stinkerFightLoop( heroHP, stinker1StartHP, 1 ,0);
			break;
		case '3':
			// 刀なしのSuper Stinker戦闘
			stinkerFightLoop( heroHP, superStinkerStartHP, 1 ,1 );
			break;
		case '4':
			// 刀なしのSuper Stinker戦闘
			stinkerFightLoop( heroHP, superStinkerStartHP, 0 ,0);
			break;
		case '5':
			// 刀ありのSuper Stinker戦闘
			stinkerFightLoop( heroHP, superStinkerStartHP, 1 ,0);
			break;
		case 'Q':
			endTestSession = 1;
			break;
		default:
			printf( "Illegal input\n" );
			break;
		}
	}

}

// 複数のStinker戦闘をシミュレーションして、総合結果を表示する
// 戦闘終了のプリンスに残っているＨＰの平均も計算する
void stinkerFightLoop( int princeHP, int stinkerHP, int hasSword ,int weakpoint)
{
	int fightNumber = 1000;
	int result, i;
	int princeWinNo = 0;
	int startHP = princeHP;
	int totalPrinceHP = 0;

	printf( "\nPrince HP: %d\n", princeHP );
	printf( "Stinker HP: %d\n", stinkerHP );

	for( i = 1; i <= fightNumber; i++ )
	{
		result = stinkerFight( &princeHP, stinkerHP, hasSword ,weakpoint);
		if( result == princeWins )
		{
			princeWinNo++;
			totalPrinceHP += princeHP; // 残りＨＰの平均計算のためＨＰ合計を更新
		}
		princeHP = startHP; // 次の戦闘のためにプリンスのＨＰを初期値に戻す
	}

	// プリンスの勝利数を表示
	printf( "Prince number of wins: %d ( %f%% )\n", princeWinNo, ( princeWinNo / (double) fightNumber ) * 100.0 );
	// プリンスの残りＨＰの平均を表示
	printf( "Average remaining prince HP: %f\n\n", ( totalPrinceHP / (double) fightNumber ) );

}

// １回のプリンスとStinkerの戦闘シミュレーション
// 戦闘の終了のＨＰを呼び出された関数に伝えるためにポインタ*princeHPを使用
int stinkerFight( int *princeHP, int stinkerHP, int hasSword ,int weakpoint )
{
	while( 1 )
	{
		// プリンスは攻撃する
		stinkerHP -= princeAttack( hasSword , weakpoint);
		// Stinkerを倒したかどうかのチェック
		if( stinkerHP <= 0 )
		{
			return princeWins;
		}
		// Stinkerは反撃する
		*princeHP -= stinkerAttack();
		// プリンスが死んだかどうかのチェック
		if( *princeHP <= 0 )
		{
			return princeLoses;
		}

	}
	return 0;
}

// へろの攻撃
int princeAttack( int hasSword ,int weakpoint )
{
	// 攻撃のダメージ
	int damage = princeAttackRange;
	// 刀があると攻撃力アップ
	if( hasSword )
	{
		damage = damage*2;
	}
	if( weakpoint )
	{
		damage = damage*2;
	}
	return damage;
}

// Enemy attack
int stinkerAttack( void )
{
	int damage = stinkerAttackRange;
	return damage;
}
