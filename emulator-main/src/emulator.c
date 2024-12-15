#include <emulator.h>

struct EmuState emu = {};

void emulator_init(const char* img) {
  cpu_init();
  memory_init(img);
}

void emulator_run() {
  emu.state = EMU_RUNNING;
  execute(-1);
  switch (emu.state) {
    case EMU_END:
      printf("\033[1;32mPASS!!! at %.8x\033[0m\n", emu.halt_pc);
      break;
    default:
      break;
  }
}

void set_emu_state(int state, addr_t halt_pc, int halt_ret) {
  emu.state = state;
  emu.halt_pc = halt_pc;
  emu.halt_ret = halt_ret;
}

bool is_exit_status_bad() {
  return emu.state == EMU_ABORT || (emu.state == EMU_END && emu.halt_ret != 0);
}