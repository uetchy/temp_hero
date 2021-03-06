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
  static const int TOP_LEFT;
  static const int TOP_RIGHT;
  static const int BOTTOM_LEFT;
  static const int BOTTOM_RIGHT;
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
public:
  Frame(int inline_cols, int inline_row, int orientation);
  void destroy();
  WINDOW* getView();
  int cols();
  int lines();
  int getIrow();
  int getIcols();
  void move(int y, int x);
  void filledWith(const char* str, int delayMsec = 0);
  void println( const char* format, ... );
  void print( const std::vector<std::string> strings, int delayMsec = 0);
  void clear();
  void update();
};

std::vector<std::string> filledWith(Frame frame, const char* str);
std::vector<std::string> centerizedStrings(std::vector<std::string> strings);
std::string seqStr(int width, std::string start, std::string mid, std::string end);

#endif
