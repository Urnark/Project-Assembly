
.data
	format:	.asciz	"%d\n"
.bss
	a:	.quad 0
.text
.globl	main

main: 
	pushq	$0
	popq	a
L000:
	pushq	a
	pushq	$5
	popq	%r11
	popq	%r12
	xor	%r13,	%r13
	cmpq	%r11,	%r12
	setl	%r13b
	pushq	%r13
	popq	%r11
	cmpb	$0,	%r11b
	je	L001
	pushq	a
	pushq	$0
	popq	%r11
	popq	%r12
	xor	%r13,	%r13
	cmpq	%r11,	%r12
	sete	%r13b
	pushq	%r13
	popq	%r11
	cmpb	$0,	%r11b
	je	L002
	pushq	$12
	pushq	$6

	popq	%r10
	popq	%r12
LF003:
	cmpq	$0,	%r10
	je	LF005
	cmpq	$0,	%r12
	je	LF006
	cmpq	%r10,	%r12
	jle	LF004
	subq	%r10,	%r12
	jmp	LF003
LF004:
	subq	%r12,	%r10
	jmp	LF003
LF005:
	pushq	%r12
	jmp	LF007
LF006:
	pushq	%r10

	jmp	LF007
LF007:
	popq	%r11
	xor	$0,	%r14
LF008:
	xor	%rax,	%rax
	movq	%r11,	%rax
	movq	$10,	%r12
	cqto
	idivq	%r12
	movq	%rax,	%r11
	addq	$48,	%rdx
	pushq	%rdx
	incq	%r14
	cmpq	$0,	%r11
	je	LF009
	jmp	LF008
LF009:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	popq	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF009
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
L002:
	pushq	a
	pushq	$1
	popq	%r11
	popq	%r12
	xor	%r13,	%r13
	cmpq	%r11,	%r12
	sete	%r13b
	pushq	%r13
	popq	%r11
	cmpb	$0,	%r11b
	je	L010
	pushq	$4
	popq	%r11
	movq	$1,	%r12
	cmpq	$0,	%r11
	je	LF011
	movq	$1,	%r13
LF012:
	cmpq	%r11,	%r13
	jg	LF011
	imul	%r13,	%r12
	incq	%r13
	jmp	LF012
LF011:
	pushq	%r12
	popq	%r11
	xor	$0,	%r14
LF013:
	xor	%rax,	%rax
	movq	%r11,	%rax
	movq	$10,	%r12
	cqto
	idivq	%r12
	movq	%rax,	%r11
	addq	$48,	%rdx
	pushq	%rdx
	incq	%r14
	cmpq	$0,	%r11
	je	LF014
	jmp	LF013
LF014:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	popq	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF014
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
L010:
	pushq	a
	pushq	$2
	popq	%r11
	popq	%r12
	xor	%r13,	%r13
	cmpq	%r11,	%r12
	sete	%r13b
	pushq	%r13
	popq	%r11
	cmpb	$0,	%r11b
	je	L015
	pushq	$32
	popq	%r11
	xor	%r12,	%r12
	movq	$1,	%r12
	xor	%r13,	%r13
	movq	$0,	%r13
LF016:
	cmpq	%r12,	%r11
	jle	LF017
	imulq	$2,	%r12
	incq	%r13
	jmp	LF016
LF017:
	pushq	%r13
	popq	%r11
	xor	$0,	%r14
LF018:
	xor	%rax,	%rax
	movq	%r11,	%rax
	movq	$10,	%r12
	cqto
	idivq	%r12
	movq	%rax,	%r11
	addq	$48,	%rdx
	pushq	%rdx
	incq	%r14
	cmpq	$0,	%r11
	je	LF019
	jmp	LF018
LF019:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	popq	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF019
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
L015:
	pushq	a
	pushq	$1
	popq	%r11
	popq	%r12
	addq	%r11,	%r12
	pushq	%r12
	popq	a
	jmp	L000
L001: 

	movq	$1,	%rdi
	call	exit
