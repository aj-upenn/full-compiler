#include "helper.h"

int is_reg(struct asm_operand *op) {
    return op && op->kind == OPERAND_REGISTER;
}

int is_imm(struct asm_operand *op) {
    return op && op->kind == OPERAND_IMMEDIATE;
}
int is_mem(struct asm_operand *op) {
    return op && op->kind == OPERAND_MEMORY;
}

int is_label(struct asm_operand *op) {
    return op && op->kind == OPERAND_LABEL;
}