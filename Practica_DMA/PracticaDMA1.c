/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 3 : DMA / DEVMAPURL
Ejercicio 1:
Implementar un código C de bajo nivel (sin utilizar las funciones de biblioteca), utilizando DMA, que genere una salida por el led de la placa de tal manera que muestre un patrón distinto al simple parpadeo.
*/

#include "map.h"
volatile devmap_t *const DEVMAP =(devmap_t *) 0x40000000;
volatile ctx_t *const CTX = ((ctx_t *) 0xE0000000);

typedef void(*interrupt_t)(void);
int  main(void);


const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,										// 0x0000_0000 Stack Pointer
	(interrupt_t) main,								// 0x0000_0004 Reset
};

uint32_t read_bit(volatile uint32_t *reg, uint32_t n) {
	return (*reg & (1 << n))>>n;
}

// One cycle first order sigma delta sin signal
uint32_t const data[256] = {
	0x00000000, 0x00002000, 0x00002000, 0x00000000, 0x00002000, 0x00000000, 0x00002000, 0x00000000,
	0x00002000, 0x00000000, 0x00002000, 0x00002000, 0x00000000, 0x00002000, 0x00002000, 0x00000000,
	0x00002000, 0x00002000, 0x00000000, 0x00002000, 0x00002000, 0x00002000, 0x00000000, 0x00002000,
	0x00002000, 0x00002000, 0x00000000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00000000,
	0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00000000,
	0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
	0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
	0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
	0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
	0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00000000, 0x00002000,
	0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
	0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00000000, 0x00002000, 0x00002000,
	0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00000000, 0x00002000, 0x00002000, 0x00002000,
	0x00002000, 0x00000000, 0x00002000, 0x00002000, 0x00002000, 0x00000000, 0x00002000, 0x00002000,
	0x00002000, 0x00000000, 0x00002000, 0x00002000, 0x00000000, 0x00002000, 0x00002000, 0x00000000,
	0x00002000, 0x00000000, 0x00002000, 0x00002000, 0x00000000, 0x00002000, 0x00000000, 0x00002000,
	0x00000000, 0x00002000, 0x00000000, 0x00002000, 0x00000000, 0x00002000, 0x00000000, 0x00000000,
	0x00002000, 0x00000000, 0x00002000, 0x00000000, 0x00000000, 0x00002000, 0x00000000, 0x00000000,
	0x00002000, 0x00000000, 0x00000000, 0x00002000, 0x00000000, 0x00000000, 0x00000000, 0x00002000,
	0x00000000, 0x00000000, 0x00000000, 0x00002000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00002000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00002000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00002000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00002000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00002000, 0x00000000,
	0x00000000, 0x00000000, 0x00002000, 0x00000000, 0x00000000, 0x00000000, 0x00002000, 0x00000000,
	0x00000000, 0x00000000, 0x00002000, 0x00000000, 0x00000000, 0x00002000, 0x00000000, 0x00002000,
	0x00000000, 0x00000000, 0x00002000, 0x00000000, 0x00002000, 0x00000000, 0x00002000, 0x00000000
};

int main(void)
{

	// Configuracion del reloj
	// PCLK code
	DEVMAP->RCC.REGs.CR   |= (1 << 16);						// Enable HSE
	while (!(DEVMAP->RCC.REGs.CR & (1 << 17)));				// Wait for HSE is locked

	DEVMAP->RCC.REGs.CR   &= ~(1 << 24);					// Disable PLL
	DEVMAP->RCC.REGs.CFGR |= (0b0111 << 18);				// Set PLLMULL to 9. Set PLL output clock to 72 Mhz
	DEVMAP->RCC.REGs.CFGR |=  (1 << 16);					// Select HSE as the PLL source clock
	DEVMAP->RCC.REGs.CR   |=  (1 << 24);					// Enable PLL
	while (!(DEVMAP->RCC.REGs.CR & (1 << 25)));				// Wait for PLL to lock

	DEVMAP->FLASH.REGs.ACR |= (0b010 << 0);					// Set FLASH WAIT STATE to 2
	DEVMAP->RCC.REGs.CFGR  |= (0b0000 << 4);				// Set AHB HPRE division to 1. Set AHB clock to 72 Mhz
	DEVMAP->RCC.REGs.CFGR  |= (0b100 << 8);					// Set APB1 PPRE1 division to 2. Set AHB clock to 36 Mhz

	DEVMAP->RCC.REGs.CFGR |= (0b10 << 0);					// Select PLL clock as the system clock
	while (!(DEVMAP->RCC.REGs.CFGR & (0b10 << 2)));			// Wait for PLL clock to be selected

	// DMA code
	DEVMAP->RCC.REGs.APB2ENR |= (1 << 4);					// Enable GPIOC clock.
	DEVMAP->RCC.REGs.APB1ENR |= (1 << 0);					// Enable TIM2 clock.
	DEVMAP->RCC.REGs.AHBENR  |= (1 << 0);					// Enable DMA1 clock.

	DEVMAP->GPIOs[GPIOC].REGs.CRL  = 0x33333333;			// Make low GPIOC output
	DEVMAP->GPIOs[GPIOC].REGs.CRH  = 0x33333333;			// Make high GPIOC output
//	DEVMAP->GPIOs[GPIOC].REGs.ODR ^= -1;

	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CNDTR = sizeof(data)/sizeof(uint32_t); // Transfer size
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CMAR	= (uint32_t) data;				 // Memory source address
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CPAR	= (uint32_t) &DEVMAP->GPIOs[GPIOC].REGs.ODR; // Peripheral destination address

	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR  = 0;				// Reset CCR
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR &= ~(1 << 14);	// Disable memory to memory transfer on DMA1 channel 2
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (0b11 << 12); // Set DMA priority to very high
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (0b10 << 10); // Set memory transfer size to 32-bits
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (0b10 << 8);	// Set peripheral transfer size to 32-bits
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 7);		// Enable memory increment mode
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR &= ~(1 << 6);		// Disable peripheral increment mode
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 5);		// Enable circular mode
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 4);		// Read from memory
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 2);		// Enable half transfer completed interrupt
	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 1);		// Enable transfer completed interrupt
	ENA_IRQ(IRQ_DMA1CHN2);									// Enable DMA1 Channel2 inturrupt on NVIC

	DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |= (1 << 0);		// Enable DMA

	ENA_IRQ(IRQ_TIM2);										// Enable TIM2 interrupt on NVIC
	DEVMAP->TIMs[TIM2].REGs.CR1  = 0x0000;					// Reset CR1 just in case
//	DEVMAP->TIMs[TIM2].REGs.CR1  |= (1 << 4);				// Down counter mode
	DEVMAP->TIMs[TIM2].REGs.PSC   = (72e6/8)/(sizeof(data)/sizeof(data[0]))-1;	// fCK_PSC / (PSC[15:0] + 1)
	DEVMAP->TIMs[TIM2].REGs.ARR   = 8-1;
	DEVMAP->TIMs[TIM2].REGs.DIER |= (1 << 14);				// Trigger DMA request enable
	DEVMAP->TIMs[TIM2].REGs.DIER |= (1 <<  8);				// Update DMA request enable
//	DEVMAP->TIMs[TIM2].REGs.DIER |= (1 <<  6);				// Enable interrupt
//	DEVMAP->TIMs[TIM2].REGs.DIER |= (1 <<  0);				// Update interrupt enable

	DEVMAP->TIMs[TIM2].REGs.CR1  |= (1 << 0);				// Finally enable TIM1 module


	for(;;);

	return 0;
}