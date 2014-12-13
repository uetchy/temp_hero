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
