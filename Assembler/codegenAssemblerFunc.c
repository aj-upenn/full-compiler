#include "codegenAssemblerFunc.h"
#include <stdio.h>

extern struct asm_program * program_pointer;
//extern section_kind current_section;

void codeGen() {
    struct binary_section *header = binarySectionCreate(64, SECTION_HEADER);
    setHeader(header, 0);

    writeBinary(header);
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

void writeBinary(struct binary_section *s){
    FILE *f = fopen("output.o", "wb");
    if (!f) {
        perror("fopen");
        return;
    }

    size_t written = fwrite(s->bytes, 1, s->size, f);
    if (written != s->size) {
        fprintf(stderr, "Error: incomplete write\n");
    }

    fclose(f);
}