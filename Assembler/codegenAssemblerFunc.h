#include "resolverAssemblerFunc.h"
#include "astAssembler.h"
#include "helper.h"
#include <stdint.h>
#include <stdio.h>

extern long text_address;

typedef enum {
    MOD_MEM_NO_DISP = 0b00,  // memory operand, no displacement
    MOD_MEM_DISP8   = 0b01,  // memory operand with 8-bit displacement
    MOD_MEM_DISP32  = 0b10,  // memory operand with 32-bit displacement
    MOD_REGISTER    = 0b11   // register operand (r/m field refers to a register)
} modrm_mod;

struct binary_section {
    size_t size;
    int section_offset;
    section_kind kind;
    char* bytes;
};

struct op_code {
    size_t size_bytes;
    uint64_t data;
    uint64_t data_extra;
};

struct binary_symbol {
    uint32_t st_name;   // 4 bytes
    uint8_t  st_info;   // 1 byte
    uint8_t  st_other;  // 1 byte
    uint16_t st_shndx;  // 2 bytes
    uint64_t st_value;  // 8 bytes
    uint64_t st_size;   // 8 bytes
};

struct section_description {
    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;
};


struct binary_symbol* createBinarySymbol(uint32_t st_name, uint8_t  st_info, uint8_t  st_other, uint16_t st_shndx, uint64_t st_value, uint64_t st_size);

struct section_description* createBinarySectionDescription(uint32_t sh_name,
    uint32_t sh_type,
    uint64_t sh_flags,
    uint64_t sh_addr,
    uint64_t sh_offset,
    uint64_t sh_size,
    uint32_t sh_link,
    uint32_t sh_info,
    uint64_t sh_addralign,
    uint64_t sh_entsize);

int registerNumber(register_kind reg);
/*
Register Encoding
Register	Number	Opcode	Machine Code
%rax	    0	    50 + 0	50
%rcx	    1	    50 + 1	51
%rdx	    2	    50 + 2	52
%rbx	    3	    50 + 3	53
%rsp	    4	    50 + 4	54
%rbp	    5	    50 + 5	55
%rsi	    6	    50 + 6	56
%rdi	    7	    50 + 7	57
%r8         8       ...
*/


struct op_code* instructionOpCode(struct asm_instr* instr);
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


Example: Decq %rbx
C8 + 3 = CB
Machine code:
48 FF CB

ADDQ rbx rax
48 01 D8
D8 = 11 (mode) 011 (reg1) 000 (reg2) 
*/

enum symbol_bind {
    STB_LOCAL  = 0,
    STB_GLOBAL = 1,
    STB_WEAK   = 2,
};

enum symbol_type {
    STT_NOTYPE  = 0,
    STT_OBJECT  = 1,
    STT_FUNC    = 2,
    // add more as needed
};

void codeGen();
void emitbyte(struct binary_section *s, char byte);
void emit8(struct binary_section *s, uint64_t value);
void emit4(struct binary_section *s, uint64_t value);
void emit2(struct binary_section *s, uint64_t value);
struct binary_section* binarySectionCreate(int section_size, section_kind kind);
void setHeader(struct binary_section *s, uint64_t offset_to_header);
void setInstructions(struct binary_section *s);
void setShstrtab(struct binary_section *s, unsigned int padding);
void setDataStrtab(struct binary_section *data, struct binary_section *strtab);
uint8_t getRM(uint8_t mod, uint8_t reg, uint8_t rm);
void padto8(struct binary_section *s);
void setSectionDescriptions(struct binary_section *s, uint32_t text_size, uint32_t text_padding, uint32_t data_size, uint32_t strTabStringLength);
int strtabLenStrings();
int strtabEntries();

void writeBinary(FILE*fp, struct binary_section *s);
