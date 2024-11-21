/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 4 Indicar los valores de x e y (y sus direcciones de memoria) en cada sentencia del siguiente
fragmento de código (mencionar cómo se llega a la obtención de los mismos).
int x = 1, y = 2;
int *ptr;
ptr = &x;
y = *ptr;
*ptr = 0;

*/
#include <stdio.h>

int main(void)
{
    int x = 1, y = 2;
    int *ptr;
    ptr = &x; //dirección de memoria de puntero
    y = *ptr; // valor del puntero (x-> 1)
    *ptr = 0; // cambio el valor de puntero (x se convierte en 0)


    printf("%d \n",ptr);
    printf("%d \n",x);
    printf("%d \n",y);

    return 0;
}