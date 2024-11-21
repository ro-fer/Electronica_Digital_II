/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 7:

Compilar el siguiente código y explicar las direcciones obtenidas en la corrida.
int main(void){
int a = 0x12345678;
short int b = 0xABCD;
char c = 'a';
int * ptr_a = &a;
short int * ptr_b = &b;
char * ptr_c = &c;
printf("\nValor de ptr_a:\t\t %p\n", ptr_a);
printf("Valor de ptr_a + 1:\t %p\n", ++ptr_a);
printf("\nValor de ptr_b:\t\t %p\n", ptr_b);
printf("Valor de ptr_b + 1:\t %p\n", ++ptr_b);
printf("\nValor de ptr_c:\t\t %p\n", ptr_c);
printf("Valor de ptr_c + 1:\t %p\n", ++ptr_c);
}


*/
#include <stdio.h>

int main(void){
    int a = 0x12345678; // El int tiene 4 bytes
    short int b = 0xABCD;// El short tiene 2 bytes
    char c = 'a';//El char tiene 1 bytes
    int * ptr_a = &a;
    short int * ptr_b = &b;
    char * ptr_c = &c;
    printf("\nValor de ptr_a:\t\t %p\n", ptr_a); 
    printf("Valor de ptr_a + 1:\t %p\n", ++ptr_a);
    /*
    Aca tengo la direccion (Ej:0061FF10) y como tiene 4 bits y se mueve cuatro bytes por lo cual ahora tendria : 0061FF14
    */ 
    printf("\nValor de ptr_b:\t\t %p\n", ptr_b);
    printf("Valor de ptr_b + 1:\t %p\n", ++ptr_b);
    /*
    Aca tengo la direccion (Ej:0061FF0E) y como tiene 2 bits y se mueve 2 bytes por lo cual ahora tendria : 0061FF10
    */ 
    printf("\nValor de ptr_c:\t\t %p\n", ptr_c);
    printf("Valor de ptr_c + 1:\t %p\n", ++ptr_c);
    /*
    Aca tengo la direccion (Ej:0061FF0D) y como tiene 1 bits y se mueve 1 bytes por lo cual ahora tendria : 0061FF0E
    */ 
}
