#include "astAssembler.h"

void resolveFile();
void programResolve();
void directiveResolve(struct asm_directive* dir);
void instructionResolve(struct asm_instr* instr);
void incrementQuadWord();
void incrementString(char *str);
struct asm_symbol *lookupSymbol(const char *name);
struct asm_symbol *insertSymbol(const char *name);
void labelResolve(char *label_name);
void symbolPrint(struct asm_symbol *sym);