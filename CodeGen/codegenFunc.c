#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegenFunc.h"
#include "hash_table.h"
#include "decl.h"

struct hash_table * scratch_table = 0;
int label_counter = 0;
FILE* ofp = 0;
extern struct decl * program_pointer;

void codegen(char * input_filename, char * output_filename){
   ofp = fopen(output_filename, "w");
   scratch_table_create();
   fprintf(ofp, ".file \"%s\"\n", input_filename);
   fprintf(ofp, ".section .note.GNU-stack,\"\",@progbits\n");
   /* printf(ofp, ".data\n");
   fprintf(ofp, "   .global strcmp\n"); */
   decl_codegen(program_pointer);
   fclose(ofp);
}

void scratch_table_create(){
   scratch_table = hash_table_create(7,0);
   hash_table_insert(scratch_table, "0", 0);
   hash_table_insert(scratch_table, "1", 0);
   hash_table_insert(scratch_table, "2", 0);
   hash_table_insert(scratch_table, "3", 0);
   hash_table_insert(scratch_table, "4", 0);
   hash_table_insert(scratch_table, "5", 0);
   hash_table_insert(scratch_table, "6", 0);
}


int scratch_alloc(){
   int * p_value = 0;
   char * buf = malloc(2);
   char * ret_val = malloc(2);

   hash_table_firstkey(scratch_table);
   if(hash_table_nextkey(scratch_table, &buf, (void *)&p_value) == 0){
      printf("Out of registers. Exiting\n");
      exit(1);
   }
   
   strcpy(ret_val, buf);
   hash_table_remove(scratch_table, buf);
   return atoi(ret_val);
}

void scratch_free( int r ) {
   char * buf = malloc(2);
   sprintf(buf, "%d", r);
   hash_table_insert(scratch_table, buf, 0);
}

const char * scratch_name( int r ){
   switch(r){
      case 0: return "%rbx";
      case 1: return "%r10";
      case 2: return "%r11";
      case 3: return "%r12";
      case 4: return "%r13";
      case 5: return "%r14";
      case 6: return "%r15";
      case REG_RAX: return "%rax";
   }
   return 0;
}

int label_create(){
   return ++label_counter;
}

char * label_name( int label ){
   char * name = malloc(5);
   sprintf(name, "_L%d", label);
   return name;
}

void label_print( char * s ){
   fprintf(ofp, "%s:\n", s);
}