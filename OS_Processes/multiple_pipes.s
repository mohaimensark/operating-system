	.file	"multiple_pipes.c"
	.text
	.section	.rodata
.LC0:
	.string	"Give the value of x: "
.LC1:
	.string	"%d"
.LC2:
	.string	"Result is: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -44(%rbp)
	jmp	.L2
.L5:
	leaq	-32(%rbp), %rdx
	movl	-44(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	pipe@PLT
	testl	%eax, %eax
	jns	.L3
	movl	$1, %eax
	jmp	.L18
.L3:
	addl	$1, -44(%rbp)
.L2:
	cmpl	$2, -44(%rbp)
	jle	.L5
	call	fork@PLT
	movl	%eax, -40(%rbp)
	cmpl	$0, -40(%rbp)
	jns	.L6
	movl	$2, %eax
	jmp	.L18
.L6:
	cmpl	$0, -40(%rbp)
	jne	.L7
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-32(%rbp), %eax
	leaq	-48(%rbp), %rcx
	movl	$4, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	testq	%rax, %rax
	jns	.L8
	movl	$3, %eax
	jmp	.L18
.L8:
	movl	-48(%rbp), %eax
	addl	$5, %eax
	movl	%eax, -48(%rbp)
	movl	-20(%rbp), %eax
	leaq	-48(%rbp), %rcx
	movl	$4, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	testq	%rax, %rax
	jns	.L10
	movl	$4, %eax
	jmp	.L18
.L10:
	movl	-32(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$0, %eax
	jmp	.L18
.L7:
	call	fork@PLT
	movl	%eax, -36(%rbp)
	cmpl	$0, -36(%rbp)
	jns	.L11
	movl	$5, %eax
	jmp	.L18
.L11:
	cmpl	$0, -36(%rbp)
	jne	.L12
	movl	-32(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-24(%rbp), %eax
	leaq	-48(%rbp), %rcx
	movl	$4, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	testq	%rax, %rax
	jns	.L13
	movl	$6, %eax
	jmp	.L18
.L13:
	movl	-48(%rbp), %eax
	addl	$5, %eax
	movl	%eax, -48(%rbp)
	movl	-12(%rbp), %eax
	leaq	-48(%rbp), %rcx
	movl	$4, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	testq	%rax, %rax
	jns	.L15
	movl	$7, %eax
	jmp	.L18
.L15:
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$0, %eax
	jmp	.L18
.L12:
	movl	-32(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-28(%rbp), %eax
	leaq	-48(%rbp), %rcx
	movl	$4, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	testq	%rax, %rax
	jns	.L16
	movl	$8, %eax
	jmp	.L18
.L16:
	movl	-16(%rbp), %eax
	leaq	-48(%rbp), %rcx
	movl	$4, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	testq	%rax, %rax
	jns	.L17
	movl	$9, %eax
	jmp	.L18
.L17:
	movl	-48(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$0, %edi
	call	wait@PLT
	movl	$0, %eax
.L18:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L19
	call	__stack_chk_fail@PLT
.L19:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
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
