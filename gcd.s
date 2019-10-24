
.data
	format:	.asciz	"%d\n"
        mychar:	.asciz	"00000000"
.bss
	a:	.quad 0
	b:	.quad 0
.text
.globl	main

main: 
	pushq	$732
	popq	a
	pushq	$2684
	popq	b
L000:
	pushq	a
	pushq	b
	popq	%r11
	popq	%r12
	xor	%r13,	%r13
	cmpq	%r11,	%r12
	setne	%r13b
	pushq	%r13
	popq	%r11
	cmpb	$0,	%r11b
	je	L001
	pushq	a
	pushq	b
	popq	%r11
	popq	%r12
	xor	%r13,	%r13
	cmpq	%r11,	%r12
	setg	%r13b
	pushq	%r13
	popq	%r11
	cmpb	$0,	%r11b
	je	L002
	pushq	a
	pushq	b
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	a
	jmp	L003
L002:
	pushq	b
	pushq	a
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	b
L003:
	jmp	L000
L001:
	pushq	a
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF004:
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
	je	LF005
	jmp	LF004
LF005:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF005
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax
	pushq	a
	pushq	b
	xorq	%rdi,	%rdi

	popq	%rdi
	xor	%rdx,	%rdx
	popq	%rsi
	xorq	%rax,	%rax
	call	gcd
	pushq	%rax
	xorq	%rsi,	%rsi
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF006:
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
	je	LF007
	jmp	LF006
LF007:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF007
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax 

	movq	$1,	%rdi
	call	exit
