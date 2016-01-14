//
//  main.c
//  EjerciciosApuntadores1
//
//  Created by Alejandro Herce on 1/14/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <string.h>

/* Obligatorio para usar con malloc */
#include <stdlib.h>

void ej1_invertirCadena();
void ej2_contarCadena();

int main(int argc, const char * argv[]) {
    
    
    //ej1_invertirCadena();
    ej2_contarCadena();
    return 0;
}

/* Escriba un programa en C que permita invertir una cadena de caracteres utilizando aritmética de apuntadores. */
void ej1_invertirCadena()
{
    char * stringOriginal = (char *)malloc(100 * sizeof(char));
    char * stringInvertido = (char *)malloc(100 * sizeof(char));
    
    int i, j;
    j = 0;
    
    printf("Ingresa la cadena \n");
    
    /* fgets obtiene string con espacios, scanf no reconoce espacios */
    fgets(stringOriginal, 100, stdin);
    
    long int size = strlen(stringOriginal);
    j = size - 1;
    
    for(i = 0; i <= size; i++)
    {
        stringInvertido[i] = stringOriginal[j];
        j--;
    }
    
    printf("%s \n", stringInvertido);
    
    free(stringOriginal);
    free(stringInvertido);
}

/* Escriba un programa en C que obtenga la longitud de una cadena (sin strlen) utilizando aritmética de apuntadores. */
void ej2_contarCadena()
{
    char * string = (char *)malloc(100 * sizeof(char));
    
    printf("Ingresa la cadena: \n");
    /* fgets obtiene string con espacios, scanf no reconoce espacios */
    fgets(string, 100, stdin);
    
    char * p = string;
    int n;
    while (*p++ != '\n'){};
    
    n = (p - string - 1);
    printf("El tamaño es: %d \n", n);
    
    free(string);
    
}
