#ifndef H_DEFINE
#define H_DEFINE

// Constants
#define PERSON_NUM 100
#define MAX_PLAYER_HP 15

// Boss
#define B_BOSS 0
#define B_HIDDEN_BOSS 1

// Condition
#define DC_NIL 0
#define DC_OPEN 1
#define DC_LOCKED 2

// Direction
#define D_UP 0
#define D_RIGHT 1
#define D_DOWN 2
#define D_LEFT 3

// World settings
#define MAX_AREA 2
#define MAX_WIDTH 8
#define MAX_HEIGHT 8

// Structures
typedef struct {
  int uniqueBossId;  // 固有敵のインデックス（nullならいない）
  int hasPotion;     // ポーションが落ちているか
  int hasKey;        // 鍵が落ちているか？
  char hint[256];    // ヒント内容（nullならヒント無し）
  int doorInfo[4];   // ドア開通状態
  int canJump;       // 次のエリアにジャンプ出来るか
  int playerVisited; // プレイヤーが通ったか
} Room;

typedef struct {
  int hp;               // HP
  int hasKey;           // 鍵を持っているか？
  int hasPotion;        // ポーションを持っているか？
  int beatenBoss;       // ボスを倒したか？
  int beatenHBoss;      // 裏ボスを倒したか？
  int c_area;           // 今プレイヤーがいるエリア
  int x;                // 現在地X
  int y;                // 現在地Y
} Player;

typedef struct { // _person がタグ名
  char name[100];    // 文字配列型のメンバ name
  int hp;
  int power;
  char point1[100]; //wpは攻撃部位
  char point2[100];
  char point3[100];
  char point4[100];
  int wp;           //wpは弱点部位のインデックスを示す　
} Monster;

#endif
