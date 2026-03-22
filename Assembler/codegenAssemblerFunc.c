#include "codegenAssemblerFunc.h"
#include "printerAssemblerFunc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern struct asm_program * program_pointer;
//extern section_kind current_section;
//extern long text_address = 0;
const unsigned int CURRENT_STRTAB_LEN = 24;

void codeGen() {
    struct binary_section *header = binarySectionCreate(64, SECTION_HEADER);
    setHeader(header, 0);  // FIX

    struct binary_section *instructions = binarySectionCreate(text_address, SECTION_TEXT);
    setInstructions(instructions);

    FILE *fp = fopen("output.o", "wb");
    if (!fp) {
        perror("fopen");
        return;
    }
    
    int shstrtab_length = 64;

    struct binary_section *strtab = binarySectionCreate(CURRENT_STRTAB_LEN, SECTION_SHSTRTAB);
    setStrtab(strtab);

    struct binary_section *shstrtab = binarySectionCreate(shstrtab_length, SECTION_SHSTRTAB);
    setShstrtab(shstrtab);

    struct binary_section *symtab = binarySectionCreate(20000, SECTION_SYMTAB); // UPDATE AT END
    setSymTab(symtab);

    struct binary_section *data = binarySectionCreate(3*sizeof(struct binary_symbol), SECTION_DATA); // UPDATE AT END
    setData(data);

    //struct binary_section *bss = binarySectionCreate(64, SECTION_BSS); // UPDATE AT END
    

    writeBinary(fp, header);
    writeBinary(fp, instructions);
    writeBinary(fp, data);
    writeBinary(fp, strtab);
    //writeBinary(fp, symtab);
    //writeBinary(fp, shstrtab);

    fclose(fp);
}

void emitSymbol(struct binary_section *s, struct binary_symbol * symb)
{
    emit4(s, symb->st_name);
    emitbyte(s, symb->st_info);
    emitbyte(s, symb->st_other);
    emit2(s, symb->st_shndx);
    emit8(s, symb->st_value);
    emit8(s, symb->st_size);
}

void setStrtab(struct binary_section *s)
{
    char tab[CURRENT_STRTAB_LEN];
    int location = 0;
    tab[location++] = 0;
    strcpy(&tab[1], program_pointer->lines->directive->name);
    location += strlen(program_pointer->lines->directive->name) + 1;
    for(unsigned int i = 0; i < CURRENT_STRTAB_LEN; i++)
    {
        emitbyte(s, tab[i+1]);
    }

    struct asm_symbol * symb = program_pointer->symbols;
    //emitbyte(s, tab[location++]);
}

void setData(struct binary_section *s)
{
    struct binary_symbol* first =  createBinarySymbol(0,0,0,0,0,0);
    emitSymbol(s, first);
    
    struct binary_symbol* b =  createBinarySymbol(1,0x04,0,0xfff1,0,0);
    emitSymbol(s, b);

    struct asm_symbol * symb = program_pointer->symbols;

    uint32_t strtab_index = 1; // starts at 1 (first byte is a 0)

    strtab_index += strlen(program_pointer->lines->directive->name) + 1;

    while(symb != 0)
    {
        
        // b =  createBinarySymbol(20/*strtab_index*/,0x1000,0x0100,0,0,0);
        b =  createBinarySymbol(strtab_index,0x10,0,0x01,0,0);
        emitSymbol(s, b);
        symb = symb->next;
    }
}

void setShstrtab(struct binary_section *s)
{
    char * sections_string = "\0symtab\0strtab\0shstrtab\0rela.text\0data\0bss\0note.GNU-stack";
    for(size_t i = 0; i < 58; i++)
    {
        emitbyte(s, sections_string[i]);
        if(sections_string[i] == '\0') {
            emitbyte(s, 0x2e);
        }
    }
}

void setSymTab(struct binary_section *s)
{
    if(!program_pointer) return;
    s->size = 0;
    struct asm_symbol * symb = program_pointer->symbols;
    while(symb != 0)
    {
        int length = strlen(symb->name);
        for(int i = 0; i < length; i++)
        {
            emitbyte(s, symb->name[i]);
            s->size++;
        }
        emitbyte(s, 0);
        s->size++;
        symb = symb->next;
    }

    symb = program_pointer->symbols;
    while(symb != 0)
    {
        emit4(s, symb->address);
        symb = symb->next;
        s->size+=4;
    }

    /*
    struct asm_line *line = program_pointer->lines;
    while(line) {
        if(line->kind == ASM_LINE_LABEL){
            int length = strlen(line->label_name);
            for(int i = 0; i < length; i++)
            {
                emitbyte(s, line->label_name[i]);
                s->size++;
            }
            emitbyte(s, 0);
            s->size++;
        }
        else if(line->kind == ASM_LINE_DIRECTIVE && line->directive != 0 && line->directive->kind == DIR_FILE) 
        {
            int length = strlen(line->directive->name);
            for(int i = 0; i < length; i++)
            {
                emitbyte(s, line->directive->name[i]);
                s->size++;
            }
            emitbyte(s, 0);
            s->size++;
            
        }
        else {

        }
        line = line->next;
    }
    */
}


void padto16(struct binary_section *s)
{
    while(s->size % 16 != 0)
    {
        emitbyte(s, 0);
        s->size += 1;
    }
}


struct binary_symbol* createBinarySymbol(uint32_t st_name, uint8_t  st_info, uint8_t  st_other, uint16_t st_shndx, uint64_t st_value, uint64_t st_size)
{
    struct binary_symbol* sym = (struct binary_symbol*) malloc(sizeof(struct binary_symbol));
    if (!sym) return NULL;

    sym->st_name  = st_name;
    sym->st_info  = st_info;
    sym->st_other = st_other;
    sym->st_shndx = st_shndx;
    sym->st_value = st_value;
    sym->st_size  = st_size;

    return sym;
}

void setInstructions(struct binary_section *s)
{
    if(!program_pointer) return;

    struct asm_line *line = program_pointer->lines;
    while(line) {
        if(line->kind == ASM_LINE_INSTRUCTION){
            struct op_code* aOpCode = instructionOpCode(line->instruction);
            if(!aOpCode) { printf("Skipping instruction\n"); }
            if(aOpCode->size_bytes <= 8) {
                uint64_t mask = 0xff;
                for(size_t i = 0; i < aOpCode->size_bytes; i++)
                {
                    uint8_t byte = (mask & aOpCode->data) >> 8*i;
                    emitbyte(s, byte);
                    mask = mask << 8;
                }
            }
            else {

            }
        }
        line = line->next;
    }
    padto16(s);
}

void setHeader(struct binary_section *s, uint64_t offset_to_header)
{
    emitbyte(s, 0x7F); emitbyte(s, 0x45); emitbyte(s, 0x4C); emitbyte(s, 0x46); // Header
    emitbyte(s, 0x02); // 64 bit processor
    emitbyte(s, 0x01); // Endian type (1 = little)
    emitbyte(s, 0x01); // Elf Version
    emitbyte(s, 0x00); emitbyte(s, 0x00); // ABI INFO
    for(int i = 0; i < 7; i ++) { emitbyte(s, 0x00); } // 0 padding 
    emitbyte(s, 0x01); emitbyte(s, 0x00); // .o File
    emitbyte(s, 0x3E); emitbyte(s, 0x00); // Little Endian
    emitbyte(s, 0x01); emitbyte(s, 0x00); emitbyte(s, 0x00); emitbyte(s, 0x00); // Elf version
    for(int i = 0; i < 8; i ++) { emitbyte(s, 0x00); } // program headers none for .o
    for(int i = 0; i < 8; i ++) { emitbyte(s, 0x00); } // file offset where your section header table begins, filled in linker?
    emit8(s, offset_to_header);
    emitbyte(s, 0x00); emitbyte(s, 0x00); emitbyte(s, 0x00); emitbyte(s, 0x00); // x86-arch
    emitbyte(s, 0x40); emitbyte(s, 0x00);  // header size (64)
    emitbyte(s, 0x00); emitbyte(s, 0x00); emitbyte(s, 0x00); emitbyte(s, 0x00); // size of program header entries
    emitbyte(s, 0x40); emitbyte(s, 0x00);  // section entry header size (64)
    emitbyte(s, 0x90); emitbyte(s, 0x00); // number of sections
    emitbyte(s, 0x80); emitbyte(s, 0x00); // which section has header names
}

void emitbyte(struct binary_section *s, char byte)
{
    s->bytes[s->section_offset] = byte;
    s->section_offset++;
}

void emit2(struct binary_section *s, uint64_t value)
{
    for (int i = 0; i < 2; i++) {
        emitbyte(s, (value >> (8 * i)) & 0xFF);
    }
}

void emit4(struct binary_section *s, uint64_t value)
{
    for (int i = 0; i < 4; i++) {
        emitbyte(s, (value >> (8 * i)) & 0xFF);
    }
}

void emit8(struct binary_section *s, uint64_t value)
{
    for (int i = 0; i < 8; i++) {
        emitbyte(s, (value >> (8 * i)) & 0xFF);
    }
}

struct binary_section* binarySectionCreate(int section_size, section_kind kind)
{
    struct binary_section *b = malloc(sizeof(struct binary_section));
    b->size = section_size;
    b->kind = kind;
    b->section_offset = 0;
    b->bytes = calloc(section_size, sizeof(char));
    return b;
}


void writeBinary(FILE*fp, struct binary_section *s){

    size_t written = fwrite(s->bytes, 1, s->size, fp);
    if (written != s->size) {
        fprintf(stderr, "Error: incomplete write\n");
    }
}

int registerNumber(register_kind reg)
{
    switch(reg) {
        case OP_RAX: return 0;
        case OP_RCX: return 1;
        case OP_RDX: return 2;
        case OP_RBX: return 3;
        case OP_STACK_POINTER: return 4;      // rsp
        case OP_FRAME_POINTER: return 5;      // rbp
        case OP_SECOND_FUNCTION_ARG: return 6; // rsi
        case OP_FIRST_FUNCTION_ARG: return 7;  // rdi
        case OP_R8:  return 8;
        case OP_R9:  return 9;
        case OP_R10: return 10;
        case OP_R11: return 11;
        case OP_R12: return 12;
        case OP_R13: return 13;
        case OP_R14: return 14;
        case OP_R15: return 15;
        default: printf("UNKNOWN REGISTER\n"); exit(1);
    }
}
/*
MOVQ r/m64, r64	  REX.W + 89 /r	    48 89	move reg → r/m
MOVQ r64, r/m64	  REX.W + 8B /r	    48 8B	move r/m → reg
LEAQ m, r64	      EX.W + 8D /r	    48 8D	load effective address
ADDQ r/m64, r64	  REX.W + 01 /r	    48 01	add r64 to r/m64
ADDQ r64, r/m64	  REX.W + 03 /r	    48 03	add r/m64 to r64
SUBQ r/m64, r64	  REX.W + 29 /r	    48 29	subtract
SUBQ r64, r/m64	  REX.W + 2B /r	    48 2B	subtract
CMPQ r/m64, r64	  REX.W + 39 /r	    48 39	compare
CMPQ r64, r/m64	  REX.W + 3B /r	    48 3B	compare
IDIVQ r/m64	      REX.W + F7 /7	    48 F7 F8+	signed divide
NEGQ r/m64	      REX.W + F7 /3	    48 F7 D8+	negate
INCQ r/m64	      REX.W + FF /0	    48 FF C0+	increment
DECQ r/m64	      REX.W + FF /1	    48 FF C8+	decrement
PUSHQ r64	      50 + reg	        50–57	push register
POPQ r64	      58 + reg	        58–5F	pop register
IMULQ r/m64	      REX.W + F7 /5	    48 F7 E8+	one-operand multiply
JE	74 rel8 or 0F 84 rel32
JNE	75 rel8 or 0F 85 rel32
JL	7C rel8 or 0F 8C rel32
JG	7F rel8 or 0F 8F rel32
JLE	7E rel8 or 0F 8E rel32
JGE	7D rel8 or 0F 8D rel32
JMP	EB rel8 or E9 rel32
CALL	E8 rel32
CQO	48 99
RET	C3
*/

uint8_t getRM(modrm_mod modrm_mod, int num1, int num2)
{
    if(num1 > 8) { num1 -= 8; }
    if(num2 > 8) { num2 -= 8; }
    return (modrm_mod << 6) | (num1 << 3) | (num2);
}

struct op_code* instructionOpCode(struct asm_instr* instr)
{
    struct op_code* aOpCode = malloc(sizeof(struct op_code));

    switch(instr->kind) {
        case OP_INSTR_MOVQ:
            if (is_reg(instr->src) && is_reg(instr->dest)) {
                int src = registerNumber(instr->src->reg);
                int dest = registerNumber(instr->dest->reg);

                aOpCode->size_bytes = 3;  // REX + opcode + modrm
                aOpCode->data = __builtin_bswap16(0x4889) | getRM(MOD_REGISTER, src, dest) << 16;

            }
            else if (is_imm(instr->src) && is_reg(instr->dest)) {
                long imm = instr->src->immediate;
                int dest = registerNumber(instr->dest->reg);

                aOpCode->size_bytes = 7;
                aOpCode->data = (uint32_t) __builtin_bswap16(0x49c7) |  (uint32_t) getRM(MOD_REGISTER, 0b000, dest)  << 16;

                aOpCode->data |= imm << 24;
            }
            else if(is_imm(instr->src) && is_mem(instr->dest)){
                long imm = instr->src->immediate;
                int dest = registerNumber(instr->dest->memory.base);

                aOpCode->size_bytes = 8;
                if(instr->dest->memory.offset == -8){
                    aOpCode->data = (uint32_t) __builtin_bswap16(0x48c7) |  (uint32_t) getRM(MOD_MEM_DISP8, 0b000, dest)  << 16 | (uint32_t) 0xf8 << 24;
                }
                else {
                    printf("MUST IMPLEMENT 1\n");
                }

                aOpCode->data |= imm << 32;

            }
            else if (is_reg(instr->src) && is_mem(instr->dest)) {
                //int src = registerNumber(instr->src->reg);
                int dest = registerNumber(instr->dest->memory.base);

                aOpCode->size_bytes = 4;
                aOpCode->data = (uint32_t) __builtin_bswap16(0x4c89) | (uint32_t) getRM(MOD_MEM_DISP8, 0b101, dest)  << 16 | (uint32_t) 0xf8 << 24;
            }
            else if (is_mem(instr->src) && is_reg(instr->dest)) {
                //int src = registerNumber(instr->dest->memory.base);
                int dest = registerNumber(instr->dest->reg);

                aOpCode->size_bytes = 4;
                aOpCode->data = (uint32_t) __builtin_bswap16(0x4c89) | (uint32_t) getRM(MOD_MEM_DISP8, 0b101, dest)  << 16 | (uint32_t) 0xf8 << 24;
            }
            break;

        case OP_INSTR_LEAQ:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x488D;
            break;

        case OP_INSTR_ADDQ:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x4801;
            break;

        case OP_INSTR_SUBQ:
            if (is_reg(instr->src) && is_reg(instr->dest)) {
                aOpCode->size_bytes = 3;
            }
            else if (is_imm(instr->src) && is_reg(instr->dest)) {
                int dest = registerNumber(instr->dest->reg);
                
                if(abs((int)instr->src->immediate) >= 128) {
                    aOpCode->size_bytes = 7;
                    aOpCode->data = __builtin_bswap16(0x4881) | getRM(MOD_REGISTER, 0b101, dest) << 16 ;
                }
                else{
                    aOpCode->size_bytes = 4;
                    aOpCode->data = __builtin_bswap16(0x4883) | getRM(MOD_REGISTER, 0b101, dest) << 16 ;
                }
                aOpCode->data |= instr->src->immediate << 24;
                                
                
            }
            else if (is_mem(instr->src) || is_mem(instr->dest) || is_label(instr->src) || is_label(instr->dest)) {
                int dest = registerNumber(instr->dest->reg);
                if(abs((int)instr->src->immediate) >= 128) {
                    aOpCode->size_bytes = 7;
                    aOpCode->data = __builtin_bswap16(0x4881) | getRM(MOD_MEM_DISP32, 0b101, dest) << 16 ;
                }
                else{
                    aOpCode->size_bytes = 4;
                    aOpCode->data = __builtin_bswap16(0x48c7) | getRM(MOD_MEM_DISP8, 0b101, dest) << 16 ;
                }
                aOpCode->data |= instr->src->immediate << 24;
                aOpCode->size_bytes = 7;
            }

            break;
        case OP_INSTR_CMPQ:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x4839;
            break;

        case OP_INSTR_IDIVQ:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x48F7;
            break;

        case OP_INSTR_NEGQ:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x48F7;
            break;

        case OP_INSTR_INCQ:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x48FF;
            break;

        case OP_INSTR_DECQ:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x48FF;
            break;

        case OP_INSTR_PUSHQ:
        {
            int src = registerNumber(instr->src->reg);
            if(src <= 7)
            {
                aOpCode->size_bytes = 1;
                aOpCode->data = 0x50 + registerNumber(instr->src->reg);
            }
            else
            {
                aOpCode->size_bytes = 2;
                aOpCode->data = 0x41 | ((0x48 + registerNumber(instr->src->reg)) << 8);
            }
            break;
        }
        case OP_INSTR_POPQ:
        {
            int src = registerNumber(instr->src->reg);
            if(src <= 7)
            {
                aOpCode->size_bytes = 1;
                aOpCode->data = 0x58 + registerNumber(instr->src->reg);
            }
            else
            {
                aOpCode->size_bytes = 2;
                aOpCode->data = 0x41 | ((0x50 + registerNumber(instr->src->reg)) << 8);
            }
            break;
        }
        case OP_INSTR_IMULQ:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x48F7;
            break;

        case OP_INSTR_JE:
            aOpCode->size_bytes = 1;
            aOpCode->data = 0x74;
            break;

        case OP_INSTR_JNE:
            aOpCode->size_bytes = 1;
            aOpCode->data = 0x75;
            break;

        case OP_INSTR_JL:
            aOpCode->size_bytes = 1;
            aOpCode->data = 0x7C;
            break;

        case OP_INSTR_JG:
            aOpCode->size_bytes = 1;
            aOpCode->data = 0x7F;
            break;

        case OP_INSTR_JLE:
            aOpCode->size_bytes = 1;
            aOpCode->data = 0x7E;
            break;

        case OP_INSTR_JGE:
            aOpCode->size_bytes = 1;
            aOpCode->data = 0x7D;
            break;

        case OP_INSTR_JMP:
            aOpCode->size_bytes = 1;
            aOpCode->data = 0xEB;
            break;

        case OP_INSTR_CALL:
            aOpCode->size_bytes = 1;
            aOpCode->data = 0xE8;
            break;

        case OP_INSTR_CQO:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x4899;
            break;

        case OP_INSTR_RET:
            aOpCode->size_bytes = 1;
            aOpCode->data = 0xC3;
            break;

        default:
            free(aOpCode);
            return NULL;
    }

    return aOpCode;
}