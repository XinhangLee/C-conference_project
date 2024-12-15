#ifndef __CPU_H__
#define __CPU_H__

#include <common.h>

struct CPU {
  addr_t pc;
  word_t regs[32];
};

extern struct CPU cpu;

#define reg(i) cpu.regs[i]

void cpu_init();
void execute(uint64_t n);

#endif