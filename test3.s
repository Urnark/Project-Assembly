
.data
	format:	.asciz	"%d\n"
.bss
.text
.globl	main

main: 
	pushq	$2
	popq	%r11
	xor	%r12,	%r12
	movq	$1,	%r12
	xor	%r13,	%r13
	movq	$0,	%r13
jmp	loop
loop:
	cmpq	%r12,	%r11
	jle out
	imulq	$2,	%r12
	incq	%r13
	jmp	loop
out:
	pushq	%r13
	movq	$format,	%rdi
	xor	%rsi,	%rsi
	popq	%rsi
	xor	%rax,	%rax
	call	printf 

	movq	$1,	%rdi
	call	exit
