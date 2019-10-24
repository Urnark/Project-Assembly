.text
.globl fact
.globl lntwo
.globl gcd

# Compute the factorial from the given argument
# Returns the result in %rax
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

# Compute the binary logarithm from the given argument
# Returns the result in %rax
lntwo:
	xor	%r12,	%r12
	movq	$1,	%r12        # x
	xor	%r11,	%r11
	movq	$0,	%r11        # i
lntwoloop:
	cmpq	%r12,	%rdi
	jle	lntwoout            # If %rdi is less or equals to x, go out of the loop
	imulq	$2,	%r12        # x = 2 * x
	incq	%r11            # i++
	jmp	lntwoloop
lntwoout:
    movq    %r11,     %rax  # move i to %rax
	ret

# Compute the gcd from the two arguments
# Returns the results in %rax
gcd:
	cmpq	$0,     %rdi
	je	gcdthen
	cmpq	$0,     %rsi
	je	gcdend
	cmpq	%rdi,	%rsi
	jle	gcdlow
    # a > b
	subq	%rdi,	%rsi
	jmp	gcd
    # a <= b
gcdlow:
	subq	%rsi,	%rdi
	jmp	gcd
gcdthen:
    movq    %rsi,   %rax    # if b == 0, return a
	ret
gcdend:
    movq    %r10,   %rax    # if a == 0, return b
    ret
