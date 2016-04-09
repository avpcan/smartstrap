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
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
.global	on
	.type	on,@object
	.size	on,16
on:
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
.global	off
	.type	off,@object
	.size	off,16
off:
	.byte	0
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
.global	red
	.type	red,@object
	.size	red,17
red:
	.byte	1
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	0
.global	green
	.type	green,@object
	.size	green,17
green:
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	0
.global	blue
	.type	blue,@object
	.size	blue,17
blue:
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	0
.global	white
	.type	white,@object
	.size	white,17
white:
	.byte	1
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.text
	.p2align 1,0
.global	updateOutput
	.type	updateOutput,@function
/***********************
 * Function `updateOutput' 
 ***********************/
updateOutput:
	sub	#4, r1
	mov	r15, 2(r1)
	mov	#0, @r1
	jmp	.L2
.L3:
	mov	@r1, r15
	add	#16, r15
	mov	@r1, r14
	add	2(r1), r14
	mov.b	@r14, r14
	mov.b	r14, output(r15)
	add	#1, @r1
.L2:
	cmp	#16, @r1
	jl	.L3
	add	#4, r1
	ret
.Lfe1:
	.size	updateOutput,.Lfe1-updateOutput
;; End of function 

	.p2align 1,0
.global	setOutput
	.type	setOutput,@function
/***********************
 * Function `setOutput' 
 ***********************/
setOutput:
	mov	&bulbState, r15
	cmp	#6, r15
	jhs	.L5
	rla	r15
	add	#.L12, r15
	mov	@r15, r15
	br	r15	; .L12
	.section	.rodata
	.p2align 1,0
.L12:
	.word	.L6
	.word	.L7
	.word	.L8
	.word	.L9
	.word	.L10
	.word	.L11
	.text
.L6:
	mov	#on, r15
	call	#updateOutput
	mov	#1, &bulbState
	jmp	.L4
.L7:
	mov	#red, r15
	call	#updateOutput
	mov	#2, &bulbState
	jmp	.L4
.L8:
	mov	#green, r15
	call	#updateOutput
	mov	#3, &bulbState
	jmp	.L4
.L9:
	mov	#blue, r15
	call	#updateOutput
	mov	#4, &bulbState
	jmp	.L4
.L10:
	mov	#white, r15
	call	#updateOutput
	mov	#5, &bulbState
	jmp	.L4
.L11:
	mov	#off, r15
	call	#updateOutput
	mov	#0, &bulbState
	jmp	.L4
.L5:
	mov	#on, r15
	call	#updateOutput
	mov	#1, &bulbState
	nop
.L4:
	ret
.Lfe2:
	.size	setOutput,.Lfe2-setOutput
;; End of function 

	.p2align 1,0
.global	sendIRData
	.type	sendIRData,@function
/***********************
 * Function `sendIRData' 
 ***********************/
sendIRData:
	sub	#2, r1
	call	#setOutput
	mov.b	&__P1SEL, r15
	bis.b	#4, r15
	mov.b	r15, &__P1SEL
	mov.b	#8, &__P1OUT
	mov	#llo(-30204), r15
.L15:
	dec	r15
	cmp	#0, r15
	jne	.L15
	nop
	nop
	mov.b	&__P1SEL, r15
	and.b	#llo(-5), r15
	mov.b	r15, &__P1SEL
	mov	#17999, r15
.L16:
	dec	r15
	cmp	#0, r15
	jne	.L16
	nop
	mov	#0, @r1
	jmp	.L17
.L23:
	mov.b	&__P1SEL, r15
	bis.b	#4, r15
	mov.b	r15, &__P1SEL
	mov.b	#8, &__P1OUT
	mov	#2132, r15
.L18:
	dec	r15
	cmp	#0, r15
	jne	.L18
	nop
	nop
	mov.b	&__P1SEL, r15
	and.b	#llo(-5), r15
	mov.b	r15, &__P1SEL
	mov	@r1, r15
	add	#output, r15
	mov.b	@r15, r15
	cmp.b	#0, r15
	jne	.L19
	mov	#2332, r15
.L20:
	dec	r15
	cmp	#0, r15
	jne	.L20
	nop
	nop
	jmp	.L21
.L19:
	mov	#6832, r15
.L22:
	dec	r15
	cmp	#0, r15
	jne	.L22
	nop
	nop
.L21:
	add	#1, @r1
.L17:
	cmp	#33, @r1
	jl	.L23
	add	#2, r1
	ret
.Lfe3:
	.size	sendIRData,.Lfe3-sendIRData
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
	call	#sendIRData
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

