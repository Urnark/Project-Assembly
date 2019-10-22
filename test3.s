
.data
	format:	.asciz	"%d\n"
.bss
	a:	.quad 0
	b:	.quad 0
.text
.globl	main

main: 
	pushq	$5
	popq	a
	pushq	$7
	popq	b
	pushq	a
	pushq	b
	popq	%r11
	popq	%r12
	cmpq	%r11,	%r12
	xor	%r13,	%r13
	setl	%r13b
	pushq	%r13
	popq	%r11
	cmpq	$1,	%r11
	je	L000
	pushq	a
	movq	$format,	%rdi
	popq	%rsi
	xor	%rax,	%rax
	call	printf
	pushq	b
	movq	$format,	%rdi
	popq	%rsi
	xor	%rax,	%rax
	call	printf
L000: 

	movq	$1,	%rdi
	call	exit
