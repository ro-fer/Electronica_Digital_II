/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 2 :  Primeros pasos con Blue Pill
Ejercicio 2 :  Implementar un código C de bajo nivel para que el led se encienda y se apague (parpadee) de acuerdo a un retardo que también deberán crear.

*/

// Defino direcciones de memoria 
#define RCC_BASE            0x40021000
#define GPIOC_BASE          0x40011000

#define RCC_APB2ENR 		(*((volatile uint32_t*)(RCC_BASE + 0x18)))
#define GPIOC_CRL           (*((volatile uint32_t*)(GPIOC_BASE + 0x00)))
#define GPIOC_CRH           (*((volatile uint32_t*)(GPIOC_BASE + 0x04)))
#define GPIOC_ODR           (*((volatile uint32_t*)(GPIOC_BASE + 0x0C)))

// Tipo de datos 
typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

void delay(void);

int main(void)
{
    // Esto es para el port C
    RCC_APB2ENR |= (1<<4); // 1)Enable GPIOC clock: El bit 4 es GPIOC clock 
    GPIOC_CRL = 0X33333333; // 2) Configuro GPIO CRL (Configuration Register Low). 3 = 0011
    GPIOC_CRH = 0X33333333;// 3) Configuro GPIO CRH (Configuration Register High). 3 = 0011
    GPIOC_ODR= 0x00000000; // 4)  Configuro GPIO ODR (Output Data Register): Reseteo
    GPIOC_ODR = 0x02000000; // Prendo pin 13
    // 4) Configuro GPIO ODR (Output Data Register). 
    // Reseteo 
    // Prendo pin 13
    volatile int i;
    while(1){
        GPIOC_ODR ^= (1<<13); // Cambio el estado del pin 13
		delay(); // Implemento un retardo
	}
	return 0;
}


void delay(void) // Función para producir un retardo
{
    volatile int i, t; 
    t=100000; // tiempo de retardo
    for(i=0; i<t; i++){}
};

#define SRAM_SIZE ((uint32_t) 0x00005000) // Tamaño memoria SRAM
#define SRAM_BASE ((uint32_t) 0x20000000) // Dirección base de la memoria SRAM
#define STACKINIT ((interrupt_t)(SRAM_BASE+SRAM_SIZE))

typedef void(*interrupt_t)(void);
const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
};
