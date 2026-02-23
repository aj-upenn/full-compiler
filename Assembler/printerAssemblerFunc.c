#include "printerAssemblerFunc.h"
#include <stdio.h>

extern int yyparse();
extern int yylex_destroy();
extern FILE *yyin;
struct asm_program * program_pointer;

void printFile() {
    if(yyparse() == 0){ programPrint(program_pointer); fclose(yyin); yylex_destroy(); }
    else{ printf("Parse Failed!\n"); fclose(yyin); yylex_destroy(); exit(1); } 
}

void programPrint(struct asm_program* program)
{
    if(!program) return;
    struct asm_line *line = program->lines;
    while(line) {
        if(line->kind == ASM_LINE_DIRECTIVE){
            directivePrint(line->directive);
        } 
        else if(line->kind == ASM_LINE_INSTRUCTION){ 
            instructionPrint(line->instruction);
        }
        else if(line->kind == ASM_LINE_LABEL){ 
            printf("%s:\n", line->label_name);
        }
        line = line->next;
    }
}

void directivePrint(struct asm_directive* dir){
    switch(dir->kind) {
        case DIR_FILE:
            printf(".file \"%s\"\n", dir->name);
            break;
        case DIR_SECTION:
            if(dir->string) printf(".section .note.GNU-stack,\"%s\",@progbits\n", dir->string);
            else { printf(".section .note.GNU-stack,\"\",@progbits\n");}
            break;
        case DIR_DATA:
            printf(".data\n");
            break;
        case DIR_GLOBAL:
            indentLine(3);
            printf(".global %s\n", dir->name);
            break;
        case DIR_QUAD:
            indentLine(3);
            printf(".quad %ld\n", dir->value);
            break;
        case DIR_TEXT:
            printf(".text\n");
            break;
        case DIR_STRING:
            indentLine(3);
            printf(".string \"%s\"\n", dir->string);
            break;
        default:
            break;
    }
}

void registerPrint(register_kind reg)
{
    switch(reg) {
        case OP_RAX:  printf("%%rax"); break;
        case OP_RBX:  printf("%%rbx"); break;
        case OP_RCX:  printf("%%rcx"); break;
        case OP_RDX:  printf("%%rdx"); break;
        case OP_FIRST_FUNCTION_ARG:  printf("%%rdi"); break;
        case OP_SECOND_FUNCTION_ARG: printf("%%rsi"); break;
        case OP_STACK_POINTER:  printf("%%rsp"); break;
        case OP_FRAME_POINTER:  printf("%%rbp"); break;
        case OP_R8:  printf("%%r8");  break;
        case OP_R9:  printf("%%r9");  break;
        case OP_R10: printf("%%r10"); break;
        case OP_R11: printf("%%r11"); break;
        case OP_R12: printf("%%r12"); break;
        case OP_R13: printf("%%r13"); break;
        case OP_R14: printf("%%r14"); break;
        case OP_R15: printf("%%r15"); break;
        default: break;
    }
}

void memoryPrint(struct memory_ref memory)
{
    if(memory.offset) { printf("%ld(", memory.offset); }
    else { printf("(");}
    registerPrint(memory.base);
    printf(")");
}

void operandPrint(struct asm_operand* operand)
{
    switch(operand->kind){
        case OPERAND_REGISTER:
            registerPrint(operand->reg);
            break;
        case OPERAND_IMMEDIATE:
            printf("$%ld", operand->immediate);
            break;
        case OPERAND_MEMORY:
            memoryPrint(operand->memory);
            break;
        case OPERAND_LABEL:
            printf("%s", operand->label);
            break;
        default:
            break;
    }

}

void twoOpPrint(struct asm_operand* src, struct asm_operand* dest)
{
    operandPrint(src);
    printf(", ");
    operandPrint(dest);
    printf("\n");
}

void instructionPrint(struct asm_instr* instr){
    switch(instr->kind) {
        case OP_INSTR_MOVQ:
            indentLine(3);
            printf("MOVQ ");
            twoOpPrint(instr->src, instr->dest);
            break;
        case OP_INSTR_LEAQ:
            indentLine(3);
            printf("LEAQ ");
            twoOpPrint(instr->src, instr->dest);
            break;
        case OP_INSTR_ADDQ:
            indentLine(3);
            printf("ADDQ ");
            twoOpPrint(instr->src, instr->dest);
            break;
        case OP_INSTR_SUBQ:
            indentLine(3);
            printf("SUBQ ");
            twoOpPrint(instr->src, instr->dest);
            break;
        case OP_INSTR_CMPQ:
            indentLine(3);
            printf("CMPQ ");
            twoOpPrint(instr->src, instr->dest);
            break;

        case OP_INSTR_IDIVQ:
            indentLine(3);
            printf("IDIVQ ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_NEGQ:
            indentLine(3);
            printf("NEGQ ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_INCQ:
            indentLine(3);
            printf("INCQ ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_DECQ:
            indentLine(3);
            printf("DECQ ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_PUSHQ:
            indentLine(3);
            printf("PUSHQ ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_POPQ:
            indentLine(3);
            printf("POPQ ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_IMULQ:
            indentLine(3);
            printf("IMULQ ");
            operandPrint(instr->src);
            printf("\n");
            break;

        case OP_INSTR_JE:
            indentLine(3);
            printf("JE ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_JNE:
            indentLine(3);
            printf("JNE ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_JL:
            indentLine(3);
            printf("JL ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_JG:
            indentLine(3);
            printf("JG ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_JLE:
            indentLine(3);
            printf("JLE ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_JGE:
            indentLine(3);
            printf("JGE ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_JMP:
            indentLine(3);
            printf("JMP ");
            operandPrint(instr->src);
            printf("\n");
            break;
        case OP_INSTR_CALL:
            indentLine(3);
            printf("CALL ");
            operandPrint(instr->src);
            printf("\n");
            break;

        case OP_INSTR_CQO:
            indentLine(3);
            printf("CQO\n");
            break;

        case OP_INSTR_RET:
            indentLine(3);
            printf("RET\n");
            break;

        default:
            break;
    }
}

void indentLine(int indent){
   int i = 0;
   for(i = 0; i < indent; i++){ printf(" "); }
}
