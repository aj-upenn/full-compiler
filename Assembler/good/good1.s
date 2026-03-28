.file "good/good20.bminor"
.section .note.GNU-stack,"",@progbits
.text
   .global main
main:
   PUSHQ %rbp
   MOVQ %rsp, %rbp
   SUBQ $1111, %rsp
   PUSHQ %r12
   PUSHQ %r13
   PUSHQ %r14
   PUSHQ %r15
   PUSHQ %rbx
   MOVQ $0, -8(%rbp)
   MOVQ $5, %r13
   MOVQ %r13, -8(%rbp)
   MOVQ -8(%rbp), %r13
   MOVQ %r13, %rax
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
