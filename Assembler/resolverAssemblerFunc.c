#include "resolverAssemblerFunc.h"
#include "helper.h"
#include "codegenAssemblerFunc.h"
#include <stdio.h>
#include <string.h>

extern int yyparse();
extern int yylex_destroy();
extern FILE *yyin;
extern struct asm_program * program_pointer;
section_kind current_section;
long text_address;
long data_address;

void resolveFile()
{
    text_address = data_address = 0;
    if(yyparse() == 0){ programResolve(); fclose(yyin); yylex_destroy(); }
    else{ printf("Parse Failed!\n"); fclose(yyin); yylex_destroy(); exit(1); } 
}

void programResolve()
{
    if(!program_pointer) return;

    struct asm_line *line = program_pointer->lines;
    while(line) {
        if(line->kind == ASM_LINE_DIRECTIVE){
            directiveResolve(line->directive);
        } 
        else if(line->kind == ASM_LINE_INSTRUCTION){ 
            instructionResolve(line->instruction);
        }
        else if(line->kind == ASM_LINE_LABEL){ 
            labelResolve(line->label_name);
        }
        line = line->next;
    }
    struct asm_symbol *s = program_pointer->symbols;
    while(s)
    {
        symbolPrint(s);
        s = s->next;
    }
}

void labelResolve(char *label_name)
{
    struct asm_symbol *s =  lookupSymbol(label_name);
    if(!s)
    {
        s = insertSymbol(label_name);
    }
    else if(s->is_defined)
    {
        fprintf(stderr, "Error: duplicate definition of %s\n", label_name);
        exit(1);
    }

    s->address = (current_section == SECTION_TEXT) ? text_address : data_address;
    s->kind = current_section;
    s->is_defined = true;
}

void directiveResolve(struct asm_directive* dir)
{
    switch(dir->kind) {
        case DIR_FILE:
            break;
        case DIR_SECTION:
            break;
        case DIR_DATA:
            current_section = SECTION_DATA;
            break;
        case DIR_GLOBAL:
            struct asm_symbol *s = lookupSymbol(dir->name);
            if (!s) { s = insertSymbol(dir->name); }
            s->is_global = true;
            //printf("created symbol %s\n", dir->name);
            break;
        case DIR_QUAD:
            incrementQuadWord();
            break;
        case DIR_TEXT:
            current_section = SECTION_TEXT;
            break;
        case DIR_STRING:
            incrementString(dir->string);
            break;
        default:
            break;
    }
}

void instructionResolve(struct asm_instr* instr)
{
    // struct asm_operand *src = instr->src;
    // struct asm_operand *dst = instr->dest;

    switch(instr->kind) {
        case OP_INSTR_MOVQ:
            if (is_reg(instr->src) && is_reg(instr->dest)) {
                text_address += 3; // REX + opcode + ModR/M
            }

            else if (is_imm(instr->src) && is_reg(instr->dest)) {
                text_address += 7; // REX + opcode + ModR/M + imm32
            }

            else if (is_imm(instr->src) && is_mem(instr->dest)) {
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;
                text_address += (mod == MOD_MEM_DISP8 ? 8 : 10);
            }

            else if (is_reg(instr->src) && is_mem(instr->dest)) {
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;
                text_address += (mod == MOD_MEM_DISP8 ? 4 : 6);
            }

            else if (is_mem(instr->src) && is_reg(instr->dest)) {
                int mod  = (instr->src->memory.offset >= -128 && instr->src->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;
                text_address += (mod == MOD_MEM_DISP8 ? 4 : 6);
            }
            break;

        case OP_INSTR_LEAQ:
            text_address += 2;
            break;

        case OP_INSTR_ADDQ:
            if (is_reg(instr->src) && is_reg(instr->dest)) {
                text_address += 3; // REX + opcode + ModR/M
            }
            else if (is_imm(instr->src) && is_reg(instr->dest)) {
                if(abs((int)instr->src->immediate) >= 128) {
                    text_address += 7;
                }
                else{
                    text_address += 4;
                }
            }
            else if (is_imm(instr->src) && is_mem(instr->dest)) {
                if(abs((int)instr->src->immediate) >= 128) {
                    text_address += 8;
                }
                else{
                    text_address += 5;
                }
            }
            else if (is_reg(instr->src) && is_mem(instr->dest)) {
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;
                text_address += (mod == MOD_MEM_DISP8 ? 4 : 6);
            }
            else if (is_mem(instr->src) && is_reg(instr->dest)) {
                int mod  = (instr->src->memory.offset >= -128 && instr->src->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;
                text_address += (mod == MOD_MEM_DISP8 ? 4 : 6);
            }
            break;

        case OP_INSTR_SUBQ:
            if (is_reg(instr->src) && is_reg(instr->dest)) {
                text_address += 3; // REX + opcode + ModR/M
            }
            else if (is_imm(instr->src) && is_reg(instr->dest)) {
                if(abs((int)instr->src->immediate) >= 128) {
                    text_address += 7;
                }
                else{
                    text_address += 4;
                }
            }
            else if (is_imm(instr->src) && is_mem(instr->dest)) {
                if(abs((int)instr->src->immediate) >= 128) {
                    text_address += 8;
                }
                else{
                    text_address += 5;
                }
            }
            else if (is_reg(instr->src) && is_mem(instr->dest)) {
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;
                text_address += (mod == MOD_MEM_DISP8 ? 4 : 6);
            }
            else if (is_mem(instr->src) && is_reg(instr->dest)) {
                int mod  = (instr->src->memory.offset >= -128 && instr->src->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;
                text_address += (mod == MOD_MEM_DISP8 ? 4 : 6);
            }
            break;
            
        case OP_INSTR_CMPQ:
            if (is_imm(instr->src) && is_reg(instr->dest)) {
                text_address += 4;
            }
            else if (is_reg(instr->src) && is_reg(instr->dest)) {
                text_address += 3;
            }
            break;

        case OP_INSTR_IDIVQ:
            text_address += 3;
            break;

        case OP_INSTR_NEGQ:
            text_address += 3;
            break;

        case OP_INSTR_INCQ:
            text_address += 2;
            break;

        case OP_INSTR_DECQ:
            text_address += 2;
            break;

        case OP_INSTR_PUSHQ:
        {
            int src = registerNumber(instr->src->reg);
            if(src <= 7)
            {
                text_address += 1;
            }
            else
            {
                text_address += 2;
            }
            break;
        }
        case OP_INSTR_POPQ:
        {
            int src = registerNumber(instr->src->reg);
            if(src <= 7)
            {
                text_address += 1;
            }
            else
            {
                text_address += 2;
            }
            break;
        }
        case OP_INSTR_IMULQ:
            text_address += 3;

            break;

        case OP_INSTR_JE:
            text_address += 1;
            break;

        case OP_INSTR_JNE:
            text_address += 1;
            break;

        case OP_INSTR_JL:
            text_address += 1;
            break;

        case OP_INSTR_JG:
            text_address += 1;
            break;

        case OP_INSTR_JLE:
            text_address += 1;
            break;

        case OP_INSTR_JGE:
            text_address += 1;
            break;

        case OP_INSTR_JMP:
            text_address += 1;
            break;

        case OP_INSTR_CALL:
            text_address += 1;
            break;

        case OP_INSTR_CQO:
            text_address += 2;
            break;

        case OP_INSTR_RET:
            text_address += 1;
            break;

        default:
    }
}


void incrementQuadWord()
{
    if(current_section == SECTION_DATA) { data_address += 8; }
    else { text_address += 8;} 
}

void incrementString(char *str)
{
    int len = strlen(str) + 1;  // +1 for null
    if(current_section == SECTION_DATA) { data_address += len; }
    else { text_address += len;} 
}

struct asm_symbol *lookupSymbol(const char *name)
{
    if(!program_pointer) { return 0; }
    struct asm_symbol *asm_temp_symbol = program_pointer->symbols;
    if(!program_pointer->symbols) { return 0; }
    while(asm_temp_symbol != 0)
    {
        if(strcmp(asm_temp_symbol->name, name) == 0) {
            return asm_temp_symbol;
        }
        asm_temp_symbol = asm_temp_symbol->next;
    }
    return 0;
}

struct asm_symbol *insertSymbol(const char *name)
{
    if (!program_pointer || !name) 
        return NULL;

    struct asm_symbol *existing = lookupSymbol(name);
    if (existing != NULL)
    {
        return existing;  // Already exists, return it
    }

    struct asm_symbol *sym = asm_symbol_create((char *)name, 0, SECTION_UNDEF, false, false);

    if (program_pointer->symbols == NULL)
    {
        program_pointer->symbols = sym;
        return sym;
    }

    struct asm_symbol *cur = program_pointer->symbols;
    struct asm_symbol *prev = NULL;

    // Special case: inserting "main" → always go to end
    if (strcmp(name, "main") == 0)
    {
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = sym;
        return sym;
    }

    // Otherwise: insert BEFORE "main" if it exists
    while (cur != NULL)
    {
        if (strcmp(cur->name, "main") == 0)
        {
            // Insert before "main"
            if (prev == NULL)
            {
                // "main" is first node
                sym->next = program_pointer->symbols;
                program_pointer->symbols = sym;
            }
            else
            {
                prev->next = sym;
                sym->next = cur;
            }
            return sym;
        }

        prev = cur;
        cur = cur->next;
    }

    // If "main" not found → append normally
    prev->next = sym;

    return sym;
}

void symbolPrint(struct asm_symbol *sym) 
{
    if (!sym) {
        printf("NULL symbol\n");
        return;
    }

    const char *section_str;

    switch (sym->kind) {
        case SECTION_TEXT:
            section_str = ".text";
            break;
        case SECTION_DATA:
            section_str = ".data";
            break;
        default:
            section_str = "UNDEF";
            break;
    }

    printf("Symbol: %-15s | "
           "Addr: %-6ld | "
           "Section: %-6s | "
           "Global: %-3s | "
           "Defined: %-3s\n",
           sym->name,
           sym->address,
           section_str,
           sym->is_global ? "yes" : "no",
           sym->is_defined ? "yes" : "no");
}
