#include "resolverAssemblerFunc.h"
#include "astAssembler.h"
#include <stdint.h>

struct binary_section {
    size_t size;
    int section_offset;
    section_kind kind;
    char* bytes;
};

void codeGen();
void emitbyte(struct binary_section *s, char byte);
void emit8(struct binary_section *s, uint64_t value);
struct binary_section* binarySectionCreate(int section_size, section_kind kind);
void setHeader(struct binary_section *s, uint64_t offset_to_header);
void writeBinary(struct binary_section *s);
