// Roteiro 1 - EA871-1S2019 - Pisca LED do LED RGB da placa Freedom


// PDDR pinos output(1) ou input(0)
// PTOR port toggle output (1)Corresponding bit in PDORn does not change. (0)Corresponding bit in PDORn is set to the inverse of its existing logic state.
//PCR bits 10-8 MUX: (001) Alternative 1 (GPIO).
//SCGC5 Port Clock Gate Control (1)clock enabled, (0)clock disabled, 12PORTD 10PORTB

//LEDS-catodos: green-PTB19, blue-PTD1, red-PTB18

#define SIM_SCGC5   (*(unsigned int volatile *) 0x40048038)	// Habilita as Portas do GPIO (Reg. SIM_SCGC5)
#define PORTB_PCR18 (*(unsigned int volatile *) 0x4004A048)	// MUX de PTB18 (Reg. PORTB_PCR18)
#define PORTB_PCR19 (*(unsigned int volatile *) 0x4004A04C)	// MUX de PTB19 (Reg. PORTB_PCR19)
#define PORTD_PCR1  (*(unsigned int volatile *) 0x4004C004)	// MUX de PTD1 (Reg. PORTD_PCR1)
#define GPIOB_PDDR  (*(unsigned int volatile *) 0x400FF054)	// Data direction do PORTB (Reg. GPIOB_PDDR)
#define GPIOB_PTOR  (*(unsigned int volatile *) 0x400FF04C)	// Toggle register do PORTB (Reg. GPIOB_PTOR)
#define GPIOD_PDDR  (*(unsigned int volatile *) 0x400FF0D4)	// Data direction do PORTD (Reg. GPIOD_PDDR)
#define GPIOD_PTOR  (*(unsigned int volatile *) 0x400FF0CC)	// Toggle register do PORTD (Reg. GPIOD_PTOR)

#define SHORT_TIME	2000000

#define SET_BIT(reg, idx)	reg = (reg | (1 << idx))	// Macro que seta o bit idx do registrador reg

void delay(unsigned int tempo)  {
	
	for ( ; tempo != 0; tempo--) ;  // espera antes de retornar
	
}

int main(void) {
	SET_BIT(SIM_SCGC5, 10);		   	// Habilita clock do PORTB (System Clock Gating Control)
	SET_BIT(SIM_SCGC5, 12);		   	// Habilita clock do PORTD (System Clock Gating Control)
	
	PORTB_PCR18 = PORTB_PCR18 & 0xFFFFF8FF;	// Zera bits de MUX de PTB18
	SET_BIT(PORTB_PCR18, 8);		// Seta bit 0 do MUX de PTB18, assim os bits de MUX serao 001
	
	PORTB_PCR19 = PORTB_PCR19 & 0xFFFFF8FF;	// Zera bits de MUX de PTB19
	SET_BIT(PORTB_PCR19, 8);		// Seta bit 0 do MUX de PTB19, assim os bits de MUX serao 001
	
	PORTD_PCR1 = PORTD_PCR1 & 0xFFFFF8FF;	// Zera bits de MUX de PTB18
	SET_BIT(PORTD_PCR1, 8); 		// Seta bit 0 do MUX de PTD1, assim os bits de MUX serao 001
	
	SET_BIT(GPIOB_PDDR, 18);		// Seta pino 18 do PORTB como saida 
	SET_BIT(GPIOB_PDDR, 19);		// Seta pino 19 do PORTB como saida 
	SET_BIT(GPIOD_PDDR, 1);			// Seta pino 1 do PORTD como saida 
	
	for( ; ; ) {	   
	
		//R-r-G-g-B-b-R--r-G--g-B--b-RG-rg-RB-rb-GB-gb-RG--rg-RB--rb-GB--gb-

		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		delay(SHORT_TIME);		// Espera um tempo
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		delay(SHORT_TIME);		// Espera um tempo
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		delay(SHORT_TIME);		// Espera um tempo
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 18);	// Toogle bit 18, LED vermelho em PTB18
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo

		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo
		delay(SHORT_TIME);		// Espera um tempo
		SET_BIT(GPIOB_PTOR, 19);	// Toogle bit 19, LED verde em PTB19
		SET_BIT(GPIOD_PTOR, 1);		// Toogle bit 1, LED azul em PTD1
		delay(SHORT_TIME);		// Espera um tempo
   }
}
