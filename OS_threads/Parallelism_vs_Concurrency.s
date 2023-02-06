	.file	"Parallelism_vs_Concurrency.c"
	.text
	.globl	primes
	.data
	.align 32
	.type	primes, @object
	.size	primes, 40
primes:
	.long	2
	.long	3
	.long	5
	.long	7
	.long	11
	.long	13
	.long	17
	.long	19
	.long	23
	.long	29
	.section	.rodata
.LC0:
	.string	"Local sum: %d\n"
	.text
	.globl	routine
	.type	routine, @function
routine:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	$0, -12(%rbp)
	movl	$1, %edi
	call	sleep@PLT
	movl	$0, -8(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	primes(%rip), %rax
	movl	(%rdx,%rax), %eax
	addl	%eax, -12(%rbp)
	addl	$1, -8(%rbp)
.L2:
	cmpl	$4, -8(%rbp)
	jle	.L3
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movl	-12(%rbp), %edx
	movl	%edx, (%rax)
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	routine, .-routine
	.section	.rodata
.LC1:
	.string	"Failed to create thread"
.LC2:
	.string	"Failed to join thread"
.LC3:
	.string	"Global sum: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -68(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -56(%rbp)
	jmp	.L6
.L8:
	movl	$4, %edi
	call	malloc@PLT
	movq	%rax, -40(%rbp)
	movl	-56(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%eax, %edx
	movq	-40(%rbp), %rax
	movl	%edx, (%rax)
	leaq	-32(%rbp), %rdx
	movl	-56(%rbp), %eax
	cltq
	salq	$3, %rax
	leaq	(%rdx,%rax), %rdi
	movq	-40(%rbp), %rax
	movq	%rax, %rcx
	leaq	routine(%rip), %rax
	movq	%rax, %rdx
	movl	$0, %esi
	call	pthread_create@PLT
	testl	%eax, %eax
	je	.L7
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
.L7:
	addl	$1, -56(%rbp)
.L6:
	cmpl	$1, -56(%rbp)
	jle	.L8
	movl	$0, -52(%rbp)
	movl	$0, -56(%rbp)
	jmp	.L9
.L11:
	movl	-56(%rbp), %eax
	cltq
	movq	-32(%rbp,%rax,8), %rax
	leaq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pthread_join@PLT
	testl	%eax, %eax
	je	.L10
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
.L10:
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	addl	%eax, -52(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	addl	$1, -56(%rbp)
.L9:
	cmpl	$1, -56(%rbp)
	jle	.L11
	movl	-52(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L13
	call	__stack_chk_fail@PLT
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
