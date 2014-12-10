#ifndef H_RENDERER
#define H_RENDERER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <stdarg.h>
#include <time.h>
#include <string>
#include <vector>

typedef struct {
  char frame_tr[20];
  char frame_tl[20];
  char frame_br[20];
  char frame_bl[20];
  char frame_h[20];
  char frame_v[20];
} UIDescriptor;

class Frame {
private:
  int row;
  int frameX;
  int frameY;
  WINDOW *framescr;
  WINDOW *inlinescr;
  UIDescriptor uiDescriptor = {"╗", "╔", "╝", "╚", "═", "║"};
public:
  Frame(int row);
  int getRow();
  void applyUIDescriptor(char *tr, char *tl, char *br, char *bl, char *h, char *v);
  void render();
  void print( const char* format, ... );
  void iprint( int msec, std::vector<std::string> strings);
  void clear();
  void bringToFront();
};

void wrapWithColor(const char *color, char *str);
void iprint( int msec, std::vector<std::string> strings);

#endif
