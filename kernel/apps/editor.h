#ifndef ZETOMIR_EDITOR_H
#define ZETOMIR_EDITOR_H
#include "../../types.h"
void editor_init(void);
void editor_open(const char *name);
void editor_insert(char c);
void editor_save(const char *name);
#endif
EOF