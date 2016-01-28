//
//  main.c
//  clase_18enero
//
//  Created by Alejandro Herce on 1/18/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

/*
MENU EN C
 Mas eficiente que el switch.
*/

#include <stdio.h>
#include <stdlib.h>

#define M 4
#define N 20
int * vector;
int tipo_dato = 1;

/* Tipos de funciones */

typedef int (*t_compare)(void *, void *);

typedef void (*t_swap)(void * , void * );

typedef void (*t_sort)(void *, size_t, size_t, t_compare, t_swap );

/* Funciones genéricas */

void sort(t_sort, void *, size_t , size_t, t_compare, t_swap );

void insertionSort(void * vector, size_t count, size_t size, t_compare compare, t_swap swap );
void selectionSort(void * vector, size_t count, size_t size, t_compare compare, t_swap swap );

/* Funciones callback para enteros */

int ascInt(void * , void * );
int descInt(void * , void * );

void swapInt(void * , void * );

/* Funciones callback para flotantes */

int ascFloat(void * , void * );
int descFloat(void * , void * );

void swapFloat(void * , void * );

/* Funciones de impresión */

void imprimeInt(int *, int );

void imprimeFloat(float *, int );

/* Funciones del menu */

typedef void (*menu_t)();

void insertion_asc();
void insertion_desc();
void selection_asc();
void selection_desc();

int main(int argc, const char * argv[]) {
    
    int opcion = -1;
    
    printf("Selecciona el tipo de dato a ordenar: \n");
    printf("1.- int, 2.- float \n");
    scanf("%i", &tipo_dato);
    
    /* Generar y guardar números enteros */
    
    vector = (int *) malloc(N * sizeof(int));
    
    int * aux = vector;
    int * last = vector + N;
    
    for (; aux < last; ++aux) {
        *aux = rand() % 100;
    }
    
    printf("\n\n--- Enteros ---\n\n");
    
    imprimeInt(vector, N);
    
    /* Menu */
    
    menu_t * opciones = (menu_t *) malloc(M * sizeof(menu_t));
    
    *opciones = insertion_asc;
    *(opciones + 1) = insertion_desc;
    *(opciones + 2) = selection_asc;
    *(opciones + 3) = selection_desc;
    
    while (opcion != 0)
    {
        printf("1.- Insertion Sort Asc \n 2.- Insertion Sort Desc \n 3.- Selection Sort Asc \n 4.- Selection Sort Desc \n 0.- Salir \n");
        printf("Selecciona tu opcion: \n");
        scanf("%d", &opcion);
        
        if (opcion > 0 && opcion < 5)
        {
            (*(opciones[opcion-1]))();
        } else {
            printf("Opcion no valida \n");
        }
    }
    
    free(opciones);
    
    return 0;
}

/* Implementación de funciones genéricas */

void sort(t_sort algorithm, void * vector, size_t count, size_t size, t_compare compare, t_swap swap )
{
    (*algorithm)(vector, count, size, compare, swap);
}

void insertionSort(void * vector, size_t count, size_t size, t_compare compare, t_swap swap )
{
    void * j;
    void * start = vector;
    void * aux = start;
    void * last = start + (count * size);
    
    for (; aux < last ; aux+=size)
    {
        j = aux - size;
        while (j >= start && (*compare)(j, j+size) )
        {
            (*swap)(j+size, j);
            j-=size;
        }
    }
}

void selectionSort(void * vector, size_t count, size_t size, t_compare compare, t_swap swap )
{
    void * minimo;
    
    void * j;
    void * start = vector;
    void * aux = start;
    void * last = start + (count * size);
    void * prelast = last - size;
    
    for(; aux < prelast; aux+=size)
    {
        minimo = aux;
        for(j = aux + size; j < last; j+=size)
        {
            if ( (*compare)(minimo, j) )
                minimo = j;
        }
        
        (*swap)(minimo, aux);
    }
}

/* Implementación de funciones callback para enteros */

int ascInt(void * pa, void * pb)
{
    int * a = (int *)pa;
    int * b = (int *)pb;
    return (*a > *b);
}

int descInt(void * pa, void * pb)
{
    int * a = (int *)pa;
    int * b = (int *)pb;
    return (*a < *b);
}

void swapInt(void * pa , void * pb )
{
    int temp;
    int * a = (int *)pa;
    int * b = (int *)pb;
    
    temp = *a;
    *a = *b;
    *b = temp;
    
}


/* Implementación de funciones callback para flotantes */

int ascFloat(void * pa, void * pb)
{
    float * a = (float *)pa;
    float * b = (float *)pb;
    return (*a > *b);
}

int descFloat(void * pa, void * pb)
{
    float * a = (float *)pa;
    float * b = (float *)pb;
    return (*a < *b);
}

void swapFloat(void * pa , void * pb )
{
    float temp;
    float * a = (float *)pa;
    float * b = (float *)pb;
    
    temp = *a;
    *a = *b;
    *b = temp;
    
}

/* Implementación de funciones de impresión */

void imprimeInt(int * vector, int count)
{
    int * aux = vector;
    int * last = vector + count;
    
    for (; aux < last; ++aux) {
        printf(" %4d ", *aux);
    }
    
    printf("\n");
}

void imprimeFloat(float * vector, int count)
{
    float * aux = vector;
    float * last = vector + count;
    
    for (; aux < last; ++aux) {
        printf(" %7.2f ", *aux);
    }
    
    printf("\n");
}

/* Implementacion de funciones del menu */

void insertion_asc()
{
    if(tipo_dato == 1)
    {
        sort(&insertionSort, vector, N, sizeof(*vector), &ascInt, &swapInt);
        printf("\n\n--- Enteros Ordenados ---\n\n");
    
        imprimeInt(vector, N);
    } else if (tipo_dato == 2)
    {
        sort(&insertionSort, vector, N, sizeof(*vector), &ascFloat, &swapFloat);
        printf("\n\n--- Floats Ordenados ---\n\n");
        
        imprimeFloat(vector, N);
    }
}

void insertion_desc()
{
    if(tipo_dato == 1)
    {
        sort(&insertionSort, vector, N, sizeof(*vector), &descInt, &swapInt);
        printf("\n\n--- Enteros Ordenados ---\n\n");
        
        imprimeInt(vector, N);
    } else if (tipo_dato == 2)
    {
        sort(&insertionSort, vector, N, sizeof(*vector), &descFloat, &swapFloat);
        printf("\n\n--- Floats Ordenados ---\n\n");
        
        imprimeFloat(vector, N);
    }
}

void selection_asc()
{
    if(tipo_dato == 1)
    {
        sort(&selectionSort, vector, N, sizeof(*vector), &ascInt, &swapInt);
        printf("\n\n--- Enteros Ordenados ---\n\n");
        
        imprimeInt(vector, N);
    } else if (tipo_dato == 2)
    {
        sort(&selectionSort, vector, N, sizeof(*vector), &ascFloat, &swapFloat);
        printf("\n\n--- Floats Ordenados ---\n\n");
        
        imprimeFloat(vector, N);
    }
}

void selection_desc()
{
    if(tipo_dato == 1)
    {
        sort(&selectionSort, vector, N, sizeof(*vector), &descInt, &swapInt);
        printf("\n\n--- Enteros Ordenados ---\n\n");
        
        imprimeInt(vector, N);
    } else if (tipo_dato == 2)
    {
        sort(&selectionSort, vector, N, sizeof(*vector), &descFloat, &swapFloat);
        printf("\n\n--- Floats Ordenados ---\n\n");
        
        imprimeFloat(vector, N);
    }
}
