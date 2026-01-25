#make && ./bminor -codegen sourcefile.bminor a.s && gcc -g a.s library.c -o myprogram && ./myprogram
./bminor -codegen sourcefile.bminor a.s && gcc -no-pie -g a.s library.c -o myprogram && ./myprogram

#echo "Return $?"