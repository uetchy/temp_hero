#include "player.hpp"

void initPlayer(Player* player) {
  // Condition
  player->hp = 15;
  player->beatenHBoss = 0;

  // Items
  player->hasPotion = 0;
  player->hasKey    = 0;

  // Area
  player->direction = D_UP;
  player->c_area = 0;
  player->x      = 3;
  player->y      = 7;
}

int isPlayerMoved(int a1, int x1, int y1, int a2, int x2, int y2) {
  if (a1 != a2 || x1 != x2 || y1 != y2) {
    return 1;
  } else {
    return 0;
  }
}
