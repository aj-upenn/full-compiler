#include "astAssembler.h"
#include <string.h>
#include <stdio.h>

struct asm_instr* instr_create( instr_kind kind, struct asm_operand* src, struct asm_operand* dest ){
   struct asm_instr* i = malloc(sizeof(*i));
   i->kind = kind;
   i->src = src;
   i->dest = dest;
   return i;
}

struct asm_operand *operand_create_register(enum register_kind r) {
    struct asm_operand *op = malloc(sizeof(*op));
    op->kind = OPERAND_REGISTER;
    op->reg = r;
    return op;
}

struct asm_operand *operand_create_immediate(long value) {
    struct asm_operand *op = malloc(sizeof(*op));
    op->kind = OPERAND_IMMEDIATE;
    op->immediate = value;
    return op;
}

struct asm_operand *operand_create_label(char *name) {
    struct asm_operand *op = malloc(sizeof(*op));
    op->kind = OPERAND_LABEL;
    op->label = name;
    return op;
}

struct asm_operand *operand_create_memory(long offset, enum register_kind base) {
    struct asm_operand *op = malloc(sizeof(*op));
    op->kind = OPERAND_MEMORY;
    op->memory.offset = offset;
    op->memory.base = base;
    return op;
}

struct asm_line* line_create( asm_line_kind kind, char *label_name, struct asm_directive* directive, struct asm_instr *instruction ){
    struct asm_line *l = malloc(sizeof(*l));
    l->kind = kind;
    l->label_name = label_name ? strdup(label_name) : 0;
    l->directive = directive;
    l->instruction = instruction;
    l->next = 0;
    return l; 
}

struct asm_directive* directive_create(directive_kind kind, char* name, char* string, long value){
    struct asm_directive* d = malloc(sizeof(*d));

    d->kind = kind;
    d->name = name ? strdup(name) : 0;
    d->string = string ? strdup(string) : 0;
    d->value = value;


    return d;
}

struct asm_program* program_create(struct asm_line* line) {
    struct asm_program* p = malloc(sizeof(*p));
    p->lines = line;
    return p;
}