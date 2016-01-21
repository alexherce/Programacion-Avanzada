//
//  main.c
//  examen_rapido1
//
//  Created by Alejandro Herce on 1/21/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    char * cadena = (char *)malloc(100 * sizeof(char));
    int * letras = (int *)malloc(30 * sizeof(int));
    
    int i, j = 0;
    for(int i = 0; i < 29; i++)
    {
        letras[i] = 0;
    }
    
    
    printf("Ingresa la cadena: \n");
    fgets(cadena, 100, stdin);
    
    long int size = strlen(cadena);
    char * p = cadena;
    
    while (*p++ != '\n')
    {
        char temp = *(p-1);
        (*(letras + temp - 'a'))++;
    }
    
    for(i = 0; i < 29; i++)
    {
        printf("%c: ", 'a'+i);
        printf("%i \n", letras[i]);
    }
    
    free(cadena);
    free(letras);
    
    return 0;
}
