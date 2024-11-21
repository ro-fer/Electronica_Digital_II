/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 3: Crear una función que realice la suma de dos enteros. Utilizarla para imprimir por pantalla la
suma de dos enteros predefinidos.
*/
#include <stdio.h>

int sumar_enteros (int num1, int num2)
{
    int suma=num1+num2;
    return suma;
}
int main(void)
{
    int num1,num2,suma;
    num1=10;
    num2=40;
    suma = sumar_enteros(num1,num2);
    printf("\n *.%d + %d = %d",num1,num2,suma);
    return 0;
}

