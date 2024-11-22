/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 3 : DMA / DEVMAPURL
Ejercicio 3:
Repetir el ejercicio 1 utilizando la interrupción de transmisión de la USART1
*/

#include "map.h"
volatile devmap_t *const DEVMAP = (devmap_t *) 0x40000000;
volatile ctx_t *const CTX = ((ctx_t *) 0xE0000000);

typedef void(*interrupt_t)(void);

volatile int t = 0;
void SYSTICK_handler(void){t++;}

void delay_ms(int ms) {
    CTX->SYSTICK.REGs.CSR |= (1<<1); //TICKINT on (interrupciones)
    while(t<ms);
    CTX->SYSTICK.REGs.CSR &= ~(1<<1);//TICKINT off
    t=0;
}


#define TX_BUFFER_SIZE 256
// Buffer circular para transmisión
volatile char tx_buffer[TX_BUFFER_SIZE];
volatile uint16_t tx_head = 0;
volatile uint16_t tx_tail = 0;

// Función para enviar un string por UART
void UART_SendString(const char *str) {
    while (*str) {
        uint16_t next_head = (tx_head + 1) % TX_BUFFER_SIZE;

        // Esperar si el buffer está lleno
        while (next_head == tx_tail);

        // Agregar carácter al buffer
        tx_buffer[tx_head] = *str++;
        tx_head = next_head;
    }

    // Habilitar interrupción TXE para iniciar transmisión
    DEVMAP->USART1.REGs.CR1 |= (1 << 7);
}

void USART1_handler(void) {
	if (DEVMAP->USART1.REGs.SR & (1 << 7)) { // TXE está listo
        if (tx_tail != tx_head) {  // Si hay datos en el buffer
            DEVMAP->USART1.REGs.DR = tx_buffer[tx_tail];
            tx_tail = (tx_tail + 1) % TX_BUFFER_SIZE;
        } else {
            // Si no hay más datos, deshabilitar interrupción TXE
            DEVMAP->USART1.REGs.CR1 &= ~(1 << 7);
        }
    }
}



void systick_config(){
    CTX->SYSTICK.REGs.RVR = CTX->SYSTICK.REGs.CALIB & 0xFFFFFF; //Uso el Syst calib para que el time reset ;
    CTX->SYSTICK.REGs.CSR = 0; 
    CTX->SYSTICK.REGs.CSR |= (1	<< 2);                 // Habilito el CLCKSOURCE. Si pongo 1: reloj del procesador - 0: reloj externo
	CTX->SYSTICK.REGs.CSR |= (1 << 1);   // habilito interrupcion (1)
    CTX->SYSTICK.REGs.CSR |= (1 << 0);                 // 1 en el ENABLE --> habilito el systick
    CTX->SYSTICK.REGs.CVR = 0;                       // Valor de la cuenta actual. Se puede leer y escribir. Una escritura con cualquier valor resetea a 0. and also clears the COUNTFLAG bit in the STK_CSR register to 0
}

int main(void)
{
	DEVMAP->RCC.REGs.APB2ENR |= (1 << 14);					// Enable USART1 clock.
	DEVMAP->RCC.REGs.APB2ENR |= (1 << 2);					// Enable GPIOA clock.

	DEVMAP->USART1.REGs.CR1 |= (1 << 3);					// Transmitter enable
	DEVMAP->USART1.REGs.CR1 |= (1 << 13);					// Enable USART1

	DEVMAP->USART1.REGs.BRR = 833;					// Set BRR to (72 Mhz/9600 bdps) = 7500

	ENA_IRQ(IRQ_USART1);									// Enable USART1 NVIC IRQ

	DEVMAP->GPIOs[GPIOA].REGs.CRH &= ~(0xFF0); // Limpio 8 bits. (PA9 y PA10)
	DEVMAP->GPIOs[GPIOA].REGs.CRH |= 0x400; // PA10 como entrada flotante
	DEVMAP->GPIOs[GPIOA].REGs.CRH |= 0xB0; // PA9 como salida alternativa push/pull

	systick_config();

	while(1) {
		UART_SendString("Hola!\n");
		delay_ms(1000);
	};

	return 0;
}

const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
	0,														// 0x0000_0008
	0,														// 0x0000_000C
	0,														// 0x0000_0010
	0,														// 0x0000_0014
	0,														// 0x0000_0018
	0,														// 0x0000_001C
	0,														// 0x0000_0020
	0,														// 0x0000_0024
	0,														// 0x0000_0028
	0,														// 0x0000_002C
	0,														// 0x0000_0030
	0,														// 0x0000_0034
	0,														// 0x0000_0038
    SYSTICK_handler,										// 0x0000_003C SYSTICK
	0,														// 0x0000_0040
	0,														// 0x0000_0044
	0,														// 0x0000_0048
	0,														// 0x0000_004C
	0,														// 0x0000_0050
	0,														// 0x0000_0054
	0,														// 0x0000_0058
	0,														// 0x0000_005C
	0,														// 0x0000_0060
	0,														// 0x0000_0064
	0,														// 0x0000_0068
	0,														// 0x0000_006C
	0,														// 0x0000_0070
	0,														// 0x0000_0074
	0,														// 0x0000_0078
	0,														// 0x0000_007C
	0,														// 0x0000_0080
	0,														// 0x0000_0084
	0,														// 0x0000_0088
	0,														// 0x0000_008C
	0,														// 0x0000_0090
	0,														// 0x0000_0094
	0,														// 0x0000_0098
	0,														// 0x0000_009C
	0,														// 0x0000_00A0
	0,														// 0x0000_00A4
	0,														// 0x0000_00A8
	0,														// 0x0000_00AC
	0,														// 0x0000_00B0
	0,														// 0x0000_00B4
	0,														// 0x0000_00B8
	0,														// 0x0000_00BC
	0,														// 0x0000_00C0
	0,														// 0x0000_00C4
	0,														// 0x0000_00C8
	0,														// 0x0000_00CC
	0,														// 0x0000_00D0
	USART1_handler,											// 0x0000_00D4
};