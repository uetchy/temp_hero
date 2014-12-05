#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "renderer.h"

UIDescriptor uiDescriptor = {"╗", "╔", "╝", "╚", "═", "║"};

TermEnv getTermEnv(){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  TermEnv tenv = {w.ws_row, w.ws_col};

  return tenv;
}

// void wrapWithColor(char* colorname) {
//   if ( colorname == "red" ) {
//     printf("red");
//   }
// }

void renderFrame(int height){
  TermEnv tenv = getTermEnv();

  for ( int i=0; i < height; i++ ) {
    if ( i == 0 ) {
      printf("%s", uiDescriptor.frame_tl);
      for ( int j=0; j < tenv.row - 2; j++) {
        printf("%s", uiDescriptor.frame_h);
      }
      printf("%s", uiDescriptor.frame_tr);
    } else if ( i == height ) {
      printf("%s", uiDescriptor.frame_bl);
      for ( int j=0; j < tenv.row - 2; j++) {
        printf("%s", uiDescriptor.frame_h);
      }
      printf("%s", uiDescriptor.frame_br);
    } else {
      printf("%s", uiDescriptor.frame_v);
      for ( int j=0; j < tenv.row - 2; j++) {
        printf(" ");
      }
      printf("%s", uiDescriptor.frame_v);
    }
  }
}
