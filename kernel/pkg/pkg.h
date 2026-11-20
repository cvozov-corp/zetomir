#ifndef ZETOMIR_PKG_H
#define ZETOMIR_PKG_H
#include "../../types.h"
void pkg_init(void);
int pkg_install(const char *name);
int pkg_remove(const char *name);
void pkg_list(void);
#endif
EOF