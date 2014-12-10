#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "renderer.hpp"

UIDescriptor uiDescriptor = {"╗", "╔", "╝", "╚", "═", "║"};

int winX;
int winY;

WINDOW *framescr;

void applyUIDescriptor(char *tr, char *tl, char *br, char *bl, char *h, char *v) {
  strcpy(uiDescriptor.frame_tr, tr);
  strcpy(uiDescriptor.frame_tl, tl);
  strcpy(uiDescriptor.frame_br, br);
  strcpy(uiDescriptor.frame_bl, bl);
  strcpy(uiDescriptor.frame_h, h);
  strcpy(uiDescriptor.frame_v, v);
}

void wrapWithColor(const char *colorname, char *str) {
  char tmp[256];
  strcpy(tmp, str);
  if ( strcmp(colorname, "red") == 0) {
    sprintf(str, "\x1b[31m%s\x1b[0m", tmp);
  } else if ( strcmp(colorname, "green") == 0) {
    sprintf(str, "\x1b[32m%s\x1b[0m", tmp);
  } else if ( strcmp(colorname, "allred") == 0) {
    sprintf(str, "\x1b[41m\x1b[31m%s\x1b[0m", tmp);
  }
}

void renderBar(int length, int color_num) {
  char tmp[256];
  sprintf(tmp, "\x1b[4%dm\x1b[3%dm%s\x1b[0m", color_num, color_num, "|");

  for (int i=0; i < length; i++) {
    printw("%s", tmp);
  }
}

void renderFrame(int row){
  getmaxyx(stdscr, winY, winX);

  framescr = newwin(row, winX, winY-row, 0);

  int frameX;
  int frameY;
  getmaxyx(framescr, frameY, frameX);

  // move(winY-row-1, 0);
  move(0, 0);

  for ( int i=0; i < row+2; i++ ) {
    if ( i == 0 ) {
      printw("%s", uiDescriptor.frame_tl);
      for ( int j=0; j < frameX - 2; j++) {
        printw("%s", uiDescriptor.frame_h);
      }
      printw("%s", uiDescriptor.frame_tr);
    } else if ( i == row+1 ) {
      printw("%s", uiDescriptor.frame_bl);
      for ( int j=0; j < frameX - 2; j++) {
        printw("%s", uiDescriptor.frame_h);
      }
      printw("%s", uiDescriptor.frame_br);
    } else {
      printw("%s", uiDescriptor.frame_v);
      for ( int j=0; j < frameX - 2; j++) {
        printw(" ");
      }
      printw("%s", uiDescriptor.frame_v);
    }
  }

  move(0, 3);
}
