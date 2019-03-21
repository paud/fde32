#pragma once
#include <vcruntime.h>
#include <malloc.h>

typedef struct cs_insn {
  // Instruction ID (basically a numeric ID for the instruction mnemonic)
  // Find the instruction id in the '[ARCH]_insn' enum in the header file 
  // of corresponding architecture, such as 'arm_insn' in arm.h for ARM,
  // 'x86_insn' in x86.h for X86, etc...
  // This information is available even when CS_OPT_DETAIL = CS_OPT_OFF
  // NOTE: in Skipdata mode, "data" instruction has 0 for this id field.
  unsigned int id;

  // Address (EIP) of this instruction
  // This information is available even when CS_OPT_DETAIL = CS_OPT_OFF
  size_t address;

  // Size of this instruction
  // This information is available even when CS_OPT_DETAIL = CS_OPT_OFF
  int size;
  // Machine bytes of this instruction, with number of bytes indicated by @size above
  // This information is available even when CS_OPT_DETAIL = CS_OPT_OFF
  char bytes[16];

  // Ascii text of instruction mnemonic
  // This information is available even when CS_OPT_DETAIL = CS_OPT_OFF
  char mnemonic[32];

  // Ascii text of instruction operands
  // This information is available even when CS_OPT_DETAIL = CS_OPT_OFF
  char op_str[160];

  // Pointer to cs_detail.
  // NOTE: detail pointer is only valid when both requirements below are met:
  // (1) CS_OP_DETAIL = CS_OPT_ON
  // (2) Engine is not in Skipdata mode (CS_OP_SKIPDATA option set to CS_OPT_ON)
  //
  // NOTE 2: when in Skipdata mode, or when detail mode is OFF, even if this pointer
  //     is not NULL, its content is still irrelevant.
  size_t *detail;
} cs_insn;


size_t cs_disasm(size_t handle,
  const size_t *code, size_t code_size,
  size_t address,
  size_t count,
  cs_insn **insn);

size_t cs_open(size_t arch, size_t mode, size_t *handle);
