# full-compiler

# To start wsl

wsl -d Ubuntu

# To install necessary packages (in wsl):

sudo apt clean
sudo apt install make
sudo apt install bison
sudo apt install gcc
sudo apt install flex

# To Compile & run the CodeGenerator, and run the code:

rm -f a.s && make && ./bminor -codegen good/good20.bminor a.s && gcc -no-pie -g a.s library.c -o myprogram && ./myprogram && echo "Return $?"
