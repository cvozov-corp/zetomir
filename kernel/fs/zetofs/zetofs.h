#ifndef ZETOMIR_ZETOFS_H
#define ZETOMIR_ZETOFS_H
#include "../../types.h"
typedef struct znode znode_t;
void zetofs_init(void);
znode_t *zetofs_create(const char *name, int is_dir);
int zetofs_write(znode_t *f, const char *buf, usize len);
int zetofs_read(znode_t *f, char *buf, usize max);
znode_t *zetofs_root(void);
#endif
EOF