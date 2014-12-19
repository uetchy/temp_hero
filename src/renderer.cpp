#include "renderer.hpp"

const int RFOrientation::TOP    = 0;
const int RFOrientation::BOTTOM = 1;

// Stdscr syntax sugar
void print( const std::vector<std::string> strings, int delayMsec ) {
  move(0, 0);

  if ( delayMsec > 0 ) {
    struct timespec req = {0, delayMsec * 1000000}; // 1 milli second = 1000000 micro seconds
    for ( std::string str : strings ) {
      printw(str.c_str());
      nanosleep(&req, NULL);
    }
  } else {
    for ( std::string str : strings )
      printw(str.c_str());
  }
}

void filledWith(const char* str) {
  move(0, 0);
  for (int x=0; x < COLS; x++)
    for (int y=0; y < LINES; y++)
      mvprintw(y, x, str);
}

std::vector<std::string> centerizedStrings(std::vector<std::string> strings) {
  int width = 0;
  for (std::string str : strings) {
    if (str.length() > width) {
      width = str.length();
    }
  }

  int leftMargin = (COLS - width) / 2;
  std::string leftMarginStr = "";
  for (int i=0; i<leftMargin; i++) {
    leftMarginStr.append(" ");
  }
  std::vector<std::string> result;

  for (std::string str : strings) {
    result.push_back(leftMarginStr+str);
  }

  return result;
}

std::string seqStr(int width, std::string start, std::string mid, std::string end) {
  std::string res;
  res += start;
  for (int i=0; i<width-2; i++) {
    res += mid;
  }
  res += end;
  return res;
}

// Frame class
Frame::Frame(int inline_row, int orientation) {
  // Define frame val
  this->frameInfo.row  = inline_row + 2;
  this->frameInfo.cols = COLS;
  this->orientation = orientation;

  switch(orientation) {
    case RFOrientation::TOP:
      this->frameInfo.absoluteX = 0;
      this->frameInfo.absoluteY = 0;
      break;
    case RFOrientation::BOTTOM:
      this->frameInfo.absoluteX = 0;
      this->frameInfo.absoluteY = LINES - this->frameInfo.row;
      break;
  }

  // Create frame
  // DEF: WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
  framescr = newwin(
    this->frameInfo.row,
    this->frameInfo.cols,
    this->frameInfo.absoluteY,
    this->frameInfo.absoluteX
  );

  // Define inline frame val
  this->inlineFrameInfo.absoluteX = this->frameInfo.absoluteX + 2;
  this->inlineFrameInfo.absoluteY = this->frameInfo.absoluteY + 1;
  this->inlineFrameInfo.row       = inline_row;
  this->inlineFrameInfo.cols      = COLS - 4;
  renderBorder();

  // Create inline frame
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

void Frame::destroy() {
  delwin(inlinescr);
  delwin(framescr);
}

WINDOW* Frame::getView() {
  return inlinescr;
}

int Frame::cols() { return this->inlineFrameInfo.cols; }
int Frame::lines() { return this->inlineFrameInfo.row; }

int Frame::getRow() { return this->frameInfo.row; }
int Frame::getCols() { return this->frameInfo.cols; }
int Frame::getIrow() { return this->inlineFrameInfo.row; }
int Frame::getIcols() { return this->inlineFrameInfo.cols; }

void Frame::filledWith(const char* str) {
  wmove(inlinescr, 0, 0);
  for (int x=0; x < getIcols(); x++)
    for (int y=0; y < getIrow(); y++)
      mvwprintw(inlinescr, y, x, str);
  update();
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
  update();

  va_end(args);
}

void Frame::print( const std::vector<std::string> strings, int delayMsec ) {
  wmove( inlinescr, 0, 0 );

  if ( delayMsec > 0 ) {
    struct timespec req = {0, delayMsec * 1000000}; // 1 milli second = 1000000 micro seconds
    for ( std::string str : strings ) {
      wprintw(inlinescr, str.c_str());
      update();
      nanosleep(&req, NULL);
    }
  } else {
    for ( std::string str : strings )
      wprintw(inlinescr, str.c_str());
    update();
  }
}

void Frame::clear() {
  wclear(inlinescr);
  wmove(inlinescr, 0, 0);
}

void Frame::update() {
  touchwin(framescr);
  wrefresh(framescr);
}
