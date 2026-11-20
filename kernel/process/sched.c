#include "sched.h"
#include "../../types.h"
#include "../../mm/heap.h"

typedef struct task {
    u64 rsp;
    int state;
    struct task *next;
} task_t;

static task_t *current = NULL;
static task_t *ready = NULL;

void sched_init(void) {
    current = kmalloc(sizeof(task_t));
    current->rsp = 0; current->state = 1; current->next = current;
    ready = current;
}

void sched_add(task_t *t) {
    t->state = 1;
    t->next = ready->next;
    ready->next = t;
}

void sched_tick(void) {
    if (!current) return;
    task_t *next = current->next;
    if (next && next != current) {
        /* context switch (simplified) */
        current = next;
    }
}
EOF