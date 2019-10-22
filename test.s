.data
	format:	.asciz	"%d\n"
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
	cmpq	%r11,	%r12
	xor	%r13,	%r13
	setne	%r13
	pushq	%r13
	popq	%r11
	cmpq	%1,	%r11
	je	L001
	pushq	a
	pushq	b
	popq	%r11
	popq	%r12
	cmpq	%r11,	%r12
	xor	%r13,	%r13
	setg	%r13
	pushq	%r13
	popq	%r11
	cmpq	%1,	%r11
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
	movq	$format,	%rdi
	popq	%rsi
	xor	%rax,	%rax
	call	printf
	pushq	a
	pushq	b
	popq	%r11
	popq	%r12
loop:	cmpq	%r11,	$0
	je then
	cmpq	%r12,	$0
	je end
	cmpq	%r11,	%r12;	jle low
	subq	%r11,	%r12
	jmp loop
low:	subq	%r12,	%r11
	jmp loop
then:	pushq	%r12
end:	pushq	%r11
	movq	$format,	%rdi
	popq	%rsi
	xor	%rax,	%rax
	call	printf 

	movq	$1,	%rdi
	call	exit
