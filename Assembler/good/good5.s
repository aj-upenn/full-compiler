.file "good/good1.bminor"
.section .note.GNU-stack,"",@progbits
.data
   .global b
b:
   .quad 16843009
.data
        .global d
d:
        .quad 9
.text
   .global main
.text
main:
   POPQ %rbp
   RET
