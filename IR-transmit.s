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
.global	crc8_calculate_byte_streaming
	.type	crc8_calculate_byte_streaming,@function
/***********************
 * Function `crc8_calculate_byte_streaming' 
 ***********************/
crc8_calculate_byte_streaming:
	add	#llo(-10), r1
	mov.b	r15, 6(r1)
	mov	r14, 8(r1)
	mov	#2, @r1
	jmp	.L2
.L4:
	mov.b	6(r1), 2(r1)
	mov	@r1, r15
	and	#1, r15
	cmp	#0, r15
	jne	.L3
	mov.b	2(r1), r15
	mov.b	r15, r15
	clrc
	rrc.b	r15
	clrc
	rrc.b	r15
	clrc
	rrc.b	r15
	clrc
	rrc.b	r15
	mov.b	r15, 2(r1)
.L3:
	mov	8(r1), r15
	mov.b	@r15, r15
	mov.b	r15, r15
	mov.b	r15, r15
	clrc
	rrc.b	r15
	clrc
	rrc.b	r15
	clrc
	rrc.b	r15
	clrc
	rrc.b	r15
	xor.b	2(r1), r15
	mov.b	r15, 4(r1)
	mov.b	#0, 5(r1)
	mov	4(r1), r15
	and	#15, r15
	mov.b	lookup_table.1414(r15), r15
	mov.b	r15, r14
	mov	8(r1), r15
	mov.b	@r15, r15
	mov.b	r15, r15
	rla	r15
	rla	r15
	rla	r15
	rla	r15
	mov.b	r15, r15
	xor.b	r14, r15
	mov.b	r15, r14
	mov	8(r1), r15
	mov.b	r14, @r15
	add	#llo(-1), @r1
.L2:
	cmp	#1, @r1
	jge	.L4
	add	#10, r1
	ret
.Lfe1:
	.size	crc8_calculate_byte_streaming,.Lfe1-crc8_calculate_byte_streaming
;; End of function 

	.p2align 1,0
.global	sendData
	.type	sendData,@function
/***********************
 * Function `sendData' 
 ***********************/
sendData:
	add	#llo(-16), r1
	mov.b	#0, 5(r1)
	mov.b	#126, 6(r1)
	mov.b	#1, 7(r1)
	mov.b	#0, 8(r1)
	mov.b	#0, 9(r1)
	mov.b	#0, 10(r1)
	mov.b	#0, 11(r1)
	mov.b	#2, 12(r1)
	mov.b	#0, 13(r1)
	mov.b	#llo(-1), 14(r1)
	mov.b	#126, 15(r1)
	mov	#1, @r1
	jmp	.L6
.L7:
	mov	r1, r15
	add	#6, r15
	add	@r1, r15
	mov.b	@r15, r15
	mov	r1, r14
	add	#5, r14
	call	#crc8_calculate_byte_streaming
	add	#1, @r1
.L6:
	cmp	#8, @r1
	jl	.L7
	mov.b	5(r1), r15
	mov.b	r15, 14(r1)
	mov	#0, @r1
	jmp	.L8
.L18:
	mov.b	&__P1OUT, r15
	and.b	#llo(-5), r15
	mov.b	r15, &__P1OUT
	mov	#396, r15
.L9:
	dec	r15
	cmp	#0, r15
	jne	.L9
	mov	r1, r15
	add	#6, r15
	add	@r1, r15
	mov.b	@r15, 4(r1)
	mov	#0, 2(r1)
	jmp	.L10
.L16:
	mov.b	4(r1), r15
	mov	2(r1), r14
	mov.b	r14, r14
	and.b	#15, r14
	cmp.b	#0, r14
	jeq	.L12
.L11:
	rra	r15
	add.b	#llo(-1), r14
	cmp.b	#0, r14
	jne	.L11
.L12:
	and	#1, r15
	mov.b	r15, r15
	cmp.b	#0, r15
	jeq	.L13
	mov.b	&__P1OUT, r15
	bis.b	#4, r15
	mov.b	r15, &__P1OUT
	jmp	.L14
.L13:
	mov.b	&__P1OUT, r15
	and.b	#llo(-5), r15
	mov.b	r15, &__P1OUT
.L14:
	mov	#396, r15
.L15:
	dec	r15
	cmp	#0, r15
	jne	.L15
	add	#1, 2(r1)
.L10:
	cmp	#8, 2(r1)
	jl	.L16
	mov.b	&__P1OUT, r15
	bis.b	#4, r15
	mov.b	r15, &__P1OUT
	mov	#826, r15
.L17:
	dec	r15
	cmp	#0, r15
	jne	.L17
	add	#1, @r1
.L8:
	cmp	#10, @r1
	jl	.L18
	add	#16, r1
	ret
.Lfe2:
	.size	sendData,.Lfe2-sendData
;; End of function 

	.p2align 1,0
.global	sendIRData
	.type	sendIRData,@function
/***********************
 * Function `sendIRData' 
 ***********************/
sendIRData:
	sub	#2, r1
	mov	&bulbState, r15
	cmp	#0, r15
	jne	.L20
	mov.b	#0, &output+16
	mov.b	#1, &output+24
	mov	#1, &bulbState
	jmp	.L21
.L20:
	mov.b	#1, &output+16
	mov.b	#0, &output+24
	mov	#0, &bulbState
.L21:
	mov.b	&__P1SEL, r15
	bis.b	#1, r15
	mov.b	r15, &__P1SEL
	mov.b	#8, &__P1OUT
	mov	#llo(-30204), r15
.L22:
	dec	r15
	cmp	#0, r15
	jne	.L22
	nop
	nop
	mov.b	&__P1SEL, r15
	and.b	#llo(-2), r15
	mov.b	r15, &__P1SEL
	mov	#17999, r15
.L23:
	dec	r15
	cmp	#0, r15
	jne	.L23
	nop
	mov	#0, @r1
	jmp	.L24
.L30:
	mov.b	&__P1SEL, r15
	bis.b	#1, r15
	mov.b	r15, &__P1SEL
	mov.b	#8, &__P1OUT
	mov	#2132, r15
.L25:
	dec	r15
	cmp	#0, r15
	jne	.L25
	nop
	nop
	mov.b	&__P1SEL, r15
	and.b	#llo(-2), r15
	mov.b	r15, &__P1SEL
	mov	@r1, r15
	add	#output, r15
	mov.b	@r15, r15
	cmp.b	#0, r15
	jne	.L26
	mov	#2332, r15
.L27:
	dec	r15
	cmp	#0, r15
	jne	.L27
	nop
	nop
	jmp	.L28
.L26:
	mov	#6832, r15
.L29:
	dec	r15
	cmp	#0, r15
	jne	.L29
	nop
	nop
.L28:
	add	#1, @r1
.L24:
	cmp	#33, @r1
	jl	.L30
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

	.section	.rodata
	.type	lookup_table.1414,@object
	.size	lookup_table.1414,16
lookup_table.1414:
	.byte	0
	.byte	47
	.byte	94
	.byte	113
	.byte	-68
	.byte	-109
	.byte	-30
	.byte	-51
	.byte	87
	.byte	120
	.byte	9
	.byte	38
	.byte	-21
	.byte	-60
	.byte	-75
	.byte	-102
