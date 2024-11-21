/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 2 : Crear un vector de enteros de 10 posiciones, recorrerlo e imprimir por pantalla cada uno de sus
valores. ¿Qué tamaño ocupa en memoria?
*/
#include <stdio.h>

int main(void)
{
    int t=10;
    int vector[t];
    int tam = sizeof(vector);
    //inicializo el vector con valores a partir de un for
    for (int i = 0; i < t; i++)
    {
        vector[i]=i+1;
    }
    printf("El vector es : \n");
    for (int i = 0; i < t; i++)
    {
        printf(" %d\n", vector[i]);
    }
    //El tamaño del vector en memoria
    printf("\n El valor del tamanio en memoria es: \n %d bytes", tam);
    return 0;
}
