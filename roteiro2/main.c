// Roteiro 2 - EA871-1S2019 - Aciona LEDs da placa Shield dependendo dos botoes
#include "derivative.h" /* include peripheral declarations */
#define SET_BIT(reg, idx)	reg = (reg | (1 << idx))		// Macro que seta o bit idx do registrador reg

/* Inicializa os GPIOs */
void init_GPIO(void) {

	SET_BIT(SIM_SCGC5, 11);		// Habilita clock do PORTC (System Clock Gating Control)

	PORTC_PCR0 &= 0xFFFFF8FF;	// Configura MUX para PTC0-PTC7 e PTC10 aparecerem nos pinos
	SET_BIT(PORTC_PCR0, 8);		
	PORTC_PCR1 &= 0xFFFFF8FF;
	SET_BIT(PORTC_PCR1, 8);
	PORTC_PCR2 &= 0xFFFFF8FF;
	SET_BIT(PORTC_PCR2, 8);
	PORTC_PCR3 &= 0xFFFFF8FF;
	SET_BIT(PORTC_PCR3, 8);
	PORTC_PCR4 &= 0xFFFFF8FF;
	SET_BIT(PORTC_PCR4, 8);
	PORTC_PCR5 &= 0xFFFFF8FF;
	SET_BIT(PORTC_PCR5, 8);
	PORTC_PCR6 &= 0xFFFFF8FF;
	SET_BIT(PORTC_PCR6, 8);
	PORTC_PCR7 &= 0xFFFFF8FF;
	SET_BIT(PORTC_PCR7, 8);
	PORTC_PCR10 &= 0xFFFFF8FF;
	SET_BIT(PORTC_PCR10, 8);

	GPIOC_PDOR = 0;			// Garante nivel 0 em todas as saidas do PORTC
	GPIOC_PDDR = 0x000004FF;	// Configura bits 0-7 e 10 do PORTC como saidas
	GPIOC_PSOR = (1<<10);       	// Habilita o LE (Latch Enable) do registrador dos LEDs vermelhos (74HC573)
	GPIOC_PCOR = (1<<10);		// Desabilita o LE (Latch Enable) do registrador dos LEDs vermelhos (74HC573)

	//parte dos botões
	SET_BIT(SIM_SCGC5, 9); 		// Habilita clock do PORTA

	PORTA_PCR4 &= 0xFFFFF8FF;	// Configura MUX para PTA4, PTA5, PTA12 aparecerem nos pinos
	SET_BIT(PORTA_PCR4, 8);
	PORTA_PCR5 &= 0xFFFFF8FF;
	SET_BIT(PORTA_PCR5, 8);
	PORTA_PCR12 &= 0xFFFFF8FF;
	SET_BIT(PORTA_PCR12, 8);

	GPIOA_PDDR = 0; 		// Configura todos bits do PORTA como entrada

}

void delay(unsigned int tempo) {

	for ( ; tempo != 0; tempo--);
}

int le_botao(){	//le o botao e retorna 1(esquerda) ,2muda ou 4(direita) para os botoes, se dois botoes forem apertados retorna a soma deles

	uint16_t a=0, pta4=1, pta5=1, pta12=1, botao=0;

	while( pta4  && pta5 && pta12) { //espera apertar um botao
		a = GPIOA_PDIR;       // Faz a leitura no PORTA (16 bits)
		pta4  = a & (1<<4);   
		pta5  = a & (1<<5);  
		pta12 = a & (1<<12);  
	}
	delay(100000);
	while( !pta4  || !pta5 || !pta12) {//espera todos os botoes serem desapertados
		a = GPIOA_PDIR;       // Faz a leitura no PORTA (16 bits)
		pta4  = a & (1<<4);   
		pta5  = a & (1<<5);  
		pta12 = a & (1<<12);  

		//calcula valor de a dependendo dos botoes
		if (!pta4)
			botao|=1;
		if (!pta5)
			botao|=2;
		if (!pta12)
			botao|=4;
	}

	return botao;
}


int main(void) {

	init_GPIO();

	uint8_t leds=0, botao;

	for(;;){
		//le o botao
		botao=le_botao();

		//muda estado do led D7
		if ( botao & 2 )
			leds ^= 1<<7;


		//se os dois botoes de direcao estiverem apertados nao faz nada
		if ( botao & 1 && botao & 4 )
			leds+42;

		//desloca leds para esquerda
		else if ( botao & 1 )
			leds=leds<<1;

		//desloca leds para a direita
		else if ( botao & 4 )
			leds=leds>>1;


		//ascende leds
		GPIOC_PDOR =  leds;		

		GPIOC_PSOR = (1<<10);	//latch enable 74HC573
		GPIOC_PCOR = (1<<10);
        delay(500000);
	}
}



