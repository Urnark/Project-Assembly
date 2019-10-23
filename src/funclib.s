.text
.globl fact

# first argument %rdi
# return value %rax

fact:
    movq    $1,     %rax
    cmpq    $0,     %rdi
    je  factout
    movq    $1,     %r12;  // i for loop
factloop:
    cmpq    %rdi,   %r12; // compare i <= n
    jg factout
    imul    %r12,   %rax; // x = x * i
    incq    %r12; // i++
    jmp factloop;

factout:
    jmp Lout




Lout:
