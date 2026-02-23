
%token TOKEN_REGISTER_RAX
%token TOKEN_REGISTER_RBX
%token TOKEN_REGISTER_RCX
%token TOKEN_REGISTER_RDX

%token TOKEN_REGISTER_FIRST_FUNCTION_ARG
%token TOKEN_REGISTER_SECOND_FUNCTION_ARG
%token TOKEN_REGISTER_STACK_POINTER
%token TOKEN_REGISTER_FRAME_POINTER

%token TOKEN_REGISTER_8
%token TOKEN_REGISTER_9
%token TOKEN_REGISTER_10
%token TOKEN_REGISTER_11
%token TOKEN_REGISTER_12
%token TOKEN_REGISTER_13
%token TOKEN_REGISTER_14
%token TOKEN_REGISTER_15

%token TOKEN_IMMEDIATE
%token TOKEN_DIGIT

%token TOKEN_OP_LEFT_PAREN
%token TOKEN_OP_RIGHT_PAREN
%token TOKEN_OP_COMMA 
%token TOKEN_OP_COLON
%token TOKEN_OP_NEWLINE

%token TOKEN_DIRECTIVE_DATA
%token TOKEN_DIRECTIVE_QUAD
%token TOKEN_DIRECTIVE_TEXT
%token TOKEN_DIRECTIVE_GLOBAL
%token TOKEN_DIRECTIVE_SECTION
%token TOKEN_DIRECTIVE_GNU_STACK
%token TOKEN_DIRECTIVE_PROGBITS
%token TOKEN_DIRECTIVE_FILE
%token TOKEN_DIRECTIVE_STRING

%token TOKEN_IDENTIFIER
%token TOKEN_LITERAL_STRING

%token TOKEN_INSTR_MOVQ
%token TOKEN_INSTR_LEAQ
%token TOKEN_INSTR_ADDQ
%token TOKEN_INSTR_SUBQ
%token TOKEN_INSTR_IMULQ
%token TOKEN_INSTR_IDIVQ
%token TOKEN_INSTR_NEGQ
%token TOKEN_INSTR_INCQ
%token TOKEN_INSTR_DECQ
%token TOKEN_INSTR_CQO
%token TOKEN_INSTR_CMPQ
%token TOKEN_INSTR_JE
%token TOKEN_INSTR_JNE
%token TOKEN_INSTR_JL
%token TOKEN_INSTR_JG
%token TOKEN_INSTR_JLE
%token TOKEN_INSTR_JGE
%token TOKEN_INSTR_JMP
%token TOKEN_INSTR_CALL
%token TOKEN_INSTR_PUSHQ
%token TOKEN_INSTR_POPQ
%token TOKEN_INSTR_RET

%token TOKEN_ERROR_UNDEFINED_CHAR
%token TOKEN_EOF

%union {
   struct asm_instr* instr;
   struct asm_operand* operand;
   struct asm_line* line;
   struct asm_directive* directive;
   struct asm_program* program;
   int command;
   int reg_num;
   int imm;
   char *name;
   
};

%type <command> instruction_2_operand instruction_1_operand instruction_0_operand
%type <instr> instruction
%type <reg_num> register
%type <imm> immediate literal_digit
%type <name> identifier literal_string
%type <operand> operand memory
%type <line> line label line_list
%type <program> program
%type <directive> directive

%{

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scannerAssemblerFunc.h"
#include "astAssembler.h"

extern char *yytext;
extern int yylex();
extern int yyerror( char *str );
extern struct asm_program * program_pointer;

%}

%%

/* PROGRAM */

program  : /* epsilon */   { $$ = 0; }
         | line_list       { program_pointer = $$ = program_create($1); }
         ;

identifier : TOKEN_IDENTIFIER { $$ = strdup(yytext); }
           ;

operand  : identifier { $$ = operand_create_label($1); }
         | immediate  { $$ = operand_create_immediate($1); }
         | memory     { $$ = $1; }
         | register   { $$ = operand_create_register($1); }
         ;

memory   : TOKEN_OP_LEFT_PAREN register TOKEN_OP_RIGHT_PAREN                 { $$ = operand_create_memory(0, $2); }
         | literal_digit TOKEN_OP_LEFT_PAREN register TOKEN_OP_RIGHT_PAREN   { $$ = operand_create_memory($1, $3); }
         ;

label    :  identifier TOKEN_OP_COLON { $$ = line_create(ASM_LINE_LABEL, $1, 0, 0); }
         ;

immediate: TOKEN_IMMEDIATE  { $$ = atoi(yytext+1); }  // skip $  
         ;

register : TOKEN_REGISTER_RAX                  { $$ = OP_RAX; }
         | TOKEN_REGISTER_RBX                  { $$ = OP_RBX; }
         | TOKEN_REGISTER_RCX                  { $$ = OP_RCX; }
         | TOKEN_REGISTER_RDX                  { $$ = OP_RDX; }
         | TOKEN_REGISTER_FIRST_FUNCTION_ARG   { $$ = OP_FIRST_FUNCTION_ARG; }
         | TOKEN_REGISTER_SECOND_FUNCTION_ARG  { $$ = OP_SECOND_FUNCTION_ARG; }
         | TOKEN_REGISTER_STACK_POINTER        { $$ = OP_STACK_POINTER; }
         | TOKEN_REGISTER_FRAME_POINTER        { $$ = OP_FRAME_POINTER; }
         | TOKEN_REGISTER_8                    { $$ = OP_R8; }
         | TOKEN_REGISTER_9                    { $$ = OP_R9; }
         | TOKEN_REGISTER_10                   { $$ = OP_R10; }
         | TOKEN_REGISTER_11                   { $$ = OP_R11; }
         | TOKEN_REGISTER_12                   { $$ = OP_R12; }
         | TOKEN_REGISTER_13                   { $$ = OP_R13; }
         | TOKEN_REGISTER_14                   { $$ = OP_R14; }
         | TOKEN_REGISTER_15                   { $$ = OP_R15; }
    ;

instruction_2_operand : TOKEN_INSTR_MOVQ  { $$ = OP_INSTR_MOVQ; }
                      | TOKEN_INSTR_LEAQ  { $$ = OP_INSTR_LEAQ; }
                      | TOKEN_INSTR_ADDQ  { $$ = OP_INSTR_ADDQ; }
                      | TOKEN_INSTR_SUBQ  { $$ = OP_INSTR_SUBQ; }
                      | TOKEN_INSTR_CMPQ  { $$ = OP_INSTR_CMPQ; }
                      ;

instruction_1_operand : TOKEN_INSTR_NEGQ   { $$ = OP_INSTR_NEGQ; }
                      | TOKEN_INSTR_IMULQ  { $$ = OP_INSTR_IMULQ; }
                      | TOKEN_INSTR_IDIVQ  { $$ = OP_INSTR_IDIVQ; }
                      | TOKEN_INSTR_INCQ   { $$ = OP_INSTR_INCQ; }
                      | TOKEN_INSTR_DECQ   { $$ = OP_INSTR_DECQ; }
                      | TOKEN_INSTR_CALL   { $$ = OP_INSTR_CALL; }
                      | TOKEN_INSTR_JE     { $$ = OP_INSTR_JE; }
                      | TOKEN_INSTR_JNE    { $$ = OP_INSTR_JNE; }
                      | TOKEN_INSTR_JL     { $$ = OP_INSTR_JL; }
                      | TOKEN_INSTR_JLE    { $$ = OP_INSTR_JLE; }
                      | TOKEN_INSTR_JG     { $$ = OP_INSTR_JG; }
                      | TOKEN_INSTR_JGE    { $$ = OP_INSTR_JGE; }
                      | TOKEN_INSTR_JMP    { $$ = OP_INSTR_JMP; }
                      | TOKEN_INSTR_PUSHQ  { $$ = OP_INSTR_PUSHQ; }
                      | TOKEN_INSTR_POPQ   { $$ = OP_INSTR_POPQ; }
                      ;
                  
instruction_0_operand: TOKEN_INSTR_CQO     { $$ = OP_INSTR_CQO; }
                     | TOKEN_INSTR_RET     { $$ = OP_INSTR_RET; }
                     ;

instruction : instruction_2_operand operand TOKEN_OP_COMMA operand { $$ = instr_create($1, $2, $4); }
            | instruction_1_operand operand                        { $$ = instr_create($1, $2, 0); }
            | instruction_0_operand                                { $$ = instr_create($1, 0, 0); } 
            ;

line        : instruction TOKEN_OP_NEWLINE    { $$ = line_create(ASM_LINE_INSTRUCTION, 0, 0, $1); }   
            | label TOKEN_OP_NEWLINE          { $$ = $1; }   
            | directive TOKEN_OP_NEWLINE      { $$ = line_create(ASM_LINE_DIRECTIVE, 0, $1, 0); }   
            | TOKEN_OP_NEWLINE                { $$ = 0; }   
            ;

directive   : TOKEN_DIRECTIVE_FILE literal_string                             { $$ = directive_create(DIR_FILE, $2, 0, 0); }                                                        
            | TOKEN_DIRECTIVE_SECTION TOKEN_DIRECTIVE_GNU_STACK TOKEN_OP_COMMA 
              literal_string TOKEN_OP_COMMA TOKEN_DIRECTIVE_PROGBITS          { $$ = directive_create(DIR_SECTION, $4, 0, 0); }  
            | TOKEN_DIRECTIVE_DATA                                            { $$ = directive_create(DIR_DATA, 0, 0, 0); }  
            | TOKEN_DIRECTIVE_GLOBAL identifier                               { $$ = directive_create(DIR_GLOBAL, $2, 0, 0); }  
            | TOKEN_DIRECTIVE_TEXT                                            { $$ = directive_create(DIR_TEXT, 0, 0, 0); }  
            | TOKEN_DIRECTIVE_STRING literal_string                           { $$ = directive_create(DIR_STRING, 0, $2, 0); }  
            | TOKEN_DIRECTIVE_QUAD literal_digit                              { $$ = directive_create(DIR_QUAD, 0, 0, $2); }  
            ;

line_list   : line line_list   { $$ = $1; $1->next = $2; }
            | line             { $$ = $1; }
            ; 
            
literal_string : TOKEN_LITERAL_STRING  { $$ = strdup(beautifyString(yytext)); }
               ;

literal_digit : TOKEN_DIGIT { $$ = atoi(yytext); }
              ;

%%

int yyerror( char *str ) {
   printf("Parse Error: %s\n",str);
   return 0;
}