
.data
	format:	.asciz	"%d\n"
        mychar:	.asciz	"00000000"
.bss
	a:	.quad 0
	n:	.quad 0
	s:	.quad 0
.text
.globl	main

main: 
	pushq	$1000000
	popq	n
	pushq	$100000000
	popq	s
	pushq	$0
	popq	a
L000:
	pushq	n
	pushq	$0
	popq	%r11
	popq	%r12
	xor	%r13,	%r13
	cmpq	%r11,	%r12
	setg	%r13b
	pushq	%r13
	popq	%r11
	cmpb	$0,	%r11b
	je	L001
	pushq	a
	pushq	s
	pushq	n
	popq	%r12
	popq	%rax
	cqto
	idivq	%r12
	pushq	%rax
	popq	%r11
	popq	%r12
	addq	%r11,	%r12
	pushq	%r12
	popq	a
	pushq	n
	pushq	$1
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	n
	jmp	L000
L001:
	pushq	a
	pushq	s
	pushq	$1000
	popq	%r12
	popq	%rax
	cqto
	idivq	%r12
	pushq	%rax
	popq	%r12
	popq	%rax
	cqto
	idivq	%r12
	pushq	%rax
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF002:
	xor	%rax,	%rax
	movq	%r9,	%rax
	movq	$10,	%r12
	cqto
	idivq	%r12
	movq	%rax,	%r9
	addq	$48,	%rdx
	pushq	%rdx
	incq	%r14
	cmpq	$0,	%r9
	je	LF003
	jmp	LF002
LF003:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF003
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax 

	movq	$1,	%rdi
	call	exit
