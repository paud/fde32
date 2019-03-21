#include "capstoneCompatible.h"
#ifdef _M_X64
#include "fde64.h"
#else
#include "fde32.h"
#endif 

size_t cs_disasm(size_t handle,
  size_t *code, size_t code_size,
  size_t address,
  size_t count,
  cs_insn **insn) {
#ifdef _M_X64
  struct fde64s cmd;
#else
  struct fde32s cmd;
#endif 
  int i = 0;
  int l = 0;
  cs_insn* ins;
  *insn = malloc(sizeof(cs_insn)*code_size);
  while (l < code_size) {
    decode(code, &cmd);
    l += cmd.len;
    code = (size_t)code+ (size_t)cmd.len;
    ins = *insn;
    ins[i].size=cmd.len;
    ++i;
  
  }

}

size_t cs_open(size_t arch, size_t mode, size_t *handle) {
  return 0;
}
