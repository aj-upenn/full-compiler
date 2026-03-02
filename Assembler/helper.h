#include "astAssembler.h"

int is_reg(struct asm_operand *op);
int is_imm(struct asm_operand *op);
int is_mem(struct asm_operand *op);
int is_label(struct asm_operand *op);