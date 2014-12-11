#include "renderer.hpp"

// Helper
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

void iprint( int msec, std::vector<std::string> strings) {
  struct timespec req = {0, msec * 1000000}; // 1 milli-sec = 1000000
  for ( std::string str : strings ) {
    printw(str.c_str());
    refresh();
    nanosleep(&req, NULL);
  }
}

// Frame class
Frame::Frame(int row, int cols, int orientation, int createBorder) {
  this->frameInfo.row  = row;
  this->frameInfo.cols = cols;
  this->orientation = orientation;
  this->hasBorder = createBorder;

  switch(orientation) {
    case FO_TOP:
      this->frameInfo.absoluteX = 0;
      this->frameInfo.absoluteY = 0;
      break;
    case FO_RIGHT:
      this->frameInfo.absoluteX = COLS - cols;
      this->frameInfo.absoluteY = 0;
      break;
    case FO_BOTTOM:
      this->frameInfo.absoluteX = 0;
      this->frameInfo.absoluteY = LINES - row;
      break;
    case FO_LEFT:
      this->frameInfo.absoluteX = 0;
      this->frameInfo.absoluteY = 0;
      break;
  }

  // Frame
  // DEF: WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
  framescr = newwin(
    this->frameInfo.row,
    this->frameInfo.cols,
    this->frameInfo.absoluteY,
    this->frameInfo.absoluteX
  );

  // Inline frame
  if ( hasBorder ) {
    this->inlineFrameInfo.absoluteX = 2;
    this->inlineFrameInfo.absoluteY = LINES - row - 1;
    this->inlineFrameInfo.row       = row - 2;
    this->inlineFrameInfo.cols      = cols - 4;
    renderBorder();
  } else {
    this->inlineFrameInfo.absoluteX = 0;
    this->inlineFrameInfo.absoluteY = LINES - row;
    this->inlineFrameInfo.row       = row;
    this->inlineFrameInfo.cols      = cols;
  }

  inlinescr = subwin(
    framescr,
    this->inlineFrameInfo.row,
    this->inlineFrameInfo.cols,
    this->inlineFrameInfo.absoluteY,
    this->inlineFrameInfo.absoluteX
  );

  // Update view
  wrefresh(framescr);
}

int Frame::getRow() { return this->frameInfo.row; }
int Frame::getCols() { return this->frameInfo.cols; }
int Frame::getIrow() { return this->inlineFrameInfo.row; }
int Frame::getIcols() { return this->inlineFrameInfo.cols; }

void Frame::filledWith(const char* str) {
  wmove(inlinescr, 0, 0);
  for (int x=0; x < getIcols(); x++)
    for (int y=0; y < getIrow(); y++)
      mvwprintw(inlinescr, y, x, str);
  bringToFront();
}

void Frame::renderBorder() {
  wmove(framescr, 0, 0);

  for ( int i=0; i < getRow(); i++ ) {
    if ( i == 0 ) {
      wprintw(framescr, "%s", borders.frame_tl);
      for ( int j=0; j < getCols() - 2; j++) {
        wprintw(framescr, "%s", borders.frame_h);
      }
      wprintw(framescr, "%s", borders.frame_tr);
    } else if ( i == getRow() - 1 ) {
      wprintw(framescr, "%s", borders.frame_bl);
      for ( int j=0; j < getCols() - 2; j++) {
        wprintw(framescr, "%s", borders.frame_h);
      }
      wprintw(framescr, "%s", borders.frame_br);
    } else {
      wprintw(framescr, "%s", borders.frame_v);
      for ( int j=0; j < getCols() - 2; j++) {
        // wmove(framescr, i, j+2);
        wprintw(framescr, " ");
      }
      wprintw(framescr, "%s", borders.frame_v);
    }
  }
}

void Frame::println( const char* format, ... ) {
  va_list args;
  va_start( args, format );

  wprintw( inlinescr, format, args );
  bringToFront();

  va_end(args);
}

void Frame::print( const std::vector<std::string> strings, int delayMsec ) {
  wmove( inlinescr, 0, 0 );

  if ( delayMsec > 0 ) {
    struct timespec req = {0, delayMsec * 1000000}; // 1 milli second = 1000000 micro seconds
    for ( std::string str : strings ) {
      wprintw(inlinescr, str.c_str());
      bringToFront();
      nanosleep(&req, NULL);
    }
  } else {
    for ( std::string str : strings )
      wprintw(inlinescr, str.c_str());
    bringToFront();
  }
}

void Frame::clear() {
  wclear(inlinescr);
}

void Frame::bringToFront() {
  touchwin(framescr);
  wrefresh(framescr);
}
