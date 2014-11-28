#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PERSON_NUM 100

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
//モンスター雑魚定義
typedef struct{           /* _person がタグ名 */
    char name[20];        /* 文字配列型のメンバ name */
    int hp;					/* HP */
	int power;				//パワー
	char point1[256];		//wpは攻撃部位
	char point2[256];
	char point3[256];
	char point4[256];
    int wp;         		//wpは弱点部位を示す　
	//弱点部位は攻撃部位を選択するときにいれる数字とれらし合わせて判断する
}monster_t;

//モンスター雑魚ステータス
  
// monster[] = { name, HP, atk, part1, part2, part3, part4, weakpart };
monster_t monsters[PERSON_NUM] = {{"Andy",3 , 2, "EEEE","??E","0","0",1},
								{"Ue-sama",4 , 2, "Eye","Throat","Armpit","Feet",2},
								{"Yazaki",3 , 3, "Right Hand","Right Feet","0","0",2},
								{"Iida",8 , 1, "Laptop","Mobile Phone","Hoodies","0",3},
								{"Yoshioka",6 , 2, "Hair","Throat","Pelvis","Nose",4},
								{"Muramatsu",2 , 8, "Hair","Keyboard","Mobile Phone","Mouse",2},
								{"とらえモン",5 , 1, "Pocket","Dorayaki","Tail","Rat",2},
								{"ビカチュウ",2 , 4, "Ear","Eye","Tail","Cheek",4},
								{"ぷにょよ",3 , 2, "邪魔ぷよ","１れんさ","５れんさ","１０れんさ",4},
								{"matsuko",10 , 1, "Eye","Throat","Jaw","Hair",3},
								{"ボス",25 , 3, "頭","腕","おなか","えんだ―",4},
								{"裏ボス",20 , 3, "頭","顎","脇腹","足",1}};

// 調整する値はここまで
//==========================================

// プリンスとStinkerの戦闘結果
const int princeWins		= 1;
const int princeLoses		= 2;

// StinkerのＨＰを格納する変数
int stinker1HP;
int stinker2HP;
int weakpoint;


// 関数のプロトタイプ
void testStinkerFight( void );
void stinkerFightLoop( int, int, int, int );
int stinkerFight( int *, int, int, int );
int princeAttack( int , int );
int stinkerAttack( int );


int main( void )
{
	char c;

	srand( time( NULL ) );			// Stinker戦闘のため乱数を初期化

	printf( "- T e m p o r a r y  H e r o -\n" );
  printf(" ___ ___         __                _____.___.                  .__\n");
  printf(" /   |   \\_____  |  | __ ____   ____\\__  |   |__ __ __ __  _____|  |__ __\n");
  printf("/    ~    \\__  \\ |  |/ // __ \\ /    \\/   |   |  |  \\  |  \\/  ___/  |  \\__\\\n");
  printf("\\    Y    // __ \\|    <\\  ___/|   |  \\____   |  |  /  |  /\\___ \\|   Y  \\/ __ \\_\n");
  printf(" \\___|_  /(____  /__|_ \\___  >___|  / ______|____/|____//____  >___|  (____  /\n");
  printf( "Alpha version\n" );
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
			stinkerFightLoop( heroHP, 0, 0 ,0);
			break;
		case '2':
			// 刀ありのStinker戦闘
			stinkerFightLoop( heroHP, 0, 1 ,0);
			break;
		case '3':
			// 刀なしのSuper Stinker戦闘
			stinkerFightLoop( heroHP, 0, 1 ,1 );
			break;
		case '4':
			// 刀なしのSuper Stinker戦闘
			stinkerFightLoop( heroHP, 1, 0 ,1);
			break;
		case '5':
			// 刀ありのSuper Stinker戦闘
			stinkerFightLoop( heroHP, 2, 1 ,1);
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
	int fightNumber = 2;
	int result, i;
	int princeWinNo = 0;
	int startHP = princeHP;
	int totalPrinceHP = 0;

	
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
int stinkerFight( int *princeHP, int monnsuta, int hasSword ,int posyonn )
{

	//モンスターを決めるための変数
	int mo;
	if(monnsuta == 0){
	//雑魚モンスターをランダムにきめるための変数
	mo = rand() % 10;
	}else if(monnsuta == 1){
	mo =10;
	}else if(monnsuta == 1){
	mo =11;
	}
	int stinkerHP;
	stinkerHP = monsters[mo].hp;
	
	printf( "\nPrince HP: %d\n", *princeHP );
	printf( "Stinker HP: %d\n", stinkerHP );

	
	while( 1 )
	{
		if(posyonn == 1){
		//プレイヤーのできる行動を指示
		printf("ポーションを使う：0 \n");
		
		}
		
		
		printf("どの部位を攻撃しますか？ \n");
		printf("%s :1 \n", monsters[mo].point1);
		printf("%s :2 \n", monsters[mo].point2);
		if(0 != atoi(monsters[mo].point3)){
		printf("%s :3 \n", monsters[mo].point3);
		}
		if(0 != atoi(monsters[mo].point4)){
		printf("%s :4 \n", monsters[mo].point4);
		}
		
		//入力される値を保持するための変数
		int a;
		char bb[80];
		//プレイヤーがどこを攻撃するか決める　数字が入力される。
		printf("数値を入力して下さい：");
		gets(bb);
		a=atoi(bb);
		printf("入力された数値は　%d　です\n",a);
		//入力された値が弱点か弱点ではないか判断
		if(a == monsters[mo].wp){
		weakpoint = 1;
		}else if(a <= 4){
		weakpoint = 0;
		}
		if(a == 0 && posyonn == 1){	//ポーションを使うと宣言	
		*princeHP +=10;
		posyonn = 0;
		if(*princeHP >= heroHP){
		*princeHP = heroHP;
		}		
		printf("へーローHP %d \n",*princeHP);
		*princeHP -= stinkerAttack( mo );
		printf("へーローHP %d \n",*princeHP);
		// プリンスが死んだかどうかのチェック
		if( *princeHP <= 0 ){
			printf("雑魚勝利 \n");
			return princeLoses;
		}
		
		}else if(a <= 4){//攻撃すると宣言
		// プリンスは攻撃する
		stinkerHP -= princeAttack( hasSword , weakpoint);
		printf("雑魚HP %d \n",stinkerHP);
		// Stinkerを倒したかどうかのチェック
		if( stinkerHP <= 0 ){
				printf("ヒーロー勝利 \n");
			return princeWins;
		}
		// Stinkerは反撃する
		*princeHP -= stinkerAttack( mo );
		printf("へーローHP %d \n",*princeHP);
		// プリンスが死んだかどうかのチェック
		if( *princeHP <= 0 ){
			printf("雑魚勝利 \n");
			return princeLoses;
		}
		}else if(a > 4){//それ以外の数字が入力された
			printf("入力の数字が間違っています。 \n");
		
		
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
	printf("へーローの攻撃  %dダメージ \n",damage);

	return damage;
}

// Enemy attack
int stinkerAttack( int mo ){
	int damage = stinkerAttackRange;
	printf("%s の攻撃  %dダメージ \n",monsters[mo].name ,damage);
	return damage;
}