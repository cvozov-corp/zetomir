#include "zetofs.h"
#include "../../types.h"
#include "../../mm/heap.h"

typedef struct znode {
    char name[32];
    int is_dir;
    char *data;
    usize size, cap;
    struct znode *parent;
    struct znode *children[16];
    int nchildren;
} znode_t;

static znode_t *root;

znode_t *zetofs_create(const char *name, int is_dir) {
    znode_t *n = kmalloc(sizeof(znode_t));
    int i=0; while (name[i] && i<31) { n->name[i]=name[i]; i++; } n->name[i]=0;
    n->is_dir=is_dir; n->data=NULL; n->size=0; n->cap=0; n->parent=NULL; n->nchildren=0;
    return n;
}

void zetofs_init(void) {
    root = zetofs_create("/", 1);
}

int zetofs_write(znode_t *f, const char *buf, usize len) {
    if (f->is_dir) return -1;
    if (f->cap < len) {
        usize newcap = len + 64;
        char *nd = kmalloc(newcap);
        if (f->data) { for (usize i=0;i<f->size;i++) nd[i]=f->data[i]; }
        f->data = nd; f->cap = newcap;
    }
    for (usize i=0;i<len;i++) f->data[i]=buf[i];
    f->size = len;
    return (int)len;
}

int zetofs_read(znode_t *f, char *buf, usize max) {
    if (f->is_dir || !f->data) return 0;
    usize n = f->size < max ? f->size : max;
    for (usize i=0;i<n;i++) buf[i]=f->data[i];
    return (int)n;
}

znode_t *zetofs_root(void) { return root; }
EOF