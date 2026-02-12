%{

#include "token.h"

%}

%option nounput
%option noinput

DIGIT [0-9]
REGISTER_SUFFIX \%r
IDENTIFIER ([a-zA-Z]|_)([a-zA-Z]|[0-9]|_){0,254}
LITERAL_STRING \"([^"^\n^\\]|(\\.)){0,255}\"

%%

(" "|\t|\r) /* skip whitespace */

{REGISTER_SUFFIX}ax        { return TOKEN_REGISTER_RAX; }
{REGISTER_SUFFIX}bx        { return TOKEN_REGISTER_RBX; }
{REGISTER_SUFFIX}cx        { return TOKEN_REGISTER_RCX; }
{REGISTER_SUFFIX}dx        { return TOKEN_REGISTER_RDX; }

{REGISTER_SUFFIX}di        { return TOKEN_REGISTER_FIRST_FUNCTION_ARG; }
{REGISTER_SUFFIX}si        { return TOKEN_REGISTER_SECOND_FUNCTION_ARG; }
{REGISTER_SUFFIX}sp        { return TOKEN_REGISTER_STACK_POINTER; }
{REGISTER_SUFFIX}bp        { return TOKEN_REGISTER_FRAME_POINTER; }

{REGISTER_SUFFIX}8         { return TOKEN_REGISTER_8; } 
{REGISTER_SUFFIX}9         { return TOKEN_REGISTER_9; }
{REGISTER_SUFFIX}10        { return TOKEN_REGISTER_10; }
{REGISTER_SUFFIX}11        { return TOKEN_REGISTER_11; }
{REGISTER_SUFFIX}12        { return TOKEN_REGISTER_12; }
{REGISTER_SUFFIX}13        { return TOKEN_REGISTER_13; }
{REGISTER_SUFFIX}14        { return TOKEN_REGISTER_14; }
{REGISTER_SUFFIX}15        { return TOKEN_REGISTER_15; }

$-?{DIGIT}+                { return TOKEN_IMMEDIATE; }
-?{DIGIT}+                 { return TOKEN_DIGIT; }

\(                         { return TOKEN_OP_LEFT_PAREN; }
\)                         { return TOKEN_OP_RIGHT_PAREN; }
,                          { return TOKEN_OP_COMMA; }
:                          { return TOKEN_OP_COLON; }
\n                         { return TOKEN_OP_NEWLINE; }

\.data                     { return TOKEN_DIRECTIVE_DATA; }
\.quad                     { return TOKEN_DIRECTIVE_QUAD; }
\.text                     { return TOKEN_DIRECTIVE_TEXT; }
\.global                   { return TOKEN_DIRECTIVE_GLOBAL; }
\.section                  { return TOKEN_DIRECTIVE_SECTION; }
\.note\.GNU-stack          { return TOKEN_DIRECTIVE_GNU_STACK; }
@progbits                  { return TOKEN_DIRECTIVE_PROGBITS; }
\.file                     { return TOKEN_DIRECTIVE_FILE; }
\.string                   { return TOKEN_DIRECTIVE_STRING; }

MOVQ                       { return TOKEN_INSTR_MOVQ; }
LEAQ                       { return TOKEN_INSTR_LEAQ; }
ADDQ                       { return TOKEN_INSTR_ADDQ; }
SUBQ                       { return TOKEN_INSTR_SUBQ; }
IMULQ                      { return TOKEN_INSTR_IMULQ; }
IDIVQ                      { return TOKEN_INSTR_IDIVQ; }
NEGQ                       { return TOKEN_INSTR_NEGQ; }
INCQ                       { return TOKEN_INSTR_INCQ; }
DECQ                       { return TOKEN_INSTR_DECQ; }
CQO                        { return TOKEN_INSTR_CQO; }
CMPQ                       { return TOKEN_INSTR_CMPQ; }
JE                         { return TOKEN_INSTR_JE; }
JNE                        { return TOKEN_INSTR_JNE; }
JL                         { return TOKEN_INSTR_JL; }
JG                         { return TOKEN_INSTR_JG; }
JLE                        { return TOKEN_INSTR_JLE; }
JGE                        { return TOKEN_INSTR_JGE; }
JMP                        { return TOKEN_INSTR_JMP; }
CALL                       { return TOKEN_INSTR_CALL; }
PUSHQ                      { return TOKEN_INSTR_PUSHQ; }
POPQ                       { return TOKEN_INSTR_POPQ; }

{IDENTIFIER}               { return TOKEN_IDENTIFIER; } 
{LITERAL_STRING}           { return TOKEN_LITERAL_STRING; }

.                          { return TOKEN_ERROR_UNDEFINED_CHAR; }   /* any non ascii character */

%%

int yywrap() { return 1; }