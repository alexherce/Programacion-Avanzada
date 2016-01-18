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

#define N 3
typedef void (*menu_t)();

void opcion1();
void opcion2();
void opcion3();

int main(int argc, const char * argv[]) {
    
    int opcion = -1;
    
    menu_t * opciones = (menu_t *) malloc(N * sizeof(menu_t));
    
    *opciones = opcion1;
    *(opciones + 1) = opcion2;
    *(opciones + 2) = opcion3;
    
    while (opcion != 0)
    {
        printf("1.- Opcion 1 \n 2.- Opcion 2 \n 3.- Opcion 3 \n 0.- Salir \n");
        printf("Selecciona tu opcion: \n");
        scanf("%d", &opcion);
        
        if (opcion > 0 && opcion < 4)
        {
            (*(opciones[opcion-1]))();
        } else {
            printf("Opcion no valida \n");
        }
    }
    
    free(opciones);
    
    return 0;
}

void opcion1()
{
    printf("Opcion 1 \n");
}

void opcion2()
{
    printf("Opcion 2 \n");
}

void opcion3()
{
    printf("Opcion 3 \n");
}
