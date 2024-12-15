#include <cpu.h>
#include <emulator.h>

struct CPU cpu = {};

void cpu_init() {
  cpu.pc = 0x80000000;
}

void execute(uint64_t n) {
  while (n--) {
    word_t inst = memory_read(cpu.pc, 4);
    decode_exec(inst);
    if (emu.state != EMU_RUNNING) break;
    cpu.pc += 4;
  }
}