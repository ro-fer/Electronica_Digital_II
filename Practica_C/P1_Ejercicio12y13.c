/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 12: 
Dado el siguiente tipo de datos y teniendo en cuenta que la dirección del miembro a es
 0x00546334, cuál sería la dirección de b?
 union aux {
 int a;
 char b;
 }*/


/*
Rta:
Como se dijo en el ejercicio anterior, en una union todos los miembros comparten ubicación, por lo cual, la dirección de b sería la misma, osea, 0x00546334
*/

/*----*/
/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 13: 
 Cuál es el tamaño de la union del punto anterior?
*/

/*
Rta:
La union tiene el tamaño del miembro mas grande, en este caso es "a" que es un dato tipo int que serian 4 bits
*/