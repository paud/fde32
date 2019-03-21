#include <stdio.h>
#include "capstoneCompatible.h"

#ifdef _M_X64
#include "fde64.h"
#else
#include "fde32.h"
#endif 

int main(void)
{
	const void *ptr = (const void *)&main;
#ifdef _M_X64
  struct fde64s cmd;
#else
  struct fde32s cmd;
#endif 
  cs_insn *insn;
  cs_disasm(0, ptr, 30, 0, 0, &insn);
  int l=0;
  int i = 0;
  while (l < 20) {
    l += insn[i].size;
    ++i;
  }

	for (;;) {
		decode(ptr, &cmd);
		ptr = (const void *)((uintptr_t)ptr + cmd.len);
		printf("opcode: ");
		switch (cmd.opcode_len) {
		case 1:
			printf("%02X", cmd.opcode);
			break;
		case 2:
			printf("%02X %02X", cmd.opcode, cmd.opcode2);
			break;
		case 3:
			printf("%02X %02X %02X", cmd.opcode, cmd.opcode2, cmd.opcode3);
			break;
		}
		printf(" full instruction-length: %d\n", cmd.len);
		if (getchar() == 'q')
			break;
	}
	return 0;
}
