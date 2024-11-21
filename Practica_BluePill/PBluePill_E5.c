/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 2 :  Primeros pasos con Blue Pill
Ejercicio 5 :  Repetir el punto anterior pero en lugar de usar un cable incluir un botón. Tener encuentalas resistencias de pull-up y pull-down del pin de entrada.

*/


#define RCC_BASE            0x40021000
#define GPIOA_BASE          0x40010800
#define GPIOC_BASE          0x40011000

#define RCC_APB2ENR 		(*((volatile uint32_t*)(RCC_BASE + 0x18)))

#define GPIOC_CRL           (*((volatile uint32_t*)(GPIOC_BASE + 0x00)))
#define GPIOC_CRH           (*((volatile uint32_t*)(GPIOC_BASE + 0x04)))
#define GPIOC_ODR           (*((volatile uint32_t*)(GPIOC_BASE + 0x0C)))

#define GPIOA_CRL           (*((volatile uint32_t*)(GPIOC_BASE + 0x00)))
#define GPIOA_CRH           (*((volatile uint32_t*)(GPIOC_BASE + 0x04)))
#define GPIOA_IDR           (*((volatile uint32_t*)(GPIOC_BASE + 0x08)))

// Tipo de datos 
typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

// Voy a encender el LED que se encuentra en la salida PC13 leyendo la entrada del pin PA7

int main(void)

{
    RCC_APB2ENR |= (1<<4); // Enable GPIOC clock: El bit 4 es GPIOC clock 
    RCC_APB2ENR |= (1<<2); // Enable GPIOA clock: El bit 2 es GPIOA clock 
    GPIOC_CRL = 0X33333333; // Configuro GPIO CRL (Configuration Register Low). 3 = 0011
    GPIOC_CRH = 0X33333333;//  Configuro GPIO CRH (Configuration Register High). 3 = 0011
    GPIOC_ODR= 0x00000000; //   Configuro GPIO ODR (Output Data Register): Reseteo
    volatile int i;

     while (1) {
        
        if (GPIOA_IDR & (1 << 7)) {// Leer el estado del pin PA7 
            // Si el pin está en 1 encender el LED
            GPIOC_ODR |= (1 << 13);
        } else {
            // Si el pin está en 0 apagar el LED
            GPIOC_ODR &= ~(1 << 13);
        }
     }
 
	return 0;
}

#define SRAM_SIZE ((uint32_t) 0x00005000) // Tamaño memoria SRAM
#define SRAM_BASE ((uint32_t) 0x20000000) // Dirección base de la memoria SRAM
#define STACKINIT ((interrupt_t)(SRAM_BASE+SRAM_SIZE))

typedef void(*interrupt_t)(void);
const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
};