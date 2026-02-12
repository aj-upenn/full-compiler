CMP = gcc -Wall
O_FILES = main.o scannerAssembler.o parserAssembler.o scannerAssemblerFunc.o parserAssemblerFunc.o

all: clean assembler

main.o: $(filter-out main.o, $(O_FILES))

# Generators
scannerAssembler.c: scannerAssembler.flex
	flex -o scannerAssembler.c scannerAssembler.flex

parserAssembler.c token.h: parserAssembler.bison
	bison --defines=token.h --output=parserAssembler.c -v parserAssembler.bison

# .o files
%.o: %.c
	$(CMP) -c $< -o $@ 

# Executable
assembler: token.h $(O_FILES)
	$(CMP) $(O_FILES) -o assembler


# Clean
clean:
	rm -f *.o assembler scannerAssembler.c token.h parserAssembler.c *.output
