#include "astAssembler.h"

void printFile();
void indentLine(int indent);
void programPrint( struct asm_program* program);
void directivePrint(struct asm_directive* line);
void instructionPrint(struct asm_instr* instr);
void operandPrint(struct asm_operand* operand);
void twoOpPrint(struct asm_operand* src, struct asm_operand* dest);
void registerPrint(register_kind reg);
void memoryPrint(struct memory_ref memory);