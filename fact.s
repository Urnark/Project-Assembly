
.data
	format:	.asciz	"%d\n"
        mychar:	.asciz	"00000000"
.bss
.text
.globl	main

main: 
	pushq	$0
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$1
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF000:
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
	je	LF001
	jmp	LF000
LF001:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF001
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax
	pushq	$1
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$1
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
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
	pushq	$2
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$2
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
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
	pushq	$3
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$6
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
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
	pushq	$4
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$24
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF008:
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
	je	LF009
	jmp	LF008
LF009:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
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
	movq	%r9,	%rax
	pushq	$5
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$120
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF010:
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
	je	LF011
	jmp	LF010
LF011:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF011
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax
	pushq	$6
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$720
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF012:
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
	je	LF013
	jmp	LF012
LF013:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF013
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax
	pushq	$7
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$5040
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF014:
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
	je	LF015
	jmp	LF014
LF015:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF015
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax
	pushq	$8
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$40320
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF016:
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
	je	LF017
	jmp	LF016
LF017:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF017
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax
	pushq	$9
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$362880
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF018:
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
	je	LF019
	jmp	LF018
LF019:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
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
	movq	%r9,	%rax
	pushq	$10
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$3628800
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF020:
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
	je	LF021
	jmp	LF020
LF021:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF021
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax
	pushq	$11
	popq	%rdi
	call	fact
	pushq	%rax
	pushq	$39916800
	popq	%r11
	popq	%r12
	subq	%r11,	%r12
	pushq	%r12
	popq	%r9
	movq	%r9,	%r10
	xor	$0,	%r14
LF022:
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
	je	LF023
	jmp	LF022
LF023:
	decq	%r14
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$mychar,	%rsi
	popq	(%rsi)
	movq	$1,	%rdx
	syscall
	cmpq	$0,	%r14
	jne	LF023
	movq	$1,	%rax
	movq	$1,	%rdi
	movq	$10,	%r15
	movq	%r15,	(%rsi)
	movq	$1,	%rdx
	syscall
	movq	%r9,	%rax 

	movq	$1,	%rdi
	call	exit
