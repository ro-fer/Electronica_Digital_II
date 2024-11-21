/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 10: 
Compilar y ejecutar el siguienye código

#include <stdio.h>

int main(void){
    char a;
    int b=0x12345678;
    short int c;
    printf("\n\nDireccion asignada para la variable a:\t%p\n",&a);
    printf("\n\nDireccion asignada para la variable b:\t%p\n",&b);
    printf("\n\nDireccion asignada para la variable c:\t%p\n",&c);
    return 0;
}

a) Analizar los valores de salida y marcar en el gráfico siguiente (esquema de la memoria) las ubicaciones asignadas a cada variable (las posiciones de memoria son decendientes de arriba hacia abajo).

b) Analizar la asignación de la memoria en el caso en que la declaración de las variables hubiera sido hecha en el siguiente orden:

char a;
short int c;
int b=0x12345678;

¿Se logra alguna mejora en la utilización de la memoria?

*/
#include <stdio.h>

int main(void){
    char a;
    short int c;
    int b=0x12345678;
    printf("\n\nDireccion asignada para la variable a:\t%p\n",&a);
    printf("\n\nDireccion asignada para la variable b:\t%p\n",&b);
    printf("\n\nDireccion asignada para la variable c:\t%p\n",&c);
    return 0;
}
/*
a)  Me da asi : 
Direccion asignada para la variable a:	0061FF1F


Direccion asignada para la variable b:	0061FF18


Direccion asignada para la variable c:	0061FF16

Entonces la visualizacion del esquema de memoria quedaria de la siguiente manera: 

+------+ 0061FF1F <-- Dirección de 'a' (1byte)
|  a   | 
+------+ 0061FFE al 0061FF1C Espacios no utilizados (son 3)
|      |
+------+ 0061FF1B <-- Parte de "b"
|      |
+------+ 0061FF1A <-- Parte de "b"
|      |
+------+ 0061FF19 <-- Parte de "b"
|      |
+------+ 0061FF18 <-- Inicio de "b" (4 bytes)
|  b   | 
+------+ 0061FF17 <-- Parte de "c"
|      |
+------+ 0061FF16 <-- Inicio de "c" (2 bytes)
|  c   | 
+------+ 0061FF15 <-- Dirección más baja


b) En este caso, obtengo lo siguiente 

Direccion asignada para la variable a:	0061FF1F


Direccion asignada para la variable b:	0061FF18


Direccion asignada para la variable c:	0061FF1C

--
Por lo cual, "c" se ha puesto en una direccion que esta inmediatamente despues de "b". Este nuevo orden respeta mejor la alineacion de los datos y permite que "c" se coloque en una direccion de memoria que es mas eficiente para el acceso en terminos de alineacion. 

*/