
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
	pushq	$5
	popq	b
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
	je	L000
	pushq	$1
	movq	$format,	%rdi
	xor	%rsi,	%rsi
	popq	%rsi
	xor	%rax,	%rax
	call	printf
L000:
	pushq	$10
	movq	$format,	%rdi
	xor	%rsi,	%rsi
	popq	%rsi
	xor	%rax,	%rax
	call	printf 

	movq	$1,	%rdi
	call	exit
