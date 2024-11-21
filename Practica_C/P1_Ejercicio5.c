/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 5:
Codificar un procedimiento que intercambie dos enteros, por medio de la utilización de
punteros. Verificarlo mediante el llamado del mismo desde un código externo con impresión del
resultado (valores antes y después del intercambio).

*/
#include <stdio.h>

void swap(int *a, int *b){
    int punt_a=*a, punt_b=*b;
    *a=punt_b;
    *b=punt_a;
}
void main(){
    int x = 1, y = 2;
    printf("Valores originales:\tx = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("Valores nuevos:\t\tx = %d, y = %d\n", x, y);
}
