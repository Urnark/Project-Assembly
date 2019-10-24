
.data
	format:	.asciz	"%d\n"
        mychar:	.asciz	"0"
.bss
.text
.globl	main

main: 
 

	movq	$1,	%rdi
	call	exit
