/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 2 :  Primeros pasos con Blue Pill
Ejercicio 6:
Implementar un código en C para configurar el reloj del sistema de la siguiente manera:
    ● Fuente de reloj:PLL
    ● Oscilador:HSE
    ● Factor multiplicador del PLL: 4
    ● Prescaler del HSE(PLLXTPRE):2
    ● Prescaler del AHB:2
    ● Prescaler del APB1:2
    ● Prescaler del APB2:4
 Indicar las frecuencias de reloj de:
    Los periféricos conectados al bus APB1--
    Los timers conectados al bus APB1
    Los periféricos conectados al bus APB2
    Los timers conectados al bus APB2
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


#define RCC_CR        (*((volatile uint32_t*)(RCC_BASE + 0x00)))
#define RCC_CFGR      (*((volatile uint32_t*)(RCC_BASE + 0x04)))
#define FLASH_ACR     (*((volatile uint32_t*)(0x40022000 + 0x00))) // Base address FLASH

int main(void)
{
    // Paso 1: Activar HSE (High-Speed External Oscillator)
    RCC_CR |= (1 << 16);                  // Activar HSE
    while (!(RCC_CR & (1 << 17)));        // Esperar a que HSE esté listo

    // Paso 2: Configurar el PLL
    RCC_CR &= ~(1 << 24);                 // Apagar el PLL antes de configurarlo
    RCC_CFGR |= (0b0111 << 18);           // Configurar multiplicador del PLL (4x)
    RCC_CFGR |= (1 << 16);                // Configurar HSE como fuente del PLL
    RCC_CR |= (1 << 24);                  // Activar el PLL
    while (!(RCC_CR & (1 << 25)));        // Esperar a que el PLL esté listo

    // Paso 3: Configurar latencia del flash
    FLASH_ACR |= (0b010 << 0);            // 2 wait states para el flash

    // Paso 4: Configurar los prescalers
    RCC_CFGR |= (0b100 << 4);             // Prescaler AHB = 2
    RCC_CFGR |= (0b101 << 8);             // Prescaler APB1 = 2
    RCC_CFGR |= (0b101 << 11);            // Prescaler APB2 = 4

    // Paso 5: Seleccionar PLL como fuente del sistema de reloj
    RCC_CFGR |= (0b10 << 0);              // Seleccionar PLL como SYSCLK
    while (!(RCC_CFGR & (0b10 << 2)));    // Esperar a que PLL sea SYSCLK
    /*
    Frecuencias calculadas:
    Suponiendo un HSE de 8 MHz:
    PLL: 8 MHz / 2 (PLLXTPRE) * 4 (PLLMUL) = 16 MHz
    AHB: 16 MHz / 2 = 8 MHz
    APB1: 8 MHz / 2 = 4 MHz
    APB2: 8 MHz / 4 = 2 MHz
    Timers APB1: 4 MHz * 2 = 8 MHz
    Timers APB2: 2 MHz * 2 = 4 MHz
    */

    while (1)
    {
        
    }

    return 0;
}
