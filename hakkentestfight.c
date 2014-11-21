// StinkinDungeon_Alfa.cpp : Defines the entry point for the console application.
//

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
const int princeStartHP			= 15;
const int zakoStartHP		= 5;
const int HBossStartHP		= 20;
const int RBossStartHP	= 25;

// 攻撃のダメージ一覧	
const int princeAttackRange			= 1;
const double swordDamageRatio		= 1;
const double weakpartratio			= 2;
const int zakoAttackRange		= 2;
const int HBossAttackRange		= 3;
const int RBossAttackRange	= 4;

// 調整する値はここまで
//==========================================

// プリンスとStinkerの戦闘結果
const int princeWins		= 1;
const int princeLoses		= 2;

// StinkerのＨＰを格納する変数
int zakoHP;
int HBossHP;
int RBossHP;

// 関数のプロトタイプ
void testStinkerFight( void );
void zakoFightLoop( int, int, int, int );
int zakoFight( int *, int, int, int );
void HBossFightLoop( int, int, int, int );
int HBossFight( int *, int, int, int );
void RBossFightLoop( int, int, int, int );
int RBossFight( int *, int, int, int );
int princeAttack( int, int );
int zakoAttack( void );
int HBossAttack( void );
int RBossAttack( void );

int main( void )
{
	char c;

	srand( time( NULL ) );			// Stinker戦闘のため乱数を初期化

	printf( "**********************************************************\n" );
	printf( "* Alfa version to test the balance of the fights *\n" );
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

		printf( "1) Fight zako without sword\n" );
		printf( "2) Fight zako with sword\n" );
		printf( "3) Fight HBoss without sword in other part\n" );
		printf( "4) Fight HBoss without sword weak or with sword in different part\n" );
		printf( "5) Fight HBoss with sword in weak part\n" );
		printf( "6) Fight RBoss without sword in other part\n" );
		printf( "7) Fight RBoss without sword weak or with sword in different part\n" );
		printf( "8) Fight RBoss with sword in weak part\n" );
		printf( "Q) Stop test session\n" );
		printf( "Please enter your selection: " );

		// ユーザの選択を獲得
		c = getchar();
		userSelection = c;
		while( ( c = getchar() ) != '\n' )
			;
		switch( userSelection )
		{
		case '1':
			// 刀なしのzako戦闘
			zakoFightLoop( princeStartHP, zakoStartHP, 0, 0 );
			break;
		case '2':
			// 刀ありのStinker戦闘
			zakoFightLoop( princeStartHP, zakoStartHP, 1, 0 );
			break;
		case '3':
			// 刀なしのHBoss戦闘,弱点X
			HBossFightLoop( princeStartHP, HBossStartHP, 0, 0 );
			break;
		case '4':
			// 刀なしのHBoss戦闘,弱点O or 刀ありのHBoss戦闘,弱点X
			HBossFightLoop( princeStartHP, HBossStartHP, 1, 0 );
			break;
		case '5':
			// 刀ありのHBoss戦闘,弱点O
			HBossFightLoop( princeStartHP, HBossStartHP, 1, 1 );
			break;
		case '6':
			// 刀なしのRBoss戦闘,弱点X
			RBossFightLoop( princeStartHP, RBossStartHP, 0, 0 );
			break;
		case '7':
			// 刀なしのRBoss戦闘,弱点O or 刀ありのRBoss戦闘,弱点X
			RBossFightLoop( princeStartHP, RBossStartHP, 1, 0 );
			break;
		case '8':
			// 刀ありのRBoss戦闘,弱点O
			RBossFightLoop( princeStartHP, RBossStartHP, 1, 1 );
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

// 複数のzako戦闘をシミュレーションして、総合結果を表示する
// 戦闘終了のプリンスに残っているＨＰの平均も計算する
void zakoFightLoop( int princeHP, int zakoHP, int hasSword, int weakpart )
{
	int fightNumber = 1000;
	int result, i;
	int princeWinNo = 0;
	int startHP = princeHP;
	int totalPrinceHP = 0;

	printf( "\nPrince HP: %d\n", princeHP );
	printf( "Zako HP: %d\n", zakoHP );

	for( i = 1; i <= fightNumber; i++ )
	{
		result = zakoFight( &princeHP, zakoHP, hasSword, weakpart );
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

// 複数のHBoss戦闘をシミュレーションして、総合結果を表示する
// 戦闘終了のプリンスに残っているＨＰの平均も計算する
void HBossFightLoop( int princeHP, int HBossHP, int hasSword, int weakpart )
{
	int fightNumber = 1000;
	int result, i;
	int princeWinNo = 0;
	int startHP = princeHP;
	int totalPrinceHP = 0;

	printf( "\nPrince HP: %d\n", princeHP );
	printf( "HBoss HP: %d\n", HBossHP );

	for( i = 1; i <= fightNumber; i++ )
	{
		result = HBossFight( &princeHP, HBossHP, hasSword, weakpart );
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

// 複数のRBoss戦闘をシミュレーションして、総合結果を表示する
// 戦闘終了のプリンスに残っているＨＰの平均も計算する
void RBossFightLoop( int princeHP, int RBossHP, int hasSword, int weakpart )
{
	int fightNumber = 1000;
	int result, i;
	int princeWinNo = 0;
	int startHP = princeHP;
	int totalPrinceHP = 0;

	printf( "\nPrince HP: %d\n", princeHP );
	printf( "RBoss HP: %d\n", RBossHP );

	for( i = 1; i <= fightNumber; i++ )
	{
		result = RBossFight( &princeHP, RBossHP, hasSword, weakpart );
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

// １回のプリンスとSzakoの戦闘シミュレーション
// 戦闘の終了のＨＰを呼び出された関数に伝えるためにポインタ*princeHPを使用
int zakoFight( int *princeHP, int zakoHP, int hasSword, int weakpart )
{
	while( 1 )
	{
		// プリンスは攻撃する
		zakoHP -= princeAttack( hasSword, weakpart );
		// Stinkerを倒したかどうかのチェック
		if( zakoHP <= 0 )
		{
			return princeWins;
		}
		// Stinkerは反撃する
		*princeHP -= zakoAttack();
		// プリンスが死んだかどうかのチェック
		if( *princeHP <= 0 )
		{
			return princeLoses;
		}
		
	}
	return 0;
}

// １回のプリンスとHBossの戦闘シミュレーション
// 戦闘の終了のＨＰを呼び出された関数に伝えるためにポインタ*princeHPを使用
int HBossFight( int *princeHP, int HBossHP, int hasSword, int weakpart )
{
	while( 1 )
	{
		// プリンスは攻撃する
		HBossHP -= princeAttack( hasSword , weakpart );
		// Stinkerを倒したかどうかのチェック
		if( zakoHP <= 0 )
		{
			return princeWins;
		}
		// Stinkerは反撃する
		*princeHP -= HBossAttack();
		// プリンスが死んだかどうかのチェック
		if( *princeHP <= 0 )
		{
			return princeLoses;
		}
		
	}
	return 0;
}

// １回のプリンスとRBossの戦闘シミュレーション
// 戦闘の終了のＨＰを呼び出された関数に伝えるためにポインタ*princeHPを使用
int RBossFight( int *princeHP, int RBossHP, int hasSword, int weakpart )
{
	while( 1 )
	{
		// プリンスは攻撃する
		RBossHP -= princeAttack( hasSword , weakpart );
		// Stinkerを倒したかどうかのチェック
		if( RBossHP <= 0 )
		{
			return princeWins;
		}
		// Stinkerは反撃する
		*princeHP -= RBossAttack();
		// プリンスが死んだかどうかのチェック
		if( *princeHP <= 0 )
		{
			return princeLoses;
		}
		
	}
	return 0;
}

// プリンスの攻撃
int princeAttack( int hasSword, int weakpart )
{
	// 攻撃のダメージは乱数で決める
	int damage = princeAttackRange;
	// 刀があると攻撃力アップ
	if( hasSword || weakpart)
	{
		damage *= princeAttackRange + swordDamageRatio;
	}
	if( hasSword && weakpart )
	{
		damage *= weakpartratio + princeAttackRange + swordDamageRatio ;
	}
	return damage;
}

// zakoの攻撃
int zakoAttack( void )
{
	// 攻撃のダメージは乱数で決める
	int damage = zakoAttackRange;
	return damage;
}

// HBossの攻撃
int HBossAttack( void )
{
	// 攻撃のダメージは乱数で決める
	int damage = HBossAttackRange;
	return damage;
}

// RBossの攻撃
int RBossAttack( void )
{
	// 攻撃のダメージは乱数で決める
	int damage = RBossAttackRange;
	return damage;
}

