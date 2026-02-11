CMP = gcc -Wall
O_FILES = main.o scannerAssembler.o parserAssembler.o 

all: clean bminor

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
bminor: token.h $(O_FILES)
	$(CMP) $(O_FILES) -o bminor


# Clean
clean:
	rm -f *.o bminor scannerAssembler.c token.h parserAssembler.c *.output
