#include <stdio.h>

typedef struct
{
    int uniqueBossId,  // 固有敵のインデックス（nullならいない）
    int hasPotion,     // ポーションが落ちているか
    int hasKey,           // 鍵が落ちているか？
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

areaList = [
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

