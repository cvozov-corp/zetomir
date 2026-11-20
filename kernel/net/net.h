#ifndef ZETOMIR_NET_H
#define ZETOMIR_NET_H
#include "../../types.h"
void net_init(void);
int net_send(const void *buf, usize len);
void net_poll(void);
#endif
EOF