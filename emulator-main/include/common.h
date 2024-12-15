#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

typedef uint8_t byte;
typedef uint32_t word_t;
typedef uint32_t addr_t;

#define Assert(cond, fmt, ...)                             \
  do {                                                     \
    if (!(cond)) {                                         \
      printf("\033[1;31m" fmt "\033[0m\n", ##__VA_ARGS__); \
      set_emu_state(EMU_ABORT, cpu.pc, 1);                 \
    }                                                      \
  } while (0)

#endif