#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "scannerFunc.h"

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
      case TOKEN_EOF:
         if(!parsing) printf("END_OF_FILE\n");
         break;
      case TOKEN_KEY_ARRAY:
         if(!parsing) printf("ARRAY\n");
			break;
      case TOKEN_KEY_AUTO:
         if(!parsing) printf("AUTO\n");
			break;
      case TOKEN_KEY_BOOLEAN:
         if(!parsing) printf("BOOLEAN\n");
			break;
      case TOKEN_KEY_CHAR:
         if(!parsing) printf("CHAR\n");
			break;
      case TOKEN_KEY_ELSE:
         if(!parsing) printf("ELSE\n");
			break;
      case TOKEN_KEY_FALSE:
         if(!parsing) printf("FALSE\n");
			break;
      case TOKEN_KEY_FOR:
         if(!parsing) printf("FOR\n");
			break;
      case TOKEN_KEY_FUNCTION:
         if(!parsing) printf("FUNCTION\n");
			break;
      case TOKEN_KEY_IF:
         if(!parsing) printf("IF\n");
			break;
      case TOKEN_KEY_INTEGER:
         if(!parsing) printf("INTEGER\n");
			break;
      case TOKEN_KEY_PRINT:
         if(!parsing) printf("PRINT\n");
			break;
      case TOKEN_KEY_RETURN:
         if(!parsing) printf("RETURN\n");   
			break;
      case TOKEN_KEY_STRING:
         if(!parsing) printf("STRING\n");
			break;
      case TOKEN_KEY_TRUE:
         if(!parsing) printf("TRUE\n");
			break;
      case TOKEN_KEY_VOID:
         if(!parsing) printf("VOID\n");
			break;
      case TOKEN_KEY_WHILE:
         if(!parsing) printf("WHILE\n");
			break;
      case TOKEN_IDENTIFIER:
         if(!parsing) printf("IDENTIFIER %s\n", text);
			break;
      case TOKEN_OP_LEFT_PAREN:
         if(!parsing) printf("LEFT_PAREN\n");
			break;
      case TOKEN_OP_RIGHT_PAREN:
         if(!parsing) printf("RIGHT_PAREN\n");
			break;
      case TOKEN_OP_LEFT_BRACKET:
         if(!parsing) printf("LEFT_BRACKET\n");
			break;
      case TOKEN_OP_RIGHT_BRACKET:
         if(!parsing) printf("RIGHT_BRACKET\n");
			break;
      case TOKEN_OP_LEFT_BRACE:
         if(!parsing) printf("LEFT_BRACE\n");
			break;
      case TOKEN_OP_RIGHT_BRACE:
         if(!parsing) printf("RIGHT_BRACE\n");
			break;
      case TOKEN_OP_INCREMENT:
         if(!parsing) printf("INCREMENT\n");
			break;
      case TOKEN_OP_DECREMENT:
         if(!parsing) printf("DECREMENT\n");
			break;
      case TOKEN_OP_SUBTRACT:
         if(!parsing) printf("SUBTRACT\n");
			break;
      case TOKEN_OP_ADD:
         if(!parsing) printf("ADD\n");
			break;
      case TOKEN_OP_LOGICAL_NOT:
         if(!parsing) printf("NOT\n");
			break;
      case TOKEN_OP_EXPONENT:
         if(!parsing) printf("EXPONENT\n");
			break;
      case TOKEN_OP_MULTIPLY:
         if(!parsing) printf("MULTIPLY\n");
			break;
      case TOKEN_OP_DIVIDE:
         if(!parsing) printf("DIVIDE\n");
			break;
      case TOKEN_OP_MODULO:
         if(!parsing) printf("MODULO\n");
			break;
      case TOKEN_OP_LESS_THAN:
         if(!parsing) printf("LESS_THAN\n");
			break;
      case TOKEN_OP_LESS_THAN_OR_EQUAL:
         if(!parsing) printf("LESS_THAN_OR_EQUAL\n");
			break;
      case TOKEN_OP_GREATER_THAN:
         if(!parsing) printf("GREATER_THAN\n");
			break;
      case TOKEN_OP_GREATER_THAN_OR_EQUAL:
         if(!parsing) printf("GREATER_THAN_OR_EQUAL\n");
			break;
      case TOKEN_OP_IS_EQUAL:
         if(!parsing) printf("IS_EQUAL\n");
			break;
      case TOKEN_OP_IS_NOT_EQUAL:
         if(!parsing) printf("IS_NOT_EQUAL\n");
			break;
      case TOKEN_OP_ASSIGNMENT:
         if(!parsing) printf("ASSIGNMENT\n");
			break;
      case TOKEN_OP_LOGICAL_AND:
         if(!parsing) printf("LOGICAL_AND\n");
			break;
      case TOKEN_OP_LOGICAL_OR:
         if(!parsing) printf("LOGICAL_OR\n");
			break;
      case TOKEN_OP_SEMICOLON:
         if(!parsing) printf("SEMICOLON\n");
			break;
      case TOKEN_OP_COLON:
         if(!parsing) printf("COLON\n");
			break;
      case TOKEN_OP_TERNARY:
         if(!parsing) printf("TERNARY\n");
			break;
      case TOKEN_OP_COMMA:
         if(!parsing) printf("COMMA\n");
			break;
      case TOKEN_LITERAL_INTEGER:
         if(!parsing) printf("INTEGER_LITERAL %s\n", text);
			break;
      case TOKEN_LITERAL_CHAR:
         buf = beautifyString(text);
         if(!parsing) printf("CHARACTER_LITERAL %s\n", buf);
         break;
      case TOKEN_LITERAL_STRING:
         buf = beautifyString(text);
         if(!parsing) printf("STRING_LITERAL %s\n", buf);
			break;
      case TOKEN_COMMENT_C:
         if(!parsing) printf("C_COMMENT\n");
			break;
      case TOKEN_COMMENT_CPP:
         if(!parsing) printf("CPP_COMMENT\n");
			break;
      case TOKEN_ERROR_INVALID_CHAR_LITERAL:
         fprintf(stderr, "Scan Error: %s is not a valid character literal.\n", text);
         free(buf);
			return -1;
      case TOKEN_ERROR_INVALID_STRING_LITERAL:
         fprintf(stderr, "Scan Error: %s is not a valid string literal.\n", text);
         free(buf);
			return -1;
      case TOKEN_ERROR_INVALID_IDENTIFIER:
         fprintf(stderr, "Scan Error: %s is not a valid Identifier.\n", text);
         free(buf);
			return -1;
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