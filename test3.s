
.data
	format:	.asciz	"%d\n"
.bss
	a:	.quad 0
.text
.globl	main

main: 
	pushq	$3
	popq	a
L000:
	pushq	a
	pushq	$3
	popq	%r11
	popq	%r12
	xor	%r13,	%r13
	cmpq	%r11,	%r12
	setl	%r13b
	pushq	%r13
	popq	%r11
	cmpb	$0,	%r11b
	je	L001
	pushq	$4
	popq	a
	jmp	L000
L001: 

	movq	$1,	%rdi
	call	exit
