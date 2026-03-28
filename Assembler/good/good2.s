.file "good/good20.bminor"
.section .note.GNU-stack,"",@progbits
.text
   .global main
main:
   MOVQ %rsp, %rbp
   MOVQ -8(%rbp), %r15
   MOVQ $3, %r10
   POPQ %rbx
   POPQ %r15
   POPQ %r14
   POPQ %r13
   POPQ %r12
   MOVQ %rbp, %rsp
   POPQ %rbp
   RET
   POPQ %rbx
   POPQ %r15
   POPQ %r14
   POPQ %r13
   POPQ %r12
   MOVQ %rbp, %rsp
   POPQ %rbp
   RET
