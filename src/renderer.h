#ifndef H_RENDERER
#define H_RENDERER

typedef struct {
  char frame_tr[20];
  char frame_tl[20];
  char frame_br[20];
  char frame_bl[20];
  char frame_h[20];
  char frame_v[20];
} UIDescriptor;

typedef struct {
  int row;
  int column;
} TermEnv;

TermEnv getTermEnv();
void renderFrame(int);

#endif
