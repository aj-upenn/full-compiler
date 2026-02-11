#rm -f a.s && make && ./bminor -codegen good/good20.bminor a.s && gcc -no-pie -g a.s library.c -o myprogram && ./myprogram
#echo "Return $?"
rm -f a.s && make && ./bminor -codegen given/good15.bminor a.s && gcc -no-pie -g a.s -o myprogram && ./myprogram && echo "Return $?"
