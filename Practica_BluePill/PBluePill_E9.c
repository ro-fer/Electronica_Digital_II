/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 2 :  Primeros pasos con Blue Pill
Ejercicio 9 : 
Implementar un código C de bajo nivel que realice el parpadeo de un led a través del SysTick utilizando interrupciones.

*/

#define RCC_BASE            0x40021000
#define GPIOC_BASE          0x40011000
#define SYST_BASE     0XE000E000

#define RCC_APB2ENR 		(*((volatile uint32_t*)(RCC_BASE + 0x18)))

#define GPIOC_CRL           (*((volatile uint32_t*)(GPIOC_BASE + 0x00)))
#define GPIOC_CRH           (*((volatile uint32_t*)(GPIOC_BASE + 0x04)))
#define GPIOC_ODR           (*((volatile uint32_t*)(GPIOC_BASE + 0x0C)))

//SysTick registers
#define SYST_CSR (*(volatile uint32_t *)(SYST_BASE + 0x10)) //Control de status
#define SYST_RVR (*(volatile uint32_t *)(SYST_BASE + 0x14)) //Recarga de datos
#define SYST_CVR (*(volatile uint32_t *)(SYST_BASE + 0x18)) //Valor actual 
#define SYST_CALIB (*(volatile uint32_t *)(SYST_BASE + 0x1C)) //Calibracion

// Tipo de datos 
typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

volatile int cont=0; // Contador
void handler_systick(void){cont++;} // Manejo de interrupciones del Systick

int main(void)

{


RCC_APB2ENR |= (1<<4); // Enable GPIOC clock: El bit 4 es GPIOC clock 
RCC_APB2ENR |= (1<<2); // Enable GPIOA clock: El bit 2 es GPIOA clock 
GPIOC_CRL = 0X33333333; // Configuro GPIO CRL (Configuration Register Low). 3 = 0011
GPIOC_CRH = 0X33333333;//  Configuro GPIO CRH (Configuration Register High). 3 = 0011

volatile int TENMS; 

SYST_CSR = 0x00000003; //Habilito el SysTick y el TICKINT
TENMS = SYST_CALIB;  // Tomo el valor del Syst Calib
TENMS = TENMS & 0xFFFFFF;// Me quedo sólo con los 24 primeros bits 
SYST_RVR =TENMS; //Seteo el valor de Reload con el valor de TENMS

SYST_CVR=0; //Reseteo SYST_CVR
cont=0;
    

     while (1) {
        
        if (cont == 100){
			GPIOC_ODR ^= (1<<13);
            cont=0;
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
	handler_systick,										// 0x0000_003C SYSTICK
};
