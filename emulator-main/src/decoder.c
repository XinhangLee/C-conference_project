#include <decoder.h>
#include <emulator.h>

#define BITMASK(len) ((1L << (len)) - 1)
#define BITS(x, high, low) (((x) >> low) & BITMASK(high - low + 1))
#define SEXT(x, len)   \
  ({                   \
    struct {           \
      int64_t n : len; \
    } __x = {.n = x};  \
    (uint64_t) __x.n;  \
  })

#define rd decoder.rd
#define rs1 decoder.rs1
#define rs2 decoder.rs2
#define imm decoder.imm

#define src1 reg(rs1)
#define src2 reg(rs2)

#define Mr(addr, len) memory_read((addr), (len))
#define Mw(addr, len, data) memory_write((addr), (len), (data))

#define R_MASK 0b11111110000000000111000001111111
#define I_MASK 0b00000000000000000111000001111111
#define S_MASK 0b00000000000000000111000001111111
#define B_MASK 0b00000000000000000111000001111111
#define U_MASK 0b00000000000000000000000001111111
#define J_MASK 0b00000000000000000000000001111111
#define N_MASK 0b11111111111111111111111111111111

#define INSTPAT(pat, type, name, ...)    \
  if ((inst & type##_MASK) == 0b##pat) { \
    decode_##type##_inst(inst);          \
    __VA_ARGS__;                         \
    return;                              \
  }

static decoder_t decoder = {};

static void decode_R_inst(word_t inst) {
  rd = BITS(inst, 11, 7);
  rs1 = BITS(inst, 19, 15);
  rs2 = BITS(inst, 24, 20);
}

static void decode_I_inst(word_t inst) {
  rd = BITS(inst, 11, 7);
  rs1 = BITS(inst, 19, 15);
  imm = SEXT(BITS(inst, 31, 20), 12);
}

static void decode_S_inst(word_t inst) {
  rs1 = BITS(inst, 19, 15);
  rs2 = BITS(inst, 24, 20);
  imm = (SEXT(BITS(inst, 31, 25), 7) << 5) | BITS(inst, 11, 7);
}

static void decode_B_inst(word_t inst) {
  rs1 = BITS(inst, 19, 15);
  rs2 = BITS(inst, 24, 20);
  imm = (SEXT(BITS(inst, 31, 31), 1) << 12) | (BITS(inst, 30, 25) << 5) |
        (BITS(inst, 11, 8) << 1) | (BITS(inst, 7, 7) << 11);
}

static void decode_U_inst(word_t inst) {
  rd = BITS(inst, 11, 7);
  imm = SEXT(BITS(inst, 31, 12), 20) << 12;
}

static void decode_J_inst(word_t inst) {
  rd = BITS(inst, 11, 7);
  imm = (SEXT(BITS(inst, 31, 31), 1) << 20) | (BITS(inst, 30, 21) << 1) |
        (BITS(inst, 20, 20) << 11) | (BITS(inst, 19, 12) << 12);
}

static void decode_N_inst(word_t inst) {
}

void decode_exec(word_t inst) {
  // TODO
  reg(0) = 0;
  INSTPAT(00000000000000000000000000010111, U, auipc, reg(rd) = cpu.pc + imm);
  INSTPAT(00000000000000000100000000000011, I, lbu,
          reg(rd) = Mr(src1 + imm, 1));
  INSTPAT(00000000000000000000000000100011, S, sb, Mw(src1 + imm, 1, src2));

  INSTPAT(00000000000100000000000001110011, N, ebreak,
          set_emu_state(EMU_END, cpu.pc, reg(10 /* $a0 */)));  // stop running

  Assert(false, "Unknown command: %.8x at %.8x", inst, cpu.pc);
}