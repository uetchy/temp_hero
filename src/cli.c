#include <stdio.h>

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
