CMP = gcc -Wall
O_FILES = main.o stmt.o decl.o expr.o symbol.o param_list.o type.o scope.o scanner.o parser.o hash_table.o scannerFunc.o parserFunc.o printerFunc.o typecheckerFunc.o codegenFunc.o

all: clean bminor

main.o: $(filter-out main.o, $(O_FILES))

# Generators
scanner.c: scanner.flex
	flex -o scanner.c scanner.flex

parser.c token.h: parser.bison
	bison --defines=token.h --output=parser.c -v parser.bison

# .o files
%.o: %.c
	$(CMP) -c $< -o $@ 

# Executable
bminor: token.h $(O_FILES)
	$(CMP) $(O_FILES) -o bminor


# Clean
clean:
	rm -f *.o bminor scanner.c token.h parser.c *.output
