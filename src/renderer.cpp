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
  struct timespec req = {0, msec * MILLI_SEC};
  for ( std::string str : strings ) {
    printw(str.c_str());
    refresh();
    nanosleep(&req, NULL);
  }
}

// Frame class
Frame::Frame(int row) {
  this->row = row;

  // DEF: WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
  framescr = newwin(row+2, COLS, LINES - row - 2, 0);
  frameX = COLS;
  frameY = row+2;

  render();

  inlinescr = subwin(framescr, row, COLS-4, LINES - row - 1, 2);
  wrefresh(framescr);
}

int Frame::getRow() {
  return this->row;
}

void Frame::applyUIDescriptor(char *tr, char *tl, char *br, char *bl, char *h, char *v) {
  strcpy(uiDescriptor.frame_tr, tr);
  strcpy(uiDescriptor.frame_tl, tl);
  strcpy(uiDescriptor.frame_br, br);
  strcpy(uiDescriptor.frame_bl, bl);
  strcpy(uiDescriptor.frame_h, h);
  strcpy(uiDescriptor.frame_v, v);
}

void Frame::render() {
  wmove(framescr, 0, 0);

  for ( int i=0; i < frameY; i++ ) {
    if ( i == 0 ) {
      wprintw(framescr, "%s", uiDescriptor.frame_tl);
      for ( int j=0; j < frameX - 2; j++) {
        wprintw(framescr, "%s", uiDescriptor.frame_h);
      }
      wprintw(framescr, "%s", uiDescriptor.frame_tr);
    } else if ( i == frameY - 1 ) {
      wprintw(framescr, "%s", uiDescriptor.frame_bl);
      for ( int j=0; j < frameX - 2; j++) {
        wprintw(framescr, "%s", uiDescriptor.frame_h);
      }
      wprintw(framescr, "%s", uiDescriptor.frame_br);
    } else {
      wprintw(framescr, "%s", uiDescriptor.frame_v);
      for ( int j=0; j < frameX - 2; j++) {
        // wmove(framescr, i, j+2);
        wprintw(framescr, " ");
      }
      wprintw(framescr, "%s", uiDescriptor.frame_v);
    }
  }
}

void Frame::print( const char* format, ... ) {
  va_list args;
  va_start( args, format );

  wprintw( inlinescr, format, args );
  touchwin(framescr);
  wrefresh(framescr);

  va_end(args);
}

void Frame::iprint( int msec, std::vector<std::string> strings) {
  struct timespec req = {0, 300 * MILLI_SEC};
  for ( std::string str : strings ) {
    wprintw(inlinescr, str.c_str());
    touchwin(framescr);
    wrefresh(framescr);
    nanosleep(&req, NULL);
  }
}

void Frame::clear() {
  wclear(inlinescr);
}

void Frame::bringToFront() {
  touchwin(framescr);
  wrefresh(framescr);
}
