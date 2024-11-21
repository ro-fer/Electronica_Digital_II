/*
Electronica Digital II
2do Cuatrimestre 2024
Fernandez, Rocio 
Guía 1 : Lenguaje C
Ejercicio 9:
Puntero a una estructura. Se tiene el siguiente extracto de código

struct pru_struct
{
    char id1;
    char id2;
    char id3[10];
    char *nombre;
    char *domicilio;
    int edad;
    int varios;
};

int main()
{
    int i;
    int tmp;
    struct pru_struct empleados = 
    {
        'B',
        'C',
        "Sensible",
        "Pedro",
        "Av. Carlos Calvo 1234",
        23,
        68,
    };
    showinfo(&empleados);
}

----
Luego de compilado se obtiene la siguiente salida:
Valores iniciales de la estructura:
id1: B      id2:C       id3:Sencible        Nombre: Pedro       Direccion: Av Carlos Calvo 1234     Edad:23     Varios:68
Direccion de la estructura: 0x0022FEF4
Direccion del miembro id1:  0x0022FEF4 (offset: 0bytes)
Direccion del miembro id2:  0x0022FEF5 (offset: 1bytes)
Direccion del miembro id3:  0x0022FEF6 (offset: 2bytes)
Direccion del miembro nombre:  0x0022FF00 (offset: 12bytes)
Direccion del miembro domicilio:  0x0022FF04 (offset: 16bytes)
Direccion del miembro edad:  0x0022FF08 (offset: 20bytes)
Direccion del miembro varios:  0x0022FF0C (offset: 24bytes)

Direccion de la primera posicion de memoria despues de la estructura: 0x0022FF10

--
a) Analizar los disstintos valores presentes en la misma indicando claramente el significado de cada uno
b) Completar la codificacion presentada implementando el procedimiento showinfo y realizar una corrida del programa compilado, verificando los resultados obtenidos con los presentados en este punto. Para calcular el offset utilizar offseetof(struct pru_struct, miembro_estructura). Incluir <stddef.h>


*/
#include <stdio.h>
#include <stddef.h>
struct pru_struct
{
    char id1;
    char id2;
    char id3[10];
    char *nombre;
    char *domicilio;
    int edad;
    int varios;
};
void showinfo(struct pru_struct *empleado){
    printf("Valoress iniciales de la estructura\n");
    printf("id1: %c\nid2: %c\nid3: %s\nNombre: %s\nDireccion: %s\nEdad: %d\nVarios: %d\n",empleado->id1,empleado->id2,empleado->id3,empleado->nombre,empleado->domicilio,empleado->edad,empleado->varios);

    printf("Direccion de la estructura: %p\n", (void*)empleado);
    printf("Direccion del miembro id1: %p (offset: %ld bytes)\n", (void*)empleado->id1, offsetof(struct pru_struct,id1));
    printf("Direccion del miembro id2: %p (offset: %ld bytes)\n", (void*)empleado->id2, offsetof(struct pru_struct,id2));
    printf("Direccion del miembro id3: %p (offset: %ld bytes)\n", (void*)empleado->id3, offsetof(struct pru_struct,id3));
    printf("Direccion del miembro nombre: %p (offset: %ld bytes)\n", (void*)empleado->nombre, offsetof(struct pru_struct,nombre));
    printf("Direccion del miembro domicilio: %p (offset: %ld bytes)\n", (void*)empleado->domicilio, offsetof(struct pru_struct,domicilio));
    printf("Direccion del miembro edad: %p (offset: %ld bytes)\n", (void*)empleado->edad, offsetof(struct pru_struct,edad));
    printf("Direccion del miembro varios: %p (offset: %ld bytes)\n", (void*)empleado->varios, offsetof(struct pru_struct,varios));

    printf("Direccion de la primera posición de memoria despues de la estructura: %p\n",(void*)((char*)empleado+sizeof(struct pru_struct)));
    
}

int main()
{
    int i;
    int tmp;
    struct pru_struct empleados = 
    {
        'B',
        'C',
        "Sensible",
        "Pedro",
        "Av. Carlos Calvo 1234",
        23,
        68,
    };
    showinfo(&empleados);
}