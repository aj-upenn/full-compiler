#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef AST_ASSEMBLER_H
#define AST_ASSEMBLER_H

typedef enum instr_kind {
    OP_INSTR_MOVQ,
    OP_INSTR_LEAQ,
    OP_INSTR_ADDQ,
    OP_INSTR_SUBQ,
    OP_INSTR_IMULQ,
    OP_INSTR_IDIVQ,
    OP_INSTR_NEGQ,
    OP_INSTR_INCQ,
    OP_INSTR_DECQ,
    OP_INSTR_CQO,
    OP_INSTR_CMPQ,
    OP_INSTR_JE,
    OP_INSTR_JNE,
    OP_INSTR_JL,
    OP_INSTR_JG,
    OP_INSTR_JLE,
    OP_INSTR_JGE,
    OP_INSTR_JMP,
    OP_INSTR_CALL,
    OP_INSTR_PUSHQ,
    OP_INSTR_POPQ,
    OP_INSTR_RET,
    OP_INSTR_NOP
} instr_kind;

typedef enum register_kind {
    OP_RAX,
    OP_RBX,
    OP_RCX,
    OP_RDX,
    OP_FIRST_FUNCTION_ARG,
    OP_SECOND_FUNCTION_ARG,
    OP_STACK_POINTER,
    OP_FRAME_POINTER,
    OP_R8,
    OP_R9,
    OP_R10,
    OP_R11,
    OP_R12,
    OP_R13,
    OP_R14,
    OP_R15
} register_kind;

typedef enum asm_line_kind {
    ASM_LINE_INSTRUCTION,
    ASM_LINE_LABEL,
    ASM_LINE_DIRECTIVE
} asm_line_kind;

typedef enum operand_kind {
    OPERAND_REGISTER,
    OPERAND_IMMEDIATE,
    OPERAND_MEMORY,
    OPERAND_LABEL
} operand_kind;

typedef enum directive_kind {
    DIR_FILE,
    DIR_SECTION,
    DIR_DATA,
    DIR_GLOBAL,
    DIR_TEXT,
    DIR_STRING,
    DIR_QUAD
} directive_kind;

typedef enum section_kind {
    SECTION_TEXT,
    SECTION_SYMTAB,
    SECTION_STRTAB,
    SECTION_SHSTRTAB,
    SECTION_RELATEXT,
    SECTION_DATA,
    SECTION_BSS,
    SECTION_GNUSTACK,
    SECTION_HEADER,
    SECTION_UNDEF
} section_kind;

struct asm_instr{
   /* used by all kinds of exprs */
   instr_kind kind;
   struct asm_operand* src;
   struct asm_operand* dest;
   uint32_t addr;
};

struct asm_directive {
    directive_kind kind;

    char* name;     // file, section, global
    char* string;   // .string
    long  value;    // .quad
};

struct asm_line {
    enum asm_line_kind kind;

    struct asm_instr *instruction;
    char *label_name;
    struct asm_directive *directive;

    struct asm_line *next;
};

struct asm_program {
    struct asm_line *lines;
    struct asm_symbol *symbols;
};

struct memory_ref {
    long offset;
    enum register_kind base;
};

struct asm_operand {
    enum operand_kind kind;

    union {
        enum register_kind reg;
        long long immediate;
        char *label;

        struct memory_ref memory;
    };
};

struct asm_symbol {
    char *name;
    long address;                  // offset within section
    enum section_kind kind;        // text or data
    bool is_global;                 // 0 or 1
    bool is_defined;
    struct asm_symbol *next;           // linked list
};

struct asm_instr* instr_create( instr_kind kind, struct asm_operand* src, struct asm_operand* dst );
struct asm_operand *operand_create_register(enum register_kind r);
struct asm_operand *operand_create_immediate(long value);
struct asm_operand *operand_create_label(char *name);
struct asm_operand *operand_create_memory(long offset, enum register_kind base);
struct asm_line* line_create( asm_line_kind kind, char *label_name, struct asm_directive* directive, struct asm_instr *instruction );
struct asm_directive* directive_create(directive_kind kind, char* name, char* string, long value);
struct asm_program* program_create(struct asm_line* line);
struct asm_symbol* asm_symbol_create(char* name, long address, section_kind kind, bool is_global, bool is_defined);


struct asm_program* program_print(struct asm_line* line);


#endif