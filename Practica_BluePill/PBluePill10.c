/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 2 :  Primeros pasos con Blue Pill
Ejercicio 10:
Implementar en C de bajo nivel una función delay a la que se le pase como argumento el tiempo de retardo en ms, utilizando el SysTick y la interrupción asociada a él.
*/

typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

#define SRAM_SIZE ((uint32_t) 0x00005000) // El tamaño de la SRAM
#define SRAM_BASE ((uint32_t) 0x20000000) //donde esta la SRAM
#define STACKINIT ((uint32_t)(SRAM_BASE + SRAM_SIZE)) // El STACK inicia en sram size + sram base

//Direcciones base de puertos
#define GPIO_PORT_A_BASE 0x40010800 //Direccion base del puerto A 
#define GPIO_PORT_B_BASE 0x40010C00 //Direccion base del puerto B
#define GPIO_PORT_C_BASE 0x40011000 //Direccion base del puerto C

//Clock registers necesito habilitar algunos relojes pa usar los GPIOS
#define RCC_BASE 0x40021000 // direccion base del reloj RCC
#define APB2ENR_OFFSET 0x18 //offset del registro APB2ENR pa configurar el base del periferico

//Systick shit
#define SYSTICK_BASE     0xE000E010 // Dirección base del temporizador SysTick
#define CTRL_OFFSET      0x00
#define LOAD_OFFSET      0x04
#define VAL_OFFSET       0x08
#define CAL_OFFSET       0x0C
#define SYSTICK_CTRL     (SYSTICK_BASE + CTRL_OFFSET) // Registro de control de SysTick
#define SYSTICK_LOAD     (SYSTICK_BASE + LOAD_OFFSET) // Registro de carga de SysTick
#define SYSTICK_VAL      (SYSTICK_BASE + VAL_OFFSET) // Registro de valor actual de SysTick
#define SYSTICK_CAL      (SYSTICK_BASE + CAL_OFFSET)

//Todos los offsets de los registros de GPIO
#define CRL_OFFSET 0x00
#define CRH_OFFSET 0x04
#define IDR_OFFSET 0x08
#define BSRRR_OFFSET 0x10
#define ODR_OFFSET 0x0C
#define BRR_OFFSET 0x14
#define LCKR_OFFSET 0x18

//Todos los offsets de los registros de clocks
#define RCC_CR          0x00
#define RCC_CFGR        0x04
#define RCC_CIR         0x08
#define RCC_APB2RSTR    0x0C
#define RCC_APB1RSTR    0x10
#define RCC_AHBENR      0x14
#define RCC_APB2ENR     0x18
#define RCC_APB1ENR     0x1C

//INTERRUPCIONES
#define NVIC_BASE 0xE000E100 //direccion base del NVIC
#define ISER0_OFFSET 0x00 //offset del registro ISER0
#define ISER1_OFFSET 0x04 //offset del registro ISER1
//EXTI REGISTERS
#define EXTI_BASE 0x40010400
#define IMR_OFFSET      0x00    //interrupt mask manager
#define EMR_OFFSET      0x04    // Event Task Manager
#define RTSR_OFFSET     0x08    //Rising Trigger Selection Register
#define FTSR_OFFSET     0x0C    //Falling Trigger Selection Register
#define SWIER_OFFSET    0x10    //Software Interrupt Event Register
#define PR_OFFSET       0x14    //Pending Register
#define AFIO_BASE       0x40010000
#define EXTICR1_OFFSET 0x08
#define EXTICR2_OFFSET 0x0C
#define EXTICR3_OFFSET 0x10

//Creo la variable global i
volatile int i=0;
int main(void);
void handler_systick(void){
    i++;
};
void handler_adc1_2(void){};
void handler_usart1(void){};
void handler_exti0(void);

//Funcion de delay

void delay_ms(int ms) {
    int Recarga_Systick = *(int*)(SYSTICK_LOAD); //Guardo el valor de lo que cuenta el systick
    int Clock_Systick = 8E6; // Guardo el valor de la fuente del clock del systick, en este caso es el del procesador -> 8MHz
    ms= ((ms)/ (((Recarga_Systick)/Clock_Systick)*1000)); 
    /*Como quiero dividir "ms" por el valor en ms y la recarga/clock me da en segundos, multiplico por 1000 y guardo todo en la variable que le pase. Necesito tener "ms" en seg por eso lo convierto*/
    i=0;
    while (i<ms);
}

/*
void delay_ms(int ms) {
    for (int i = 0; i < ms * 1000; i++) {
        __asm__("nop"); // No-operation, simplemente espera
    }
}
*/

typedef void(*interrupt_t)(void);
const interrupt_t vector_table[] __attribute__ ((section(".vtab"))) = {
	(interrupt_t)STACKINIT,												// 0x0000_0000 Stack Pointer
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
	0,														// 0x0000_0040
	0,														// 0x0000_0044
	0,														// 0x0000_0048
	0,														// 0x0000_004C
	0,														// 0x0000_0050
	0,														// 0x0000_0054
	handler_exti0,											// 0x0000_0058
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
	handler_adc1_2,											// 0x0000_0088
	0,														// 0x0000_008C
	0,														// 0x0000_0090
	0,														// 0x0000_0094
	0,														// 0x0000_0098
	0,														// 0x0000_009C
	0,														// 0x0000_00A0
	0,														// 0x0000_00A4
	0,														// 0x0000_00A8
	0,														// 0x0000_00AC
	0,														// 0x0000_00B0 TIM2
	0,														// 0x0000_00B4
	0,														// 0x0000_00B8
	0,														// 0x0000_00BC
	0,														// 0x0000_00C0
	0,														// 0x0000_00C4
	0,														// 0x0000_00C8
	0,														// 0x0000_00CC
	0,														// 0x0000_00D0
	handler_usart1,											// 0x0000_00D4 USART1
	0,														// 0x0000_00D8
	0,														// 0x0000_00DC
};

volatile int flag=0;

    void handler_exti0(void){
        int *EXTI_PR =(int*)(EXTI_BASE + PR_OFFSET);
        flag = 1;
        *EXTI_PR = (1<<0);
    }


int main(void){
    //Primero que nada hay que habilitar los relojes de los perifericos dentro del RCC_APB2ENR (GPIOx) que quieras usar
    
    int *RCC_APB2ENR_clocks = (int*)(RCC_BASE + APB2ENR_OFFSET); //Creo un puntero que apunta a la direccion de los clocks de los GPIOS
    // Tengo que habilitar los relojes de los puertos de GPIOS que me interese utilizar
    *RCC_APB2ENR_clocks |= (1 << 0) | (1 << 2) | (1 << 4); // AFIO, GPIOA, GPIOC
    //Ahora tengo que configurar los pines del puerto que voy a usar como entrada/salida y con que configuracion.
    // Si voy a usar los puertos del 0 al 7....
    int *GPIOC_LowPorts = (int*)(GPIO_PORT_C_BASE + CRL_OFFSET); // puntero los puertos del 0 al 7 
    //Si voy a usar los pines del 8 al 15...
   // Configurar PC13 como salida push-pull a 50MHz
	int *GPIOC_HighPorts = (int*)(GPIO_PORT_C_BASE + CRH_OFFSET); // Puntero a CRH (pines 8-15)
	*GPIOC_HighPorts &= ~(0xF << 20);  // Limpiar los bits de configuración de PC13 (bits 20-23)
	*GPIOC_HighPorts |= (0x3 << 20);   // Configurar PC13 como salida push-pull a 50MHz

    int *GPIO_PORT_A_ODR = (int*)(GPIO_PORT_A_BASE + ODR_OFFSET);
    //(*GPIO_PORT_A_ODR) = (0<<0); // le ponemos un cero para q sea pull down en la posicion del pin q quiero (0)
    (*GPIO_PORT_A_ODR) &= ~(1 << 0);   // Pull-down activado (ODR = 0)
    //Seteo el ODR del registro C
    volatile int *GPIO_PORT_C_ODR = (int*)(GPIO_PORT_C_BASE + ODR_OFFSET);
    (*GPIO_PORT_C_ODR) = (0<<13);

    
    //Systick configs de punteros
    //Inicializo punteros a los registros de SYSTICK previamente definidos.
    volatile int *SYSTICK_LOAD_ptr = (int*)(SYSTICK_LOAD); 
    volatile int *SYSTICK_VAL_ptr = (int*)(SYSTICK_VAL); 
    volatile int *SYSTICK_CTRL_ptr = (int*)(SYSTICK_CTRL); 
    volatile int *SYSTICK_CAL_ptr = (int*)(SYSTICK_CAL); 

    //Inicializo y configuro el SysTick
    *SYSTICK_LOAD_ptr = 8E6 ; //establesco el valor de la recarga de systick
 	*SYSTICK_CTRL_ptr &= ~(0xF << 0);
    *SYSTICK_CTRL_ptr |= (1<<2);            // Elijo Reloj Interno
   	*SYSTICK_CTRL_ptr |= (1<<1);            // Habilito Interrupciones
    *SYSTICK_CTRL_ptr |= (1<<0);
    //*SYSTICK_VAL_ptr = 0;                   // Reinicia el valor actual de SysTick


    delay_ms(5000);
    *GPIO_PORT_C_ODR |= (1<<13);
    delay_ms(1000);
    *GPIO_PORT_C_ODR = (0<<13);
}