#ifndef ZETOMIR_VFS_H
#define ZETOMIR_VFS_H
#include "../types.h"
void vfs_init(void);
int vfs_ls(char *out, int max);
int vfs_read(const char *name, char *out, int max);
#endif
