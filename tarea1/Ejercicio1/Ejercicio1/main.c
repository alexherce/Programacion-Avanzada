//
//  main.c
//  Ejercicio1
//
//  Created by Alejandro Herce on 1/27/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 20

int nTripulantes = 1;
int tripsActuales = 0;
int nBarcos = 1;
int barcosActuales = 0;

// Testing date changes

/* --- STRUCTS --- */

struct tripulante
{
    int edad;
    char * nombreTripulante;
    char * apellidoTripulante;
    char * rol;
    
};
struct tripulante* tripulacion;


struct barco{
    char *nombreBarco;
    float eslora;
    float manga;
    int maxTripulantes;
    int numTripulantes;
    char *nombreOwner;
    char *apellidoOwner;
    struct tripulante *tripulacion;
};
struct barco * b;

/* --- DECLARACION DE FUNCIONES --- */

void add_barco();
void print_barcos();
void add_tripulante();
void print_tripulante_barco();
void print_tripulante_all();
void super_free_mem();

/* --- FUNCIONES DEL MENU --- */

typedef void (*menu_t)();

/* --- MAIN -- */
int main(int argc, const char * argv[]) {
    
    b = (struct barco *)malloc(nBarcos * sizeof(struct barco));
    
    /* Menu */
    
    int opcion = -1;
    menu_t * opciones = (menu_t *) malloc(5 * sizeof(menu_t));
    
    *opciones = add_barco;
    *(opciones + 1) = print_barcos;
    *(opciones + 2) = add_tripulante;
    *(opciones + 3) = print_tripulante_all;
    *(opciones + 4) = print_tripulante_barco;
    
    while (opcion != 0)
    {
        printf("1.- Agregar Barco \n 2.- Ver Barcos \n 3.- Agregar Tripulante por # de Barco \n 4.- Ver Todos los Tripulantes \n 5.- Ver Tripulantes de un Barco (Por # de Barco) \n 0.- Salir \n");
        printf("Selecciona tu opcion: \n");
        scanf("%d", &opcion);
        
        if (opcion > 0 && opcion < 6)
        {
            (*(opciones[opcion-1]))();
        } else {
            printf("Opcion no valida \n");
        }
    }
    
    /* Liberar Memoria */
    
    super_free_mem();
    free(b);
    free(opciones);
    
    return 0;
}

/* --- FUNCIONES --- */

void add_barco(){
    if(barcosActuales >= nBarcos)
    {
        printf("Realloc Barcos \n");
        b = (struct barco *)realloc(b, (nBarcos + 1) * sizeof(struct barco));
        nBarcos++;
    }
    
    printf("- Añadir nuevo barco: \n");
    printf("-- Ingresa el nombre del barco: \n");
    (b + barcosActuales)->nombreBarco = (char *)malloc(STRSIZE * sizeof(char));
    scanf("%s", (b + barcosActuales)->nombreBarco);
    
    printf("-- Ingresa la eslora: \n");
    scanf("%f", &(b + barcosActuales)->eslora);
    
    printf("-- Ingresa la manga: \n");
    scanf("%f", &(b + barcosActuales)->manga);
    
    printf("-- Ingresa el numero max de tripulantes: \n");
    scanf("%d", &(b + barcosActuales)->maxTripulantes);
    (b + barcosActuales)->tripulacion = (struct tripulante *)malloc(((b + barcosActuales)->maxTripulantes - 1) * sizeof(struct tripulante));
    (b + barcosActuales)->numTripulantes = 0;
    
    printf("-- Ingresa el nombre del dueño: \n");
    (b + barcosActuales)->nombreOwner = (char *)malloc(STRSIZE * sizeof(char));
    scanf("%s", (b + barcosActuales)->nombreOwner);
    
    printf("-- Ingresa el apellido del dueño: \n");
    (b + barcosActuales)->apellidoOwner = (char *)malloc(STRSIZE * sizeof(char));
    scanf("%s", (b + barcosActuales)->apellidoOwner);
    
    barcosActuales++;
}

void print_barcos(){
    int i;
    if(barcosActuales > 0)
    {
        printf("- Barcos: \n");
        printf("--------------------------------------- \n");
        for(i = 0; i < barcosActuales; i++)
        {
            printf("-- Barco [%d]: \n", i + 1);
            printf("--- Nombre: %s \n", (b + i)->nombreBarco);
            printf("--- Eslora: %f \n", (b + i)->eslora);
            printf("--- Manga: %f \n", (b + i)->manga);
            printf("--- Tripulantes: %d / %d \n", (b + i)->numTripulantes, (b + i)->maxTripulantes);
            printf("--- Dueño: %s %s \n", (b + i)->nombreOwner, (b + i)->apellidoOwner);
            printf("--------------------------------------- \n");
        }
    } else {
        printf("No hay barcos en el sistema. \n");
    }
}

void add_tripulante(){
    
    int tmp;
    
    printf("- Ingresa el numero de barco: \n");
    scanf("%d", &tmp);
    tmp = tmp - 1;
    
    if(tmp < barcosActuales)
    {

        if((b+tmp)->numTripulantes <= (b+tmp)->maxTripulantes - 1)
        {
            ((b+tmp)->tripulacion + ((b+tmp)->numTripulantes))->nombreTripulante = (char *)malloc(STRSIZE * sizeof(char));
            ((b+tmp)->tripulacion + ((b+tmp)->numTripulantes))->apellidoTripulante = (char *)malloc(STRSIZE * sizeof(char));
            ((b+tmp)->tripulacion + ((b+tmp)->numTripulantes))->rol = (char *)malloc(STRSIZE * sizeof(char));
        
            printf("-- Agregando tripulante %d de %d: \n", ((b+tmp)->numTripulantes + 1), (b+tmp)->maxTripulantes);
            printf("-- Ingresa el nombre del tripulante: \n");
            scanf("%s", ((b+tmp)->tripulacion + ((b+tmp)->numTripulantes))->nombreTripulante);
            printf("-- Ingresa el apellido del tripulante: \n");
            scanf("%s", ((b+tmp)->tripulacion + ((b+tmp)->numTripulantes))->apellidoTripulante);
            printf("-- Ingresa la edad del tripulante: \n");
            scanf("%d", &((b+tmp)->tripulacion + ((b+tmp)->numTripulantes))->edad);
            printf("-- Ingresa el rol del tripulante: \n");
            scanf("%s", ((b+tmp)->tripulacion + ((b+tmp)->numTripulantes))->rol);
        
            (b+tmp)->numTripulantes++;
        
        } else {
            printf("ERROR: El barco ya esta lleno! Capacidad: %d \n", (b+tmp)->maxTripulantes);
        }
    } else {
        printf("ERROR: El barco no existe! \n");
    }
}

void print_tripulante_barco(int n){
    int i, tmp;
    
    printf("Ingresa el numero de barco: \n");
    scanf("%d", &tmp);
    tmp = tmp - 1;
    if(tmp < barcosActuales)
    {
        if((b+tmp)->numTripulantes > 0)
        {
            printf("- Tripulantes del barco %s: \n", (b + tmp)->nombreBarco);
            printf("---------------------- \n");
            for(i = 0; i < (b + tmp)->numTripulantes; i++)
            {
                printf("-- Tripulante %d de %d: \n", i + 1, (b + tmp)->numTripulantes);
                printf("--- Nombre: %s \n", ((b + tmp)->tripulacion + i)->nombreTripulante);
                printf("--- Apellido: %s \n", ((b + tmp)->tripulacion + i)->apellidoTripulante);
                printf("--- Edad: %i \n", ((b + tmp)->tripulacion + i)->edad);
                printf("--- Rol: %s \n", ((b + tmp)->tripulacion + i)->rol);
                printf("---------------------- \n");
            }
        } else {
            printf("-- El barco no tiene tripulantes! \n");
        }
    } else {
        printf("ERROR: Barco no existe! \n");
    }
}

void print_tripulante_all()
{
    int i, j;
    for(i = 0; i < barcosActuales; i++)
    {
        printf("- Tripulantes del barco: %s \n", (b + i)->nombreBarco);
        printf("---------------------- \n");
        for(j = 0; j < (b + i)->numTripulantes; j++)
        {
            printf("-- Tripulante %d de %d: \n", j + 1, (b + i)->numTripulantes);
            printf("--- Nombre: %s \n", ((b + i)->tripulacion + j)->nombreTripulante);
            printf("--- Apellido: %s \n", ((b + i)->tripulacion + j)->apellidoTripulante);
            printf("--- Edad: %i \n", ((b + i)->tripulacion + j)->edad);
            printf("--- Rol: %s \n", ((b + i)->tripulacion + j)->rol);
            printf("---------------------- \n");
        }
        printf("--------------------------------------- \n");
    }
}

void super_free_mem()
{
    int i, j;
    for(i = 0; i < barcosActuales; i++)
    {
        for(j = 0; j < (b + i)->numTripulantes; j++)
        {
            free(((b+i)->tripulacion + j)->nombreTripulante);
            free(((b+i)->tripulacion + j)->apellidoTripulante);
            free(((b+i)->tripulacion + j)->rol);
        }
        free((b+i)->nombreBarco);
        free((b+i)->nombreOwner);
        free((b+i)->apellidoOwner);
        free((b+i)->tripulacion);
    }
}
