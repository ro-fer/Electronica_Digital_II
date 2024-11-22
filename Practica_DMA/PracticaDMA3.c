/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 3 : DMA / DEVMAPURL
Ejercicio 3:
Implementar los ejercicios 5 y 8 de la guía “Primeros pasos con Blue Pill” utilizando la estructura DEVMAP.
*/

#include "map.h"


volatile devmap_t *const DEVMAP = (devmap_t *)0x40000000;

typedef void (*interrupt_t)(void);
const interrupt_t vector_table[256] __attribute__((section(".vtab"))) = {
    (interrupt_t)(0x20005000), 
    (interrupt_t)main          
};


volatile int flag = 0;


void handler_exti0(void) {
    
    DEVMAP->EXTI.REGs.PR |= (1 << 0); 
    flag = 1; 
}


int main(void) {
    
    DEVMAP->RCC.REGs.APB2ENR |= (1 << 2) | (1 << 4) | (1 << 0);

    
    DEVMAP->GPIOs[GPIOC].REGs.CRH &= ~(0xF << 20); 
    DEVMAP->GPIOs[GPIOC].REGs.CRH |= (0x2 << 20);  
    DEVMAP->GPIOs[GPIOC].REGs.ODR &= ~(1 << 13);   

    
    DEVMAP->GPIOs[GPIOA].REGs.CRL &= ~(0xF << 0);  
    DEVMAP->GPIOs[GPIOA].REGs.CRL |= (0x8 << 0);   
    DEVMAP->GPIOs[GPIOA].REGs.ODR &= ~(1 << 0);    

    
    DEVMAP->AFIO.REGs.EXTICR[0] &= ~(0xF << 0);    
    DEVMAP->EXTI.REGs.IMR |= (1 << 0);             
    DEVMAP->EXTI.REGs.RTSR |= (1 << 0);            
    DEVMAP->EXTI.REGs.FTSR &= ~(1 << 0);           
    ENA_IRQ(IRQ_EXTI0);                            

    // Configurar DMA para salida en GPIOC (Ejercicio 5)
    uint32_t data[] = {0x00000000, 0xFFFFFFFF};    
    DEVMAP->RCC.REGs.AHBENR |= (1 << 0);           
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CNDTR = sizeof(data) / sizeof(uint32_t); 
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CMAR = (uint32_t)data; 
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CPAR = (uint32_t)&DEVMAP->GPIOs[GPIOC].REGs.ODR; 
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |= (0b10 << 8) | (1 << 7) | (1 << 4) | (1 << 0); 

    // Configurar TIM2 para disparar DMA
    DEVMAP->RCC.REGs.APB1ENR |= (1 << 0);          
    DEVMAP->TIMs[TIM2].REGs.PSC = (72e6 / 8) - 1;  
    DEVMAP->TIMs[TIM2].REGs.ARR = 8 - 1;           
    DEVMAP->TIMs[TIM2].REGs.DIER |= (1 << 8);      
    DEVMAP->TIMs[TIM2].REGs.CR1 |= (1 << 0);       

    while (1) {
        if (flag) {
            DEVMAP->GPIOs[GPIOC].REGs.ODR ^= (1 << 13); 
            for (volatile int i = 0; i < 500000; i++); 
            flag = 0; 
        }
    }

    return 0;
}
