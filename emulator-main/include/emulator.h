#ifndef __EMULATOR_H__
#define __EMULATOR_H__

#include <common.h>
#include <cpu.h>
#include <mem.h>
#include <decoder.h>

struct EmuState {
  int state;
  addr_t halt_pc;
  int halt_ret;
};

extern struct EmuState emu;

enum {
  EMU_RUNNING,
  EMU_END,
  EMU_ABORT,
};

void emulator_init(const char* img);
void emulator_run();
void set_emu_state(int state, addr_t halt_pc, int halt_ret);
bool is_exit_status_bad();

#endif