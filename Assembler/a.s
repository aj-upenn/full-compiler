.file "good/good13.bminor"
.section .note.GNU-stack,"",@progbits
.data
   .global a
a:
   .quad 0
   .quad 0
   .quad 0
   .quad 0
   .quad 0
   .quad 0
   .quad 0
   .quad 0
   .quad 0
   .quad 0
b:
   .quad 5
.data
   .global rand
.data
   .global srand
.data
   .global time
.text
   .global print_arr
print_arr:
   PUSHQ %rbp
   MOVQ %rsp, %rbp
   SUBQ $8, %rsp
   PUSHQ %r12
   PUSHQ %r13
   PUSHQ %r14
   PUSHQ %r15
   PUSHQ %rbx
   MOVQ $0, -8(%rbp)
   MOVQ $0, %r13
   MOVQ %r13, -8(%rbp)
_L1:
   MOVQ -8(%rbp), %r13
   MOVQ $10, %r10
   CMPQ %r10, %r13
   JL _L3
   MOVQ $0, %r10
   JMP _L4
_L3:
   MOVQ $1, %r10
_L4:
   CMPQ $0, %r10
   JE _L2
   MOVQ -8(%rbp), %rax
   INCQ -8(%rbp)
   JMP _L1
_L2:
   POPQ %rbx
   POPQ %r15
   POPQ %r14
   POPQ %r13
   POPQ %r12
   MOVQ %rbp, %rsp
   POPQ %rbp
   RET
_L99:
   .string "\n"
.text
   .global main
main:
   PUSHQ %rbp
   MOVQ %rsp, %rbp
   SUBQ $32, %rsp
   PUSHQ %r12
   PUSHQ %r13
   PUSHQ %r14
   PUSHQ %r15
   PUSHQ %rbx
   MOVQ $0, %r13
   PUSHQ %r10
   PUSHQ %r11
   MOVQ %r13, %rdi
   CALL time
   POPQ %r11
   POPQ %r10
   MOVQ %rax, %r10
   PUSHQ %r10
   PUSHQ %r11
   MOVQ %r10, %rdi
   CALL srand
   POPQ %r11
   POPQ %r10
   MOVQ %rax, %r13
   MOVQ $0, -8(%rbp)
   MOVQ $0, -16(%rbp)
   MOVQ $0, -24(%rbp)
   MOVQ $0, %r13
   MOVQ %r13, -8(%rbp)
_L5:
   MOVQ -8(%rbp), %r13
   MOVQ $10, %r10
   CMPQ %r10, %r13
   JL _L7
   MOVQ $0, %r10
   JMP _L8
_L7:
   MOVQ $1, %r10
_L8:
   CMPQ $0, %r10
   JE _L6
   PUSHQ %r10
   PUSHQ %r11
   CALL rand
   POPQ %r11
   POPQ %r10
   MOVQ %rax, %r13
   MOVQ $100, %r10
   MOVQ %r13, %rax
   CQO
   IDIVQ %r10
   MOVQ %rdx, %r10
   MOVQ -8(%rbp), %r13
   LEAQ a, %r11
   MOVQ $8, %rax
   IMULQ %r13
   ADDQ %r11, %rax
   MOVQ (%rax), %r11
   MOVQ %r10, (%rax)
   MOVQ -8(%rbp), %rax
   INCQ -8(%rbp)
   JMP _L5
_L6:
   PUSHQ %r10
   PUSHQ %r11
   CALL print_arr
   POPQ %r11
   POPQ %r10
   MOVQ %rax, %r13
   MOVQ $0, %r13
   MOVQ %r13, -8(%rbp)
_L9:
   MOVQ -8(%rbp), %r13
   MOVQ $10, %r10
   CMPQ %r10, %r13
   JL _L11
   MOVQ $0, %r10
   JMP _L12
_L11:
   MOVQ $1, %r10
_L12:
   CMPQ $0, %r10
   JE _L10
   MOVQ $0, %r13
   MOVQ %r13, -16(%rbp)
_L13:
   MOVQ -16(%rbp), %r13
   MOVQ $10, %r10
   CMPQ %r10, %r13
   JL _L15
   MOVQ $0, %r10
   JMP _L16
_L15:
   MOVQ $1, %r10
_L16:
   CMPQ $0, %r10
   JE _L14
   MOVQ -8(%rbp), %r13
   LEAQ a, %r10
   MOVQ $8, %rax
   IMULQ %r13
   ADDQ %r10, %rax
   MOVQ (%rax), %r10
   MOVQ -16(%rbp), %r13
   LEAQ a, %r11
   MOVQ $8, %rax
   IMULQ %r13
   ADDQ %r11, %rax
   MOVQ (%rax), %r11
   CMPQ %r11, %r10
   JL _L19
   MOVQ $0, %r11
   JMP _L20
_L19:
   MOVQ $1, %r11
_L20:
   CMPQ $0, %r11
   JE _L17
   MOVQ -8(%rbp), %r13
   LEAQ a, %r10
   MOVQ $8, %rax
   IMULQ %r13
   ADDQ %r10, %rax
   MOVQ (%rax), %r10
   MOVQ %r10, -24(%rbp)
   MOVQ -16(%rbp), %r13
   LEAQ a, %r10
   MOVQ $8, %rax
   IMULQ %r13
   ADDQ %r10, %rax
   MOVQ (%rax), %r10
   MOVQ -8(%rbp), %r13
   LEAQ a, %r11
   MOVQ $8, %rax
   IMULQ %r13
   ADDQ %r11, %rax
   MOVQ (%rax), %r11
   MOVQ %r10, (%rax)
   MOVQ -24(%rbp), %r13
   MOVQ -16(%rbp), %r10
   LEAQ a, %r11
   MOVQ $8, %rax
   IMULQ %r10
   ADDQ %r11, %rax
   MOVQ (%rax), %r11
   MOVQ %r13, (%rax)
   JMP _L18
_L17:
_L18:
   MOVQ -16(%rbp), %rax
   INCQ -16(%rbp)
   JMP _L13
_L14:
   MOVQ -8(%rbp), %rax
   INCQ -8(%rbp)
   JMP _L9
_L10:
   PUSHQ %r10
   PUSHQ %r11
   CALL print_arr
   POPQ %r11
   POPQ %r10
   MOVQ %rax, %r13
   MOVQ $10, %r13
   MOVQ $2, %r10
   MOVQ %r13, %rax
   CQO
   IDIVQ %r10
   MOVQ %rax, %r10
   MOVQ %r10, -32(%rbp)
   POPQ %rbx
   POPQ %r15
   POPQ %r14
   POPQ %r13
   POPQ %r12
   MOVQ %rbp, %rsp
   POPQ %rbp
   RET
