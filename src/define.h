// Constants

// Monster
// #define M_NAME 0
// #define M_HP 1
// #define M_POWER 2
// #define M_AA 3
// #define M_PARTS 4

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
#define MAX_WIDTH 8
#define MAX_HEIGHT 8

// Structures
struct Room {
  int uniqueBossId;  // 固有敵のインデックス（nullならいない）
  int hasPotion;     // ポーションが落ちているか
  int hasKey;        // 鍵が落ちているか？
  char hint[256];    // ヒント内容（nullならヒント無し）
  int doorInfo[4];   // ドア開通状態
  int canJump;       // 次のエリアにジャンプ出来るか
  int playerVisited; // プレイヤーが通ったか
};

struct Player {
  int hp;               // HP
  int hasKey;           // 鍵を持っているか？
  int hasPotion;        // ポーションを持っているか？
  int beatenHiddenBoss; // 裏ボスを倒したか？
  int c_area;           // 今プレイヤーがいるエリア
  int x;                // 現在地X
  int y;                // 現在地Y
};

// Declare prototypes


// Renderer
void render();

// Helper
void checkEncountGauge();
