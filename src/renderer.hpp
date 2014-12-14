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

// Struct

struct RFOrientation {
  static const int TOP;
  static const int BOTTOM;
};

struct Border {
  char frame_tr[4];
  char frame_tl[4];
  char frame_br[4];
  char frame_bl[4];
  char frame_h[4];
  char frame_v[4];
};

struct FrameInfo {
  int x;
  int y;
  int absoluteX;
  int absoluteY;
  int row;
  int cols;
};

// Functions

void print( const std::vector<std::string> strings, int delayMsec = 0);
void filledWith(const char* str);
std::vector<std::string> centerizedStrings(std::vector<std::string> strings);
std::string seqStr(int width, std::string start, std::string mid, std::string end);

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
  Frame(int inline_row, int orientation);
  void destroy();
  WINDOW* getView();
  int cols();
  int lines();
  void filledWith(const char* str);
  void println( const char* format, ... );
  void print( const std::vector<std::string> strings, int delayMsec = 0);
  void clear();
  void bringToFront();
};

#endif
