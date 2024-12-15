#ifndef __DECODER_H__
#define __DECODER_H__

#include <common.h>

typedef struct InstDecoder {
  word_t imm;
  uint8_t rd, rs1, rs2;
} decoder_t;

void decode_exec(word_t inst);

#endif