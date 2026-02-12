#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "scannerAssemblerFunc.h"

extern int yylex_destroy();
extern int yylex();
extern FILE *yyin;
extern char *yytext;

int scanFile(bool parsing){

   //if(parsing){ freopen("/dev/null", "w", stdout); }
   enum yytokentype token;

   while(1){
      token = yylex();
      if(token == TOKEN_EOF || token == 0) { break; }
      else if(printOuptut(token, yytext, parsing) < 0){
         fclose(yyin); yylex_destroy(); exit(1);
      }   
   }

   //freopen("/dev/tty", "a", stdout);
   fclose(yyin);
   yylex_destroy();
   return 0;
}

int printOuptut(enum yytokentype token, char* text, bool parsing){
   char* buf = 0;
   switch(token){
      case TOKEN_REGISTER_RAX:
         if(!parsing) printf("REGISTER_RAX\n");
			break;
      case TOKEN_REGISTER_RBX:
         if(!parsing) printf("REGISTER_RBX\n");
			break;
      case TOKEN_REGISTER_RCX:
         if(!parsing) printf("REGISTER_RCX\n");
			break;
      case TOKEN_REGISTER_RDX:
         if(!parsing) printf("REGISTER_RDX\n");
			break;
      case TOKEN_REGISTER_FIRST_FUNCTION_ARG:
         if(!parsing) printf("REGISTER_FIRST_FUNCTION_ARG\n");
			break;
      case TOKEN_REGISTER_SECOND_FUNCTION_ARG:
         if(!parsing) printf("REGISTER_SECOND_FUNCTION_ARG\n");
			break;
      case TOKEN_REGISTER_STACK_POINTER:
         if(!parsing) printf("REGISTER_STACK_POINTER\n");
			break;
      case TOKEN_REGISTER_FRAME_POINTER:
         if(!parsing) printf("REGISTER_FRAME_POINTER\n");
			break;
      case TOKEN_REGISTER_8:
         if(!parsing) printf("REGISTER_8\n");
			break;
      case TOKEN_REGISTER_9:
         if(!parsing) printf("REGISTER_9\n");
			break;
      case TOKEN_REGISTER_10:
         if(!parsing) printf("REGISTER_10\n");
			break;
      case TOKEN_REGISTER_11:
         if(!parsing) printf("REGISTER_11\n");
			break;
      case TOKEN_REGISTER_12:
         if(!parsing) printf("REGISTER_12\n");
			break;
      case TOKEN_REGISTER_13:
         if(!parsing) printf("REGISTER_13\n");
			break;
      case TOKEN_REGISTER_14:
         if(!parsing) printf("REGISTER_14\n");
			break;
      case TOKEN_REGISTER_15:
         if(!parsing) printf("REGISTER_15\n");
			break;
      case TOKEN_IMMEDIATE:
         if(!parsing) printf("IMMEDIATE %s\n", &text[1]);
			break;
      case TOKEN_DIGIT:
         if(!parsing) printf("DIGIT %s\n", text);
			break;
      case TOKEN_OP_LEFT_PAREN:
         if(!parsing) printf("LEFT_PAREN\n");
			break;
      case TOKEN_OP_RIGHT_PAREN:
         if(!parsing) printf("RIGHT_PAREN\n");
			break;
      case TOKEN_OP_COMMA:
         if(!parsing) printf("COMMA\n");
			break;
      case TOKEN_OP_COLON:
         if(!parsing) printf("COLON\n");
			break;
      case TOKEN_OP_NEWLINE:
         if(!parsing) printf(" \\n ");
			break;
      case TOKEN_DIRECTIVE_DATA:
         if(!parsing) printf("DIRECTIVE_DATA\n");
			break;
      case TOKEN_DIRECTIVE_QUAD:
         if(!parsing) printf("DIRECTIVE_QUAD\n");
			break;
      case TOKEN_DIRECTIVE_TEXT:
         if(!parsing) printf("DIRECTIVE_TEXT\n");
			break;
      case TOKEN_DIRECTIVE_GLOBAL:
         if(!parsing) printf("DIRECTIVE_GLOBAL\n");
			break;
      case TOKEN_DIRECTIVE_SECTION:
         if(!parsing) printf("DIRECTIVE_SECTION\n");
			break;
      case TOKEN_DIRECTIVE_GNU_STACK:
         if(!parsing) printf("DIRECTIVE_GNU_STACK\n");
			break;
      case TOKEN_DIRECTIVE_PROGBITS:
         if(!parsing) printf("DIRECTIVE_PROGBITS\n");
			break;
      case TOKEN_DIRECTIVE_FILE:
         if(!parsing) printf("DIRECTIVE_FILE\n");
			break;
      case TOKEN_DIRECTIVE_STRING:
         if(!parsing) printf("DIRECTIVE_STRING\n");
			break;
      case TOKEN_IDENTIFIER:
         if(!parsing) printf("IDENTIFIER %s\n", text);
			break;
      case TOKEN_LITERAL_STRING:
         buf = beautifyString(text);
         if(!parsing) printf("STRING_LITERAL %s\n", buf);
			break;
      case TOKEN_INSTR_MOVQ:
         if(!parsing) printf("INSTR_MOVQ\n");
			break;
      case TOKEN_INSTR_LEAQ:
         if(!parsing) printf("INSTR_LEAQ\n");
			break;
      case TOKEN_INSTR_ADDQ:
         if(!parsing) printf("INSTR_ADDQ\n");
			break;
      case TOKEN_INSTR_SUBQ:
         if(!parsing) printf("INSTR_SUBQ\n");
			break;
      case TOKEN_INSTR_IMULQ:
         if(!parsing) printf("INSTR_IMULQ\n");
			break;
      case TOKEN_INSTR_IDIVQ:
         if(!parsing) printf("INSTR_IDIVQ\n");
			break;
      case TOKEN_INSTR_NEGQ:
         if(!parsing) printf("INSTR_NEGQ\n");
			break;
      case TOKEN_INSTR_INCQ:
         if(!parsing) printf("INSTR_INCQ\n");
			break;
      case TOKEN_INSTR_DECQ:
         if(!parsing) printf("INSTR_DECQ\n");
			break;
      case TOKEN_INSTR_CQO:
         if(!parsing) printf("INSTR_CQO\n");
			break;
      case TOKEN_INSTR_CMPQ:
         if(!parsing) printf("INSTR_CMPQ\n");
			break;
      case TOKEN_INSTR_JE:
         if(!parsing) printf("INSTR_JE\n");
			break;
      case TOKEN_INSTR_JNE:
         if(!parsing) printf("INSTR_JNE\n");
			break;
      case TOKEN_INSTR_JL:
         if(!parsing) printf("INSTR_JL\n");
			break;
      case TOKEN_INSTR_JG:
         if(!parsing) printf("INSTR_JG\n");
			break;
      case TOKEN_INSTR_JLE:
         if(!parsing) printf("INSTR_JLE\n");
			break;
      case TOKEN_INSTR_JGE:
         if(!parsing) printf("INSTR_JGE\n");
			break;
      case TOKEN_INSTR_JMP:
         if(!parsing) printf("INSTR_JMP\n");
			break;
      case TOKEN_INSTR_CALL:
         if(!parsing) printf("INSTR_CALL\n");
			break;
      case TOKEN_INSTR_PUSHQ:
         if(!parsing) printf("INSTR_PUSHQ\n");
			break;
      case TOKEN_INSTR_POPQ:
         if(!parsing) printf("INSTR_POPQ\n");
			break;
      case TOKEN_INSTR_RET:
         if(!parsing) printf("INSTR_RET\n");
			break;
      case TOKEN_ERROR_UNDEFINED_CHAR:
         fprintf(stderr, "Scan Error: %s is not a valid character.\n", text);
         fprintf(stderr, "|%d|\n", text[0]);
         free(buf);
			return -1;
      default:
			break;
   }
   
   free(buf);

   return 0;
}

char* beautifyString(char* str){
   int i = 0;
   int j = 0;
   char c = 0;
   int counter = 0;
   char* buf = calloc(2048, sizeof(char));
   int length = (int) strlen(str);

   for(i = 1; i < length - 1; i++){
      if(str[i] != '\\'){ buf[counter++] = str[i]; }
      else{
         c = str[i + 1];
         if(c == 'n'){ buf[counter++] = '\\'; buf[counter++] = 'n';  }
         else if(c == '0'){ buf[counter++] = '\0'; }
         else if(c == '\\') { buf[counter++] = '\\'; }
         else if(c == '"') { buf[counter++] = '\\'; buf[counter++] = '"';}
         else if(c == '\'') { buf[counter++] = '\\'; buf[counter++] = '\'';}
         else{ buf[counter++] = c; }
         
         for(j = i; j < length - 1; j++){ str[j] = str[j + 1]; }
         length--;
      }
   }

   return buf;
}

char * beautifyChar(char* str){
   if(str[1] != '\\') { return &str[1]; }
   
   if(str[2] == 'n') { return "\n"; }
   else if(str[2] == '0') { return "\0"; }
   else if(str[2] == '\'') { return "'"; }
   else{ return &str[2]; }

   return 0;
}