/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 1 : Armar un código en C para mostrar por pantalla los diferentes tamaños de los tipos: char, short, int, long, float y double
*/
#include <stdio.h>


int main(void)
{
    char var_char;
    short var_short;
    int var_int;
    long var_long;
    float var_float;
    double var_double;
    printf("El tamanio de los diferentes tipos de variables son: \n ");
    printf("Char : %d\n",sizeof(var_char)); // 1
    printf("Short : %d\n",sizeof(var_short)); // 2
    printf("Int : %d\n",sizeof(var_int)); // 4
    printf("Long : %d\n",sizeof(var_long)); // 4
    printf("Float : %d\n",sizeof(var_float)); // 4
    printf("Double : %d\n",sizeof(var_double)); // 8 

    return 0;
}
