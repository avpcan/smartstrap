	.file	"IR-transmit.c"
	.arch msp430g2553
	.cpu 430
	.mpy none

	.text
	.p2align 1,0
.global	sendOne
	.type	sendOne,@function
/***********************
 * Function `sendOne' 
 ***********************/
sendOne:
	mov.b	&__P1SEL, r15
	and.b	#llo(-5), r15
	mov.b	r15, &__P1SEL
	mov.b	#8, &__P1OUT
	mov	#192, r15
.L2:
	dec	r15
	cmp	#0, r15
	jne	.L2
	mov.b	&__P1SEL, r15
	bis.b	#4, r15
	mov.b	r15, &__P1SEL
	mov	#749, r15
.L3:
	dec	r15
	cmp	#0, r15
	jne	.L3
	nop
	ret
.Lfe1:
	.size	sendOne,.Lfe1-sendOne
;; End of function 

	.p2align 1,0
.global	sendZero
	.type	sendZero,@function
/***********************
 * Function `sendZero' 
 ***********************/
sendZero:
	mov.b	&__P1SEL, r15
	and.b	#llo(-5), r15
	mov.b	r15, &__P1SEL
	mov.b	#8, &__P1OUT
	mov	#192, r15
.L5:
	dec	r15
	cmp	#0, r15
	jne	.L5
	mov.b	&__P1SEL, r15
	bis.b	#4, r15
	mov.b	r15, &__P1SEL
	mov	#374, r15
.L6:
	dec	r15
	cmp	#0, r15
	jne	.L6
	nop
	ret
.Lfe2:
	.size	sendZero,.Lfe2-sendZero
;; End of function 

	.p2align 1,0
.global	sendData
	.type	sendData,@function
/***********************
 * Function `sendData' 
 ***********************/
sendData:
	mov.b	&__P1OUT, r15
	xor.b	#5, r15
	mov.b	r15, &__P1OUT
	mov.b	&__P1SEL, r15
	bis.b	#4, r15
	mov.b	r15, &__P1SEL
	mov	#2999, r15
.L8:
	dec	r15
	cmp	#0, r15
	jne	.L8
	nop
	mov.b	&__P1SEL, r15
	and.b	#llo(-5), r15
	mov.b	r15, &__P1SEL
	mov.b	#0, &__P1OUT
	mov	#1499, r15
.L9:
	dec	r15
	cmp	#0, r15
	jne	.L9
	nop
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendZero
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	call	#sendOne
	ret
.Lfe3:
	.size	sendData,.Lfe3-sendData
;; End of function 

	.section	.init9,"ax",@progbits
	.p2align 1,0
.global	main
	.type	main,@function
/***********************
 * Function `main' 
 ***********************/
main:
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
.Lfe4:
	.size	main,.Lfe4-main
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
	call	#sendData
	call	#sendData
	call	#sendData
	call	#sendData
	mov.b	&__P1IFG, r15
	and.b	#llo(-9), r15
	mov.b	r15, &__P1IFG
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	reti
.Lfe5:
	.size	PORT1_ISR,.Lfe5-PORT1_ISR
;; End of function 

