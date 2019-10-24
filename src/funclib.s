.text
.globl fact
.globl lntwo
.globl gcd

# first argument %rdi
# return value %rax

fact:
    movq    $1,     %rax
    cmpq    $0,     %rdi
    je  factout
    movq    $1,     %r12    # i for loop
factloop:
    cmpq    %rdi,   %r12    # compare i <= n
    jg factout
    imul    %r12,   %rax    # x = x * i
    incq    %r12            # i++
    jmp factloop
factout:
    ret

lntwo:
	xor	%r12,	%r12
	movq	$1,	%r12
	xor	%r11,	%r11
	movq	$0,	%r11
lntwoloop:
	cmpq	%r12,	%rdi
	jle	lntwoout
	imulq	$2,	%r12
	incq	%r11
	jmp	lntwoloop
lntwoout:
    movq    %r11,     %rax
	ret

# r10 == rdi, r12 == rsi
gcd:
    movq    %rdi,   %r10
    movq    %rsi,   %r12
gcdloop:
	cmpq	$0,     %r10
	je	gcdthen
	cmpq	$0,     %r12
	je	gcdend
	cmpq	%r10,	%r12
	jle	gcdlow
	subq	%r10,	%r12
	jmp	gcdloop
gcdlow:
	subq	%r12,	%r10
	jmp	gcdloop
gcdthen:
    movq    %r12,   %rax
    xorq   %r12,   %r12
    xorq   %r10,   %r10
    xorq   %rdi,   %rdi
    xorq   %rsi,   %rsi
	ret
gcdend:
    movq    %r10,   %rax
    xorq   %r12,   %r12
    xorq   %r10,   %r10
    xorq   %rdi,   %rdi
    xorq   %rsi,   %rsi
    ret
