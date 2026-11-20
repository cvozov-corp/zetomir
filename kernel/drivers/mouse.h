#ifndef ZETOMIR_MOUSE_H
#define ZETOMIR_MOUSE_H
#include "../types.h"
void mouse_init(void);
int mouse_read(int *dx, int *dy, int *buttons);
#endif
