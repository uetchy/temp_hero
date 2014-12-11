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

#define FO_TOP 0
#define FO_RIGHT 1
#define FO_BOTTOM 2
#define FO_LEFT 3

typedef struct {
  char frame_tr[20];
  char frame_tl[20];
  char frame_br[20];
  char frame_bl[20];
  char frame_h[20];
  char frame_v[20];
} Border;

typedef struct {
  int x;
  int y;
  int absoluteX;
  int absoluteY;
  int row;
  int cols;
} FrameInfo;

class Frame {
private:
  int orientation;
  int hasBorder;
  FrameInfo frameInfo;
  FrameInfo inlineFrameInfo;
  WINDOW *framescr;
  WINDOW *inlinescr;
  Border borders = {"╗", "╔", "╝", "╚", "═", "║"};

  void renderBorder();
  int getRow();
  int getCols();
  int getIrow();
  int getIcols();
public:
  Frame(int row, int cols, int orientation, int hasBorder = false);
  void filledWith(const char* str);
  void println( const char* format, ... );
  void print( const std::vector<std::string> strings, int delayMsec = 0);
  void clear();
  void bringToFront();
};

void wrapWithColor(const char *color, char *str);
void iprint( int msec, std::vector<std::string> strings);

#endif
