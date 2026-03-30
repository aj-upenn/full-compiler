.file "good/good20.bminor"
.section .note.GNU-stack,"",@progbits
.text
   .global main
main:
   MOVQ -8(%rbp), %r14
   MOVQ %rsp, %rbp
   MOVQ -32(%rbp), %r15
   MOVQ $3, -32(%rbp)
   CMPQ %r11, %r12
   CMPQ %r11, %r10
   CMPQ $1, %r12
   IDIVQ %rbx
   IDIVQ %r12
   IDIVQ %r13
   NEGQ  %r12
   NEGQ  %rax
   IMULQ %rax
   IMULQ %r13
   MOVQ $8, %r11
   SUBQ %r12, %r11
   SUBQ $3, %r11
_A:
   SUBQ $200, %r11
   SUBQ $100, -8(%rbp)
   SUBQ $200, -8(%rbp)
   SUBQ $200, -32(%rbp)
_B:
   SUBQ %r12, -8(%rbp)
   SUBQ %r12, -32(%rbp)
   SUBQ -32(%rbp), %r14
   ADDQ $3, %r11
   ADDQ $200, %r11
   ADDQ $100, -8(%rbp)
_C:
   ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
      ADDQ $200, -8(%rbp)
   ADDQ $200, -32(%rbp)
   ADDQ %r12, -8(%rbp)
   ADDQ %r12, -32(%rbp)
   ADDQ -32(%rbp), %r14
   CQO
   JMP  _A
   RET
