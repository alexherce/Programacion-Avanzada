//
//  main.c
//  Ejercicio2
//
//  Created by Alejandro Herce on 1/28/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define N 5
#define STRSIZE 20

/* --- STRUCTS --- */
int nCamillas = 5;

struct paciente
{
    char * nombrePaciente;
    char * apellidoPaciente;
    int edad;
    int telefono;
};
struct paciente* p;


struct camilla{
    int ocupado;
    struct paciente *paciente;
};
struct camilla * c;

void add_paciente();
void check_available();
void view_camillas();
void remove_paciente();
void view_paciente();
void view_stats();
void super_free_mem();

/* --- FUNCIONES DEL MENU --- */

typedef void (*menu_t)();

int main(int argc, const char * argv[]) {
    c = (struct camilla *)malloc(nCamillas * sizeof(struct camilla));
    
    int i = 0;
    for (i = 0; i < nCamillas; i++)
    {
        (c + i)->ocupado = 0;
    }
    
    /* Menu */
    
    int opcion = -1;
    menu_t * opciones = (menu_t *) malloc(5 * sizeof(menu_t));
    
    *opciones = add_paciente;
    *(opciones + 1) = view_camillas;
    *(opciones + 2) = view_paciente;
    *(opciones + 3) = remove_paciente;
    *(opciones + 4) = view_stats;
    
    while (opcion != 0)
    {
        printf("1.- Agregar paciente \n2.- Ver Todas las Camillas \n3.- Ver Paciente en Camilla \n4.- Dar de Alta a Paciente \n5.- Ver Camillas Vacias y Ocupadas \n0.- Salir \n");
        printf("Selecciona tu opcion: \n");
        scanf("%d", &opcion);
        
        if (opcion > 0 && opcion < 6)
        {
            (*(opciones[opcion-1]))();
        } else {
            printf("Opcion no valida \n");
        }
    }
    
    free(opciones);
    super_free_mem();
    
    return 0;
}

void check_available()
{
    int i, disp = 0;
    for(i = 0; i < nCamillas; i++)
    {
        if((c+i)->ocupado == 0)
        {
            disp++;
        }
    }
    if(disp == 0)
    {
        printf("Realloc Camillas \n");
        c = (struct camilla *)realloc(c, (nCamillas + 5) * sizeof(struct camilla));
        for (i = nCamillas; i < nCamillas + 5; i++)
        {
            (c + i)->ocupado = 0;
        }
        nCamillas = nCamillas + 5;
    }
}

void add_paciente()
{
    check_available();
    
    int i = 0;
    int disp = -1;
    for(i = 0; i < nCamillas; i++)
    {
        if((c+i)->ocupado == 0)
        {
            disp = i;
            break;
        }
    }
    
    (c+disp)->paciente = (struct paciente *)malloc(1 * sizeof(struct paciente));
    
    printf("Ingresa el nombre del paciente: \n");
    (c+disp)->paciente->nombrePaciente = (char *)malloc(STRSIZE * sizeof(char));
    scanf("%s", (c+disp)->paciente->nombrePaciente);
    
    printf("Ingresa el apellido del paciente: \n");
    (c+disp)->paciente->apellidoPaciente = (char *)malloc(STRSIZE * sizeof(char));
    scanf("%s", (c+disp)->paciente->apellidoPaciente);
    
    printf("Ingresa la edad del paciente: \n");
    scanf("%d", &(c+disp)->paciente->edad);
    
    printf("Ingresa el telefono del paciente: \n");
    scanf("%d", &(c+disp)->paciente->telefono);
    
    (c+disp)->ocupado = 1;
    
}

void view_camillas()
{
    int i = 0;
    for (i = 0; i < nCamillas; i++)
    {
        if((c + i)->ocupado == 0)
        {
            printf("Camilla [%d]: Vacia. \n", i + 1);
        } else {
            printf("Camilla [%d]: \n", i + 1);
            printf("-- Nombre: %s \n", (c+i)->paciente->nombrePaciente);
            
            printf("-- Apellido: %s \n", (c+i)->paciente->apellidoPaciente);
            
            printf("-- Edad: %d \n", (c+i)->paciente->edad);
            
            printf("-- Telefono: %d \n", (c+i)->paciente->telefono);
        }
    }
}

void view_paciente()
{
    int n;
    printf("Ingresa el numero de camilla: \n");
    scanf("%d", &n);
    n = n - 1;
    
    if((c+n)->ocupado == 0)
    {
        printf("Camilla vacia. \n");
    } else if ((c+n)->ocupado == 1)
    {
        printf("-- Nombre: %s \n", (c+n)->paciente->nombrePaciente);
        
        printf("-- Apellido: %s \n", (c+n)->paciente->apellidoPaciente);
        
        printf("-- Edad: %d \n", (c+n)->paciente->edad);
        
        printf("-- Telefono: %d \n", (c+n)->paciente->telefono);
    }
    
    
}

void view_stats()
{
    int i;
    int ocupadas = 0;
    int vacias = 0;
    for(i = 0; i < nCamillas; i++)
    {
        if((c+i)->ocupado == 1)
        {
            ocupadas++;
        } else {
            vacias++;
        }
    }
    
    printf("-- Camillas ocupadas: %d \n-- Camillas vacias: %d \n", ocupadas, vacias);
}

void remove_paciente()
{
    int n;
    printf("Ingresa el numero de camilla: \n");
    scanf("%d", &n);
    n = n - 1;
    
    if((c+n)->ocupado == 0)
    {
        printf("No hay paciente en esta camilla. \n");
    } else if ((c+n)->ocupado == 1)
    {
        free((c + n)->paciente->nombrePaciente);
        free((c + n)->paciente->apellidoPaciente);
        free((c + n)->paciente);
        (c + n)->ocupado = 0;
        
        printf("Paciente dado de alta! \n");
    }
    
}

void super_free_mem()
{
    int i;
    for (i = 0; i < nCamillas; i++)
    {
        if((c+i)->ocupado == 1)
        {
            free((c + i)->paciente->nombrePaciente);
            free((c + i)->paciente->apellidoPaciente);
            free((c + i)->paciente);
        }
    }
    free(c);
}