/* Roteiro 3 - Contador binario de leds coloridos */

/* This assembly file uses GNU syntax */
	.text
    .global    main
    .type main function

@-----------------------------------
@ Funcao de gastar tempo
@ Entradas:
@    r0 - valor tempo espera
@ Altera:
@    r0 = 0
@    Flags
@-----------------------------------
delay:
 	push {lr}
again:
 	cmp r0,#0
 	beq return
	sub r0,#1
	b   again
return:
	pop {pc}


@-----------------------------------
@ Funcao Main
@-----------------------------------
 main:
@   Habilita clock do PORTB (System Clock Gating Control)
	ldr r3,SIM_SCGC5
	ldr r2,[r3]
 	movs r1,#128
 	lsl r1,r1,#3
  	orr r2,r1
  	str r2,[r3]
@-------------------------------------------------------------------------------------------
@seta port do led vermelho
@   Zera bits de MUX de PTB18
 	ldr r3,PORTB_PCR18
  	ldr r2,[r3]
   	ldr r1,MUXMASK
  	and r2,r1
   	str r2,[r3]
   	
@   Seta bit 0 do MUX de PTB18, assim os bits de MUX serao 001
  	ldr r3,PORTB_PCR18
  	ldr r2,[r3]
    movs r1,#0x80
 	lsl r1,r1,#1
  	orr r2,r1
   	str r2,[r3]
   	
@   Seta pino 18 do PORTB como saida 
  	ldr r3,GPIOB_PDDR
   	ldr r2,[r3]
    movs r1,#128
   	lsl r1,r1,#11
  	orr r2,r1
 	str r2,[r3]
@---------------------------------------
@seta port do led verde
 	  	
 	@   Zera bits de MUX de PTB19
 	ldr r3,PORTB_PCR19
  	ldr r2,[r3]
   	ldr r1,MUXMASK
  	and r2,r1
   	str r2,[r3]
   	
@   Seta bit 0 do MUX de PTB19, assim os bits de MUX serao 001
  	ldr r3,PORTB_PCR19
  	ldr r2,[r3]
    movs r1,#128
 	lsl r1,r1,#1
  	orr r2,r1
   	str r2,[r3]
   	
@   Seta pino 19 do PORTB como saida ***
  	ldr r3,GPIOB_PDDR
   	ldr r2,[r3]
    movs r1,#128
   	lsl r1,r1,#12
  	orr r2,r1
 	str r2,[r3]
 	
 @-------------------------------------------------------------------------------------
 @	Seta port do led azul
 
 @   Habilita clock do PORTD (System Clock Gating Control)*****
	ldr r3,SIM_SCGC5
	ldr r2,[r3]
 	movs r1,#0x80
 	lsl r1,r1,#5
  	orr r2,r1
  	str r2,[r3]
  
@   Zera bits de MUX de PTD1
 	ldr r3,PORTD_PCR1
  	ldr r2,[r3]
   	ldr r1,MUXMASK
  	and r2,r1
   	str r2,[r3]
   	
@   Seta bit 0 do MUX de PTD1, assim os bits de MUX serao 001
  	ldr r3,PORTD_PCR1
  	ldr r2,[r3]
    movs r1,#128
 	lsl r1,r1,#1
  	orr r2,r1
   	str r2,[r3]
   	
@   Seta pino 1 do PORTD como saida 
  	ldr r3,GPIOD_PDDR
   	ldr r2,[r3]
    movs r1,#1
  	orr r2,r1
 	str r2,[r3]
 	
@------------------------------------------------------------------------------------
@Inicio

	movs r4, #0	@esses dois registradores contam os toggles
	movs  r6, #0

loop:	
@   Espera um tempo
 	ldr r0,WAIT
  	bl delay           

@   Toggle azul
 @   Toogle bit 1, LED azul em PTD1
 	ldr r3,GPIOD_PTOR
 	ldr r2,[r3]
 	movs r1,#1
 	orr r2,r1
 	str r2,[r3]
 
	mov  r5, #1	@se o bit menos signif de r4 for um passa do branch
	tst r4, r5
 	add r4, #1	@toggle bit flag do led azul
	bne loop

@   Toggle verde
@   Toogle bit 19, LED verde em PTB19
 	ldr r3,GPIOB_PTOR
 	ldr r2,[r3]
 	movs r1,#128
 	lsl r1,r1,#12
 	orr r2,r1
 	str r2,[r3]

	mov  r5, #1	@se o bit menos signif de r6 for um passa do branch
	tst r6, r5
	add r6, #1
	bne loop

@   Toggle vermelho
@   Toogle bit 18, LED vermelho em PTB18
 	ldr r3,GPIOB_PTOR
 	ldr r2,[r3]
 	movs r1,#128
 	lsl r1,r1,#11
 	orr r2,r1
 	str r2,[r3]

	b loop

    .align	2

SIM_SCGC5:
	.word	0x40048038
	
PORTB_PCR18:
	.word	0x4004A048
PORTB_PCR19:
	.word	0x4004A04C
GPIOB_PDDR:
	.word	0x400FF054 
GPIOB_PTOR:
	.word	0x400FF04C

	
PORTD_PCR1:
	.word	0x4004C004
GPIOD_PDDR:
	.word	0x400FF0D4 
GPIOD_PTOR:
	.word	0x400FF0CC 
	
MUXMASK:
	.word	0xFFFFF8FF
WAIT:
	.word	5000000

.end @ final do arquivo assembly
