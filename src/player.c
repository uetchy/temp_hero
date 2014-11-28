#include "define.h"

void initializePlayer(struct Player player) {
  // Condition
  player.hp = 100000;
  player.beatenHiddenBoss = 0;

  // Items
  player.hasPotion = 0;
  player.hasKey    = 0;

  // Area
  player.c_area = 0;
  player.x = 8;
  player.y = 4;
}
