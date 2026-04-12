.file "good/good4.bminor"
.section .note.GNU-stack,"",@progbits
.text
   MOVQ %r13, %rdi
   PUSHQ %r10
   PUSHQ %r11
   POPQ %r11
   POPQ %r10
   POPQ %rbx
   POPQ %r15
   POPQ %r14
   POPQ %r13
   POPQ %r12
   MOVQ %rbp, %rsp
   POPQ %rbp
   RET
.text
   .global main
.text
main:
   PUSHQ %rbp
   MOVQ %rsp, %rbp
   SUBQ $8, %rsp
   PUSHQ %r12
   PUSHQ %r13
.data
_L11:
   .string "aaaaaaaaaa"
.data
_L12:
   .string "bbbbbbbbbbbbb"
.text
_L3:
   PUSHQ %r14
   PUSHQ %r15
   PUSHQ %rbx
   MOVQ $0, -8(%rbp)
   MOVQ $0, %r13
   MOVQ %r13, -8(%rbp)
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   JE _L3
   JNE _L3
   JL _L3
   JG _L3
   JLE _L3
   JGE _L3
