#ifndef __MEM_H__
#define __MEM_H__

#include <common.h>

#define MEMSIZE (1 << 20)

void memory_init(const char* img);
word_t memory_read(addr_t addr, int len);
void memory_write(addr_t addr, int len, word_t data);

#endif