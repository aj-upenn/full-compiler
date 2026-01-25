
#ifndef CODEGENFUNC_H
#define CODEGENFUNC_H

typedef enum {
   REG_RAX=7
} reg_t;

void codegen(char * input_filename, char * output_filename);
void scratch_table_create();
int scratch_alloc();
void scratch_free( int r );
const char * scratch_name( int r );
int label_create();
char * label_name( int label );
void label_print( char * s );

#endif