//
//  main.c
//  Ejercicio2
//
//  Created by Alejandro Herce on 1/28/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define STRSIZE 20
#define N_RESP 6
#define N_PREG 10

int nPersonas = 0;
int maxPersonas = 10;

struct respuestas{
    int respuesta;
};

struct persona {
    char * nombre;
    int edad;
    struct respuestas *respuestas;
};
struct persona * p;

struct opciones {
    int nOpcion;
    char * opcion;
};

struct pregunta {
    char * pregunta;
    struct opciones *opciones;
};
struct pregunta * preg;

void add_persona();
void add_preguntas();
void answer();
void view_answers();
void view_answers_age();

/* --- FUNCIONES DEL MENU --- */

typedef void (*menu_t)();

int main(int argc, const char * argv[]) {
    
    p = (struct persona *)malloc(maxPersonas * sizeof(struct persona));
    preg = (struct pregunta *)malloc(N_PREG * sizeof(struct pregunta));

    /* Menu */
    
    int opcion = -1;
    menu_t * opciones = (menu_t *) malloc(5 * sizeof(menu_t));
    
    *opciones = add_persona;
    *(opciones + 1) = add_preguntas;
    *(opciones + 2) = answer;
    *(opciones + 3) = view_answers;
    *(opciones + 4) = view_answers_age;
    
    while (opcion != 0)
    {
        printf("1.- Agregar Personas \n 2.- Agregar Preguntas \n 3.- Contestar Encuesta \n 4.- Ver Respuestas \n 5.- Ver Respuestas por Edad \n 0.- Salir \n");
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
    
    free(p);
    free(preg);
    free(opciones);
    
    return 0;
}

void add_persona()
{
    int age = 0;
    if(nPersonas >= maxPersonas)
    {
        printf("Realloc Personas \n");
        p = (struct persona *)realloc(p, (maxPersonas + 1) * sizeof(struct persona));
        maxPersonas++;
    }
    
    printf("- Añadir nueva persona: \n");
    printf("-- Ingresa el nombre: \n");
    (p + nPersonas)->nombre = (char *)malloc(STRSIZE * sizeof(char));
    scanf("%s", (p + nPersonas)->nombre);
    
    while(age < 17 || age > 120)
    {
        printf("-- Ingresa la edad (solo mayores de 17): \n");
        scanf("%d", &age);
        (p + nPersonas)->edad = age;
    }
    
    (p + nPersonas)->respuestas = (struct respuestas *)malloc(N_PREG * sizeof(struct respuestas));
    
    nPersonas++;
}

void add_preguntas()
{
    int i, j = 0;
    for(i = 0; i < N_PREG; i++)
    {
        printf("Ingresa la pregunta:  \n");
        (preg + i)->pregunta = (char *)malloc(STRSIZE * sizeof(char));
        scanf("%s", (preg + i)->pregunta);
        
        (preg + i)->opciones = (struct opciones *)malloc(N_RESP * sizeof(struct opciones));
        for(j = 0; j < N_RESP; j++)
        {
            ((preg + i)->opciones + j)->opcion = (char *)malloc(STRSIZE * sizeof(char));
            ((preg + i)->opciones + j)->nOpcion = j;
            printf("Ingresa la opcion %d: \n", j + 1);
            scanf("%s", ((preg + i)->opciones + j)->opcion);
        }
    }
}

void answer()
{
    int user = 0;
    int answ = 0;
    printf("Ingresa el numero de usuario: \n");
    scanf("%d", &user);
    user = user - 1;
    
    printf("Contestar encuesta para usuario '%s' \n", (p + user)->nombre);
    
    int i, j = 0;
    for(i = 0; i < N_PREG; i++)
    {
        printf("[%d] %s \n", i + 1, (preg + i)->pregunta);
        printf("Opciones: \n");
        for(j = 0; j < N_RESP; j++)
        {
            printf("%d.- %s \n", j, ((preg + i)->opciones + j)->opcion);
        }
        
        while(answ < 1 || answ > 6)
        {
            printf("Elige una opcion: \n");
            scanf("%d", &answ);
            ((p + i)->respuestas + j)->respuesta = answ;
        }
    }

}

void view_answers()
{
    
}

void view_answers_age()
{
    
}
