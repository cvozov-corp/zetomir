#ifndef ZETOMIR_COMPOSITOR_H
#define ZETOMIR_COMPOSITOR_H
#include "../../types.h"
void compositor_init(void);
int compositor_create_window(int x, int y, int w, int h, u32 bg);
void compositor_paint(void);
void compositor_move(int id, int x, int y);
#endif
EOF