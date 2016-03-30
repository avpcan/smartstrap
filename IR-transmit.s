	.file	"IR-transmit.c"
	.arch msp430g2553
	.cpu 430
	.mpy none

	.comm bulbState,2,2
.global	output
	.data
	.type	output,@object
	.size	output,33
output:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.text
	.p2align 1,0
.global	sendData
	.type	sendData,@function
/***********************
 * Function `sendData' 
 ***********************/
sendData:
	sub	#2, r1
	mov	&bulbState, r15
	cmp	#0, r15
	jne	.L2
	mov.b	#0, &output+16
	mov.b	#1, &output+24
	mov	#1, &bulbState
	jmp	.L3
.L2:
	mov.b	#1, &output+16
	mov.b	#0, &output+24
	mov	#0, &bulbState
.L3:
	mov.b	&__P1SEL, r15
	bis.b	#4, r15
	mov.b	r15, &__P1SEL
	mov.b	#8, &__P1OUT
	mov	#llo(-30204), r15
.L4:
	dec	r15
	cmp	#0, r15
	jne	.L4
	nop
	nop
	mov.b	&__P1SEL, r15
	and.b	#llo(-5), r15
	mov.b	r15, &__P1SEL
	mov	#17999, r15
.L5:
	dec	r15
	cmp	#0, r15
	jne	.L5
	nop
	mov	#0, @r1
	jmp	.L6
.L12:
	mov.b	&__P1SEL, r15
	bis.b	#4, r15
	mov.b	r15, &__P1SEL
	mov.b	#8, &__P1OUT
	mov	#2132, r15
.L7:
	dec	r15
	cmp	#0, r15
	jne	.L7
	nop
	nop
	mov.b	&__P1SEL, r15
	and.b	#llo(-5), r15
	mov.b	r15, &__P1SEL
	mov	@r1, r15
	add	#output, r15
	mov.b	@r15, r15
	cmp.b	#0, r15
	jne	.L8
	mov	#2332, r15
.L9:
	dec	r15
	cmp	#0, r15
	jne	.L9
	nop
	nop
	jmp	.L10
.L8:
	mov	#6832, r15
.L11:
	dec	r15
	cmp	#0, r15
	jne	.L11
	nop
	nop
.L10:
	add	#1, @r1
.L6:
	cmp	#33, @r1
	jl	.L12
	add	#2, r1
	ret
.Lfe1:
	.size	sendData,.Lfe1-sendData
;; End of function 

	.section	.init9,"ax",@progbits
	.p2align 1,0
.global	main
	.type	main,@function
/***********************
 * Function `main' 
 ***********************/
main:
	mov	#0, &bulbState
	mov	#23168, &__WDTCTL
	mov.b	&__P1DIR, r15
	bis.b	#5, r15
	mov.b	r15, &__P1DIR
	mov.b	#0, &__P1SEL
	mov.b	#13, &__P1OUT
	mov.b	#8, &__P1REN
	mov.b	#8, &__P1IE
	mov.b	&__CALBC1_16MHZ, r15
	mov.b	r15, &__BCSCTL1
	mov.b	&__CALDCO_16MHZ, r15
	mov.b	r15, &__DCOCTL
	mov	#420, &__TA0CCR0
	mov	#96, &__TA0CCTL1
	mov	#210, &__TA0CCR1
	mov	#528, &__TA0CTL
	bis	#248, r2
.LIRD0:
.Lfe2:
	.size	main,.Lfe2-main
;; End of function 

	.text
	.p2align 1,0
.global	PORT1_ISR
	.type	PORT1_ISR,@function
/***********************
 * Interrupt Vector 2 Service Routine `PORT1_ISR' 
 ***********************/
PORT1_ISR:
.global	__isr_2
__isr_2:
	push	r15
	push	r14
	push	r13
	push	r12
	call	#sendData
	mov.b	&__P1IFG, r15
	and.b	#llo(-9), r15
	mov.b	r15, &__P1IFG
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	reti
.Lfe3:
	.size	PORT1_ISR,.Lfe3-PORT1_ISR
;; End of function 

