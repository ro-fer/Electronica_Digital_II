/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 6:
Se tiene la siguiente declaración:
int x[5];
int *ptr;
a) ¿Cómo haría para que el puntero ptr apunte a la primera posición del vector x?
b) ¿Recorrer el vector completo utilizando incrementos en el puntero ptr?
c) Realizar un printf del puntero ptr para cada incremento del punto b. Indicar por qué entre
valor y valor existe un salto en la secuencia.
d) Si en lugar de tener un vector de enteros (int) en el ejemplo utilizáramos un vector de chars, el
salto entre valores consecutivos del punto c cambiaría? Corroborarlo modificando lo que
corresponda del código.

*/
#include <stdio.h>
int main()
{
    int x[5];
    int *ptr;
    
    int i, vector[3] = {1, 2, 3};
    int *p, *p1;
    p = vector;
    
    printf("%i\t", *(p + 1));
    printf("%i\t", vector[1]);
    
    return 0;
}
