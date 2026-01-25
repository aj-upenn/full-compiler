%{

#include "token.h"

%}

%option nounput
%option noinput

DIGIT [0-9]
LETTER [a-zA-Z]
IDENTIFIER ([a-zA-Z]|_)([a-zA-Z]|[0-9]|_){0,254}
LITERAL_STRING \"([^"^\n^\\]|(\\.)){0,255}\"

%%

(" "|\t|\n) /* skip whitespace */                                                /* WHITESPACE */


array        { return TOKEN_KEY_ARRAY; }                                         /* KEYWORDS AND IDENTIFIERS */ 
auto         { return TOKEN_KEY_AUTO; } 
boolean      { return TOKEN_KEY_BOOLEAN; } 
char         { return TOKEN_KEY_CHAR; }  
else         { return TOKEN_KEY_ELSE; }  
false        { return TOKEN_KEY_FALSE; }      
for          { return TOKEN_KEY_FOR; } 
function     { return TOKEN_KEY_FUNCTION; }   
if           { return TOKEN_KEY_IF; }           
integer      { return TOKEN_KEY_INTEGER; } 
print        { return TOKEN_KEY_PRINT; }       
return       { return TOKEN_KEY_RETURN; }   
string       { return TOKEN_KEY_STRING; } 
true         { return TOKEN_KEY_TRUE; }       
void         { return TOKEN_KEY_VOID; }   
while        { return TOKEN_KEY_WHILE; }   
{IDENTIFIER} { return TOKEN_IDENTIFIER; }                                   

\(           { return TOKEN_OP_LEFT_PAREN; }                                   /* OPERATORS */ 
\)           { return TOKEN_OP_RIGHT_PAREN; }
\[           { return TOKEN_OP_LEFT_BRACKET; }
\]           { return TOKEN_OP_RIGHT_BRACKET; }
\{           { return TOKEN_OP_LEFT_BRACE; }
\}           { return TOKEN_OP_RIGHT_BRACE; }
\+\+         { return TOKEN_OP_INCREMENT; }
\-\-         { return TOKEN_OP_DECREMENT; }
\-           { return TOKEN_OP_SUBTRACT; }
\+           { return TOKEN_OP_ADD; }
!            { return TOKEN_OP_LOGICAL_NOT; }
\^           { return TOKEN_OP_EXPONENT; }
\*           { return TOKEN_OP_MULTIPLY; }
\/           { return TOKEN_OP_DIVIDE; }
%            { return TOKEN_OP_MODULO; }
\<           { return TOKEN_OP_LESS_THAN; }
\<=          { return TOKEN_OP_LESS_THAN_OR_EQUAL; }
\>           { return TOKEN_OP_GREATER_THAN; }
\>=          { return TOKEN_OP_GREATER_THAN_OR_EQUAL; }
==           { return TOKEN_OP_IS_EQUAL; }
!=           { return TOKEN_OP_IS_NOT_EQUAL; }
=            { return TOKEN_OP_ASSIGNMENT; }
&&           { return TOKEN_OP_LOGICAL_AND; }
\|\|         { return TOKEN_OP_LOGICAL_OR; }
;            { return TOKEN_OP_SEMICOLON; }
:            { return TOKEN_OP_COLON; }
\?           { return TOKEN_OP_TERNARY; }
,            { return TOKEN_OP_COMMA; }

{DIGIT}+                   { return TOKEN_LITERAL_INTEGER; }                         /* LITERLALS */
'([^\n^\\^')]|\\.)'        { return TOKEN_LITERAL_CHAR; }
{LITERAL_STRING}           { return TOKEN_LITERAL_STRING; }
                      
\/\/.*                     /* { return TOKEN_COMMENT_C; } */                                  /* COMMENTS */
\/\*([^*]|\*[^\/])*\*?\*\/ /* { return TOKEN_COMMENT_CPP; } */


('[^'^\\^\n]*\n)|('[^'])             { return TOKEN_ERROR_INVALID_CHAR_LITERAL; }    /* ERROR CHECK */ 
(\"[^"]*\n?)|{LITERAL_STRING}        { return TOKEN_ERROR_INVALID_STRING_LITERAL; }                    
([a-zA-Z]|_)([a-zA-Z]|[0-9]|_){255,} { return TOKEN_ERROR_INVALID_IDENTIFIER; }

.                           { return TOKEN_ERROR_UNDEFINED_CHAR; }   /* any non ascii character */

%%

int yywrap() { return 1; }