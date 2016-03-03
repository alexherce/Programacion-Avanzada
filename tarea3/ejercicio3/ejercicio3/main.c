//
//  main.c
//  ejercicio3
//
//  Created by Alejandro Herce on 3/3/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include	<stdlib.h>
#include    <stdio.h>
#include    <signal.h>
#include    <sys/types.h>
#include    <unistd.h>
#include    <string.h>

void handler(int);
char* mensaje;

int main (int argc, char *argv[])
{
    int n;
    int* array;
    int i = 0;
    
    if (argc != 2)
    {
        printf("Error! Numero de argumentos invalido. \n");
        abort();
    }
    
    signal(SIGINT, SIG_IGN);
    mensaje = (char*)malloc(50*sizeof(char));
    strcpy(mensaje, "Dato");
    signal(SIGALRM, handler);
    n = atoi(argv[1]);
    
    if (n < 5 || n > 9)
    {
        printf("Error! Cantidad de numeros debe ser entre 5 y 9. \n");
        abort();
    }
    
    array = (int*)malloc(n*sizeof(int));
    
    alarm(3);
    
    for (i = 0; i < n; ++i)
    {
        printf("%s %d:", mensaje, i);
        scanf("%d", array+i);
    }
    
    printf("Numeros: \n");
    
    for (i = 0; i < n; ++i)
    {
        printf("%d: %d\n", i, *(array+i));
    }
    
    free(array);
    free(mensaje);
    return 0;
}

void handler(int sig){
    strcpy(mensaje,"Dese prisa. Dato");
}
