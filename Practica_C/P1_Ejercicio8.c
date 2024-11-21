/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 8:
La siguiente función calcula el largo de una cadena de caracteres. Reformularla para que la funcionalidad sea resuelta por medio del uso de un puntero auxiliar en lugar de la variable n.

int strlen(char*s){
int n;
for(n=:*s!='\0';s++)
n++;
return n;
}
*/
#include <stdio.h>

int strlen(char *s){
    char *p=s; // puntero aux que apunta al inicio de la cadena
    while(*p!='\0'){
        p++; // avanzo el puntero aux hasta el final de la cadena
    }
    return p-s; // la long de la cadena es la diferencia entre punteros
}

int main()
{
    char str[]="Hola mundo";
    int longitud = strlen(str);
    printf("La longitud de la cadena es: %d\n", longitud);
    return 0;
}
