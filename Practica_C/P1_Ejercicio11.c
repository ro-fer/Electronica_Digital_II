/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 11: 
 Explicar la diferencia entre un union y un struct
*/


/*
Rta:
Una struct  permite agrupar diferentes variables bajo un mismo nombre. Cada miembro tiene su propia ubicación en memoria. Por lo cual, la memoria total es la suma de las memorias de cada elemento. Tambien, por esto, es que cada miembro de la estructura es accesible simultáneamente.

En cambio, una union que tambien agrupa diferentes variables bajo un mismo nombre todos los miembros comparten la misma ubicación en memoria. Por lo cual, el tamaño de la memoria total usado por una union es igual es igual al tamaño del miembro más grande. Esto significa que solo uno de los miembros puede contener un valor válido en un momento dado.

En conclusión, la principal diferencia es como se almacenan los datos y por ende, como es que se puede acceder a cada miembro que puede contener la union o la struct
 */