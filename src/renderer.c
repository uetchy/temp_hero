#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "renderer.h"

UIDescriptor uiDescriptor = {"╗", "╔", "╝", "╚", "═", "║"};

void disableCursor() {
  printf("\x1b[>5h");
}

void clearLine(){
  printf("\x1b[2K\r");
}

void clearLines(int length){
  for (int i=0; i < length; i++) {
    printf("\x1b[2K\r\x1b[1A");
  }
}

void clearScreen(){
  printf("\x1b[2J\x1b[f");
}

void moveCursor(int x, int y) {
  printf("\x1b[%d;%df", x, y);
}

TermEnv getTermEnv(){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  TermEnv tenv = {w.ws_row, w.ws_col};

  return tenv;
}

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
    printf("%s", tmp);
  }
}

void renderFrame(int row){
  TermEnv tenv = getTermEnv();

  moveCursor(tenv.row-row-1, 0);

  for ( int i=0; i < row+2; i++ ) {
    if ( i == 0 ) {
      printf("%s", uiDescriptor.frame_tl);
      for ( int j=0; j < tenv.column - 2; j++) {
        printf("%s", uiDescriptor.frame_h);
      }
      printf("%s", uiDescriptor.frame_tr);
    } else if ( i == row+1 ) {
      printf("%s", uiDescriptor.frame_bl);
      for ( int j=0; j < tenv.column - 2; j++) {
        printf("%s", uiDescriptor.frame_h);
      }
      printf("%s", uiDescriptor.frame_br);
    } else {
      printf("%s", uiDescriptor.frame_v);
      for ( int j=0; j < tenv.column - 2; j++) {
        printf(" ");
      }
      printf("%s", uiDescriptor.frame_v);
    }
  }

  moveCursor(tenv.row - row, 3);
}
