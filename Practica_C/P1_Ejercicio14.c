/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 14: 
 Dado el siguiente código, ¿qué se mostraría por pantalla al correrlo?

#include <stdio.h>
union aux {
    int a;
    char b;
 };
 int main(void){
    union aux var;
    var.a = 77;
    printf("a: %d\n", var.a);
    printf("b: %c\n", var.b);
 }
*/
#include <stdio.h>
union aux {
    int a;
    char b;
 };
 int main(void){
    union aux var;
    var.a = 77;
    printf("a: %d\n", var.a);
    printf("b: %c\n", var.b);
 }

/*
Rta:
Primero se obtiene 77, que es el valor de a
Luego se obtiene M que es el valor de 77 en codigo ASCII
*/