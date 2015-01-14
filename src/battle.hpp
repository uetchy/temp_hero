#ifndef H_BATTLE
#define H_BATTLE

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <string>

#include "define.hpp"
#include "renderer.hpp"

struct Monster { // _person がタグ名
  char name[100]; // 文字配列型のメンバ name
  int hp;
  int power;
  char point1[100]; // wpは攻撃部位
  char point2[100];
  char point3[100];
  char point4[100];
  int wp; // wpは弱点部位のインデックスを示す　
};

int battle(Player*, int);
int attack(Frame* textFrame, Frame* viewFrame, Player* player, Monster* monster, int input);
void usePotion(Frame* frame, Player* player);
int computeDamage(Player* player);

#endif
