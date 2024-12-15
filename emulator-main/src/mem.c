#include <mem.h>
#include <emulator.h>

#define MEM_BASE 0x80000000
#define MEM_ADDR(addr) ((addr) - MEM_BASE)

static byte memory[MEMSIZE];

#define in_mem(addr) (MEM_BASE <= (addr) && (addr) < MEM_BASE + MEMSIZE)

void memory_init(const char* img) {
  if (!img) {
    word_t dummy = 0b00000000000100000000000001110011;
    memcpy(memory, &dummy, sizeof(dummy));
    return;
  }
  FILE* fp = fopen(img, "rb");
  assert(fp);
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  assert(fread(memory, size, 1, fp));
  fclose(fp);
}

word_t memory_read(addr_t addr, int len) {
  Assert(in_mem(addr), "addr = %.8x is out of bound");
  byte* mem = memory + MEM_ADDR(addr);
  switch (len) {
    case 1:
      return *mem;
    case 2:
      return *(uint16_t*)mem;
    case 4:
      return *(word_t*)mem;
    default:
      Assert(false, "len must in {1, 2, 4}");
  }
}

void memory_write(addr_t addr, int len, word_t data) {
  Assert(in_mem(addr), "addr = %.8x is out of bound");
  byte* mem = memory + MEM_ADDR(addr);
  switch (len) {
    case 1:
      *mem = (byte)data;
      break;
    case 2:
      *(uint16_t*)mem = (uint16_t)data;
      break;
    case 4:
      *(word_t*)mem = data;
      break;
    default:
      Assert(false, "len must in {1, 2, 4}");
  }
}