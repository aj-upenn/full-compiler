#include "codegenAssemblerFunc.h"
#include "printerAssemblerFunc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern struct asm_program * program_pointer;
//extern section_kind current_section;
//extern long text_address = 0;
const unsigned int SHSTRTAB_LEN = 60;
const unsigned int HEADER_LEN = 64;

void codeGen() {

    int padded_size_text = (text_address + 7) & ~0x7;
    int text_padding = padded_size_text - text_address;
    struct binary_section *instructions = binarySectionCreate(padded_size_text, SECTION_TEXT);
    setInstructions(instructions);

    FILE *fp = fopen("output.o", "wb");
    if (!fp) {
        perror("fopen");
        return;
    }
    

    int strTabStringLength = strlen(program_pointer->lines->directive->name) + 1 + strtabLenStrings() + 1;
    struct binary_section *strtab = binarySectionCreate(strTabStringLength, SECTION_SHSTRTAB);
    
    int data_entries = strtabEntries();
    int data_size = data_entries * sizeof(struct binary_symbol);
    struct binary_section *data = binarySectionCreate(data_size, SECTION_DATA); // UPDATE AT END
    setDataStrtab(data, strtab);

    int current_length = HEADER_LEN + padded_size_text + strTabStringLength + data_size;
    int length_with_SHSTR = current_length + SHSTRTAB_LEN;
    int SHSTR_padding = 8 - (length_with_SHSTR % 8);
    if(SHSTR_padding == 8) { SHSTR_padding = 0; }
    int padded_SHSTR_size = SHSTRTAB_LEN + SHSTR_padding;
    struct binary_section *shstrtab = binarySectionCreate(padded_SHSTR_size, SECTION_SHSTRTAB);
    setShstrtab(shstrtab, SHSTR_padding);

    struct binary_section *section_descriptions = binarySectionCreate(8*sizeof(struct section_description), SECTION_SHSTRTAB); // UPDATE AT END
    setSectionDescriptions(section_descriptions, instructions->size-text_padding, text_padding, data->size, strTabStringLength);

    //struct binary_section *bss = binarySectionCreate(64, SECTION_BSS); // UPDATE AT END
    
    struct binary_section *header = binarySectionCreate(HEADER_LEN, SECTION_HEADER);
    setHeader(header, HEADER_LEN + padded_size_text + strTabStringLength + data_size + padded_SHSTR_size);

    writeBinary(fp, header);
    writeBinary(fp, instructions);
    writeBinary(fp, data);
    writeBinary(fp, strtab);
    writeBinary(fp, shstrtab);
    writeBinary(fp, section_descriptions);
        //writeBinary(fp, symtab);

    fclose(fp);
}

int strtabLenStrings()
{
    struct asm_symbol * symb = program_pointer->symbols;
    uint32_t strtab_index = 0;
    int length = 0;

    while(symb != 0)
    {
        createBinarySymbol(strtab_index,0x10,0,0x01,0,0);
        length += strlen(symb->name)+1;
        strtab_index += strlen(symb->name)+1;
        symb = symb->next;
    }

    return length;
}

int strtabEntries()
{
    struct asm_symbol * symb = program_pointer->symbols;
    int length = 0;

    while(symb != 0)
    {
        length++;
        symb = symb->next;
    }

    return length + 2;
}

void emitDescription(struct binary_section *s, struct section_description * d)
{
    emit4(s, d->sh_name);
    emit4(s, d->sh_type);
    emit8(s, d->sh_flags);
    emit8(s, d->sh_addr);
    emit8(s, d->sh_offset);
    emit8(s, d->sh_size);
    emit4(s, d->sh_link);
    emit4(s, d->sh_info);
    emit8(s, d->sh_addralign);
    emit8(s, d->sh_entsize);

}



void setSectionDescriptions(struct binary_section *s, uint32_t text_size, uint32_t text_padding, uint32_t data_size, uint32_t strTabStringLength)
{
    struct section_description* first = createBinarySectionDescription(0,0,0,0,0,0,0,0,0,0);
    emitDescription(s, first);

    struct section_description* text = createBinarySectionDescription(0x1b,0x01,0x06,0,0x40,text_size,0,0,0x01,0);
    emitDescription(s, text);

    struct section_description* data = createBinarySectionDescription(0x21,0x01,0x03,0,HEADER_LEN+text_size,0,0,0,0x01,0);
    emitDescription(s, data);

    struct section_description* bss = createBinarySectionDescription(0x27,0x08,0x03,0,HEADER_LEN+text_size,0,0,0,0x01,0);
    emitDescription(s, bss);

    struct section_description* notegnustack = createBinarySectionDescription(0x2c,0x01,0,0,HEADER_LEN+text_size,0,0,0,0x01,0);
    emitDescription(s, notegnustack);

    struct section_description* symtab = createBinarySectionDescription(0x01,0x02,0,0,HEADER_LEN+text_size+text_padding,data_size,0x06,strtabEntries()-1,0x08,0x18);
    emitDescription(s, symtab);

    struct section_description* strtab = createBinarySectionDescription(0x09,0x03,0,0,HEADER_LEN+text_size+text_padding+data_size,strTabStringLength,0,0,0x01,0);
    emitDescription(s, strtab);

    struct section_description* shstrtab = createBinarySectionDescription(0x11,0x03,0,0,HEADER_LEN+text_size+text_padding+data_size + strTabStringLength,0x3c,0,0,0x01,0);
    emitDescription(s, shstrtab);
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
#define ELF64_ST_INFO(bind,type) (((bind)<<4)+((type)&0xf))

void setDataStrtab(struct binary_section *data, struct binary_section *strtab)
{
    struct binary_symbol* first =  createBinarySymbol(0,0,0,0,0,0);
    emitSymbol(data, first);
    
    struct binary_symbol* b =  createBinarySymbol(1,0x04,0,0xfff1,0,0);
    emitSymbol(data, b);

    uint32_t strtab_index = 0;
    char tab[100000];
    tab[strtab_index++] = 0;
    strcpy(&tab[1], program_pointer->lines->directive->name);
    strtab_index += strlen(program_pointer->lines->directive->name) + 1;

    struct asm_symbol * symb = program_pointer->symbols;

    while(symb != 0)
    {
            
        uint32_t name_index = strtab_index;

        strcpy(&tab[strtab_index], symb->name);
        strtab_index += strlen(symb->name) + 1;

        uint8_t bind = symb->is_global ? STB_GLOBAL : STB_LOCAL;
        uint8_t info = ELF64_ST_INFO(bind, 0);

        b = createBinarySymbol(name_index, info, 0, 0x01, symb->address, 0);
        emitSymbol(data, b);

        symb = symb->next;

    }

    for(unsigned int i = 0; i < strtab_index; i++)
    {
        emitbyte(strtab, tab[i]);
    }
}

void setShstrtab(struct binary_section *s, unsigned int padding)
{
    char * sections_string = "\0.symtab\0.strtab\0.shstrtab\0.text\0.data\0.bss\0.note.GNU-stack";
    for(size_t i = 0; i < SHSTRTAB_LEN; i++)
    {
        emitbyte(s, sections_string[i]);
    }

    for(unsigned int i = 0; i < padding + 1; i++)
    {
        emitbyte(s, 0);
    }

}


void padto8(struct binary_section *s)
{
    while(s->size % 8 != 0)
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
    padto8(s);
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
    emitbyte(s, 0x08); emitbyte(s, 0x00); // number of sections
    emitbyte(s, 0x07); emitbyte(s, 0x00); // which section has header names
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

// uint8_t getRM(modrm_mod modrm_mod, int num1, int num2)
// {
//     if(num1 > 8) { num1 -= 8; }
//     if(num2 > 8) { num2 -= 8; }
//     return (modrm_mod << 6) | (num1 << 3) | (num2);
// }

struct section_description* createBinarySectionDescription(uint32_t sh_name,
    uint32_t sh_type,
    uint64_t sh_flags,
    uint64_t sh_addr,
    uint64_t sh_offset,
    uint64_t sh_size,
    uint32_t sh_link,
    uint32_t sh_info,
    uint64_t sh_addralign,
    uint64_t sh_entsize){

    struct section_description* sec =
        (struct section_description*) malloc(sizeof(struct section_description));

    if (!sec) return NULL;

    sec->sh_name = sh_name;
    sec->sh_type = sh_type;
    sec->sh_flags = sh_flags;
    sec->sh_addr = sh_addr;
    sec->sh_offset = sh_offset;
    sec->sh_size = sh_size;
    sec->sh_link = sh_link;
    sec->sh_info = sh_info;
    sec->sh_addralign = sh_addralign;
    sec->sh_entsize = sh_entsize;

    return sec;
}

// Compute REX prefix for a 64-bit instruction
uint8_t getREX(int reg_field, int rm_field, int w) {
    uint8_t rex = 0x40;   // 0100----
    if(w) rex |= 0x08;    // W = 1 for 64-bit operand
    if(reg_field >= 8) rex |= 0x04;  // REX.R
    if(rm_field  >= 8) rex |= 0x01;  // REX.B
    return rex;
}

// ModR/M byte
uint8_t getRM(uint8_t mod, uint8_t reg, uint8_t rm) {
    return (mod << 6) | ((reg & 0x7) << 3) | (rm & 0x7);
}

struct op_code* instructionOpCode(struct asm_instr* instr)
{
    struct op_code* aOpCode = malloc(sizeof(struct op_code));

    switch(instr->kind) {
        case OP_INSTR_MOVQ:
            if (is_reg(instr->src) && is_reg(instr->dest)) {
                int src = registerNumber(instr->src->reg);
                int dest = registerNumber(instr->dest->reg);

                aOpCode->size_bytes = 3; // REX + opcode + ModR/M
                aOpCode->data = getREX(src, dest, 1) | 0x89 << 8 | (uint32_t)getRM(MOD_REGISTER, src, dest) << 16;
            }

            else if (is_imm(instr->src) && is_reg(instr->dest)) {
                long imm = instr->src->immediate;
                int dest = registerNumber(instr->dest->reg);

                aOpCode->size_bytes = 7; // REX + opcode + ModR/M + imm32
                aOpCode->data = getREX(0, dest, 1) | 0xC7 << 8 | (uint32_t)getRM(MOD_REGISTER, 0, dest) << 16;
                aOpCode->data |= (uint32_t)imm << 24;
            }

            else if (is_imm(instr->src) && is_mem(instr->dest)) {
                long long imm = instr->src->immediate;
                int base = registerNumber(instr->dest->memory.base);
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;

                aOpCode->size_bytes = (mod == MOD_MEM_DISP8 ? 8 : 10);
                aOpCode->data = getREX(0, base, 1) | 0xC7 << 8 | (uint32_t)getRM(mod, 0, base) << 16;
                aOpCode->data |= (uint32_t)(instr->dest->memory.offset & 0xFF) << 24;
                aOpCode->data |= (imm << 32);
            }

            else if (is_reg(instr->src) && is_mem(instr->dest)) {
                int src  = registerNumber(instr->src->reg);
                int base = registerNumber(instr->dest->memory.base);
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;

                aOpCode->size_bytes = (mod == MOD_MEM_DISP8 ? 4 : 6);
                aOpCode->data = getREX(src, base, 1) | 0x89 << 8 | (uint32_t)getRM(mod, src, base) << 16;
                aOpCode->data |= (uint32_t)(instr->dest->memory.offset & 0xFF) << 24;
            }

            else if (is_mem(instr->src) && is_reg(instr->dest)) {
                int dest = registerNumber(instr->dest->reg);
                int base = registerNumber(instr->src->memory.base);
                int mod  = (instr->src->memory.offset >= -128 && instr->src->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;

                aOpCode->size_bytes = (mod == MOD_MEM_DISP8 ? 4 : 6);
                aOpCode->data = getREX(dest, base, 1) | 0x8B << 8 | (uint32_t)getRM(mod, dest, base) << 16;
                aOpCode->data |= (uint32_t)(instr->src->memory.offset & 0xFF) << 24;
            }
        break;

        case OP_INSTR_LEAQ:
            aOpCode->size_bytes = 2;
            aOpCode->data = 0x488D;
            break;

        case OP_INSTR_ADDQ:
            if (is_reg(instr->src) && is_reg(instr->dest)) {
                int src = registerNumber(instr->src->reg);
                int dest = registerNumber(instr->dest->reg);

                aOpCode->size_bytes = 3; // REX + opcode + ModR/M
                aOpCode->data = getREX(src, dest, 1) | 0x29 << 8 | (uint32_t)getRM(MOD_REGISTER, src, dest) << 16;
            }
            else if (is_imm(instr->src) && is_reg(instr->dest)) {
                
                int dest = registerNumber(instr->dest->reg);
                
                if(abs((int)instr->src->immediate) >= 128) {
                    aOpCode->size_bytes = 7;
                    aOpCode->data = getREX(0, dest, 1) | 0x81 << 8 | (uint32_t)getRM(MOD_REGISTER, 0b000, dest) << 16;
                }
                else{
                    aOpCode->size_bytes = 4;
                    aOpCode->data = getREX(0, dest, 1) | 0x83 << 8 | (uint32_t)getRM(MOD_REGISTER, 0b000, dest) << 16;
                }

                aOpCode->data |= instr->src->immediate << 24;
            }
            else if (is_imm(instr->src) && is_mem(instr->dest)) {

                long long imm = instr->src->immediate;
                int base = registerNumber(instr->dest->memory.base);
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;

                if(abs((int)instr->src->immediate) >= 128) {
                    aOpCode->size_bytes = 8;
                    aOpCode->data = getREX(0, base, 1) | 0x81 << 8 | (uint32_t)getRM(mod, 0b000, base) << 16;
                }
                else{
                    aOpCode->size_bytes = 5;
                    aOpCode->data = getREX(0, base, 1) | 0x83 << 8 | (uint32_t)getRM(mod, 0b000, base) << 16;
                }

                aOpCode->data |= (uint32_t)(instr->dest->memory.offset & 0xFF) << 24;
                aOpCode->data |= (imm << 32);
            }
            else if (is_reg(instr->src) && is_mem(instr->dest)) {
                int src  = registerNumber(instr->src->reg);
                int base = registerNumber(instr->dest->memory.base);
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;

                aOpCode->size_bytes = (mod == MOD_MEM_DISP8 ? 4 : 6);
                aOpCode->data = getREX(src, base, 1) | 0x01 << 8 | (uint32_t)getRM(mod, src, base) << 16;
                aOpCode->data |= (uint32_t)(instr->dest->memory.offset & 0xFF) << 24;
            }
            else if (is_mem(instr->src) && is_reg(instr->dest)) {
                int dest = registerNumber(instr->dest->reg);
                int base = registerNumber(instr->src->memory.base);
                int mod  = (instr->src->memory.offset >= -128 && instr->src->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;

                aOpCode->size_bytes = (mod == MOD_MEM_DISP8 ? 4 : 6);
                aOpCode->data = getREX(dest, base, 1) | 0x03 << 8 | (uint32_t)getRM(mod, dest, base) << 16;
                aOpCode->data |= (uint32_t)(instr->src->memory.offset & 0xFF) << 24;
            }
            break;

        case OP_INSTR_SUBQ:
            if (is_reg(instr->src) && is_reg(instr->dest)) {
                int src = registerNumber(instr->src->reg);
                int dest = registerNumber(instr->dest->reg);

                aOpCode->size_bytes = 3; // REX + opcode + ModR/M
                aOpCode->data = getREX(src, dest, 1) | 0x29 << 8 | (uint32_t)getRM(MOD_REGISTER, src, dest) << 16;
            }
            else if (is_imm(instr->src) && is_reg(instr->dest)) {
                
                int dest = registerNumber(instr->dest->reg);
                
                if(abs((int)instr->src->immediate) >= 128) {
                    aOpCode->size_bytes = 7;
                    aOpCode->data = getREX(0, dest, 1) | 0x81 << 8 | (uint32_t)getRM(MOD_REGISTER, 0b101, dest) << 16;
                }
                else{
                    aOpCode->size_bytes = 4;
                    aOpCode->data = getREX(0, dest, 1) | 0x83 << 8 | (uint32_t)getRM(MOD_REGISTER, 0b101, dest) << 16;
                }

                aOpCode->data |= instr->src->immediate << 24;
            }
            else if (is_imm(instr->src) && is_mem(instr->dest)) {

                long long imm = instr->src->immediate;
                int base = registerNumber(instr->dest->memory.base);
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;

                if(abs((int)instr->src->immediate) >= 128) {
                    aOpCode->size_bytes = 8;
                    aOpCode->data = getREX(0, base, 1) | 0x81 << 8 | (uint32_t)getRM(mod, 0b101, base) << 16;
                }
                else{
                    aOpCode->size_bytes = 5;
                    aOpCode->data = getREX(0, base, 1) | 0x83 << 8 | (uint32_t)getRM(mod, 0b101, base) << 16;
                }

                aOpCode->data |= (uint32_t)(instr->dest->memory.offset & 0xFF) << 24;
                aOpCode->data |= (imm << 32);
            }
            else if (is_reg(instr->src) && is_mem(instr->dest)) {
                int src  = registerNumber(instr->src->reg);
                int base = registerNumber(instr->dest->memory.base);
                int mod  = (instr->dest->memory.offset >= -128 && instr->dest->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;

                aOpCode->size_bytes = (mod == MOD_MEM_DISP8 ? 4 : 6);
                aOpCode->data = getREX(src, base, 1) | 0x29 << 8 | (uint32_t)getRM(mod, src, base) << 16;
                aOpCode->data |= (uint32_t)(instr->dest->memory.offset & 0xFF) << 24;
            }
            else if (is_mem(instr->src) && is_reg(instr->dest)) {
                int dest = registerNumber(instr->dest->reg);
                int base = registerNumber(instr->src->memory.base);
                int mod  = (instr->src->memory.offset >= -128 && instr->src->memory.offset <= 127) ? MOD_MEM_DISP8 : MOD_MEM_DISP32;

                aOpCode->size_bytes = (mod == MOD_MEM_DISP8 ? 4 : 6);
                aOpCode->data = getREX(dest, base, 1) | 0x2b << 8 | (uint32_t)getRM(mod, dest, base) << 16;
                aOpCode->data |= (uint32_t)(instr->src->memory.offset & 0xFF) << 24;
            }

            break;
        case OP_INSTR_CMPQ:
            if (is_imm(instr->src) && is_reg(instr->dest)) {
                //int src = registerNumber(instr->src->reg);
                int dest = registerNumber(instr->dest->reg);
                aOpCode->size_bytes = 4;
                aOpCode->data = getREX(0, dest, 1) | 0x83 << 8 | getRM(MOD_REGISTER, 0b111, dest) << 16 |  instr->src->immediate << 24;
            }
            else if (is_reg(instr->src) && is_reg(instr->dest)) {
                int src = registerNumber(instr->src->reg);
                int dest = registerNumber(instr->dest->reg);
                aOpCode->size_bytes = 3;
                aOpCode->data = getREX(src, dest, 1) | 0x39 << 8 | getRM(MOD_REGISTER, src, dest) << 16;
            }
            break;

        case OP_INSTR_IDIVQ:
            int src = registerNumber(instr->src->reg);
            aOpCode->size_bytes = 3;
            if(src <= 7)
            {
                aOpCode->data = getREX(src, 0, 1) | 0xf7 << 8 | getRM(MOD_REGISTER, 0b111, src) << 16;
            }  
            else
            {
                aOpCode->data = getREX(0, src, 1)| 0xf7 << 8 | getRM(MOD_REGISTER, 0b111, src) << 16;
            }
            break;

        case OP_INSTR_NEGQ:
            src = registerNumber(instr->src->reg);
            aOpCode->size_bytes = 3;
            if(src <= 7)
            {
                aOpCode->data = getREX(src, 0, 1) | 0xf7 << 8 | getRM(MOD_REGISTER, 0b011, src) << 16;
            }  
            else
            {
                aOpCode->data = getREX(0, src, 1) | 0xf7 << 8 | getRM(MOD_REGISTER, 0b011, src) << 16;
            }
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
            src = registerNumber(instr->src->reg);
            aOpCode->size_bytes = 3;
            if(src <= 7)
            {
                aOpCode->data = getREX(src, 0, 1) | 0xf7 << 8 | getRM(MOD_REGISTER, 0b101, src) << 16;
            }  
            else
            {
                aOpCode->data = getREX(0, src, 1) | 0xf7 << 8 | getRM(MOD_REGISTER, 0b101, src) << 16;
            }
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
            aOpCode->data = __builtin_bswap16(0x4899);
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