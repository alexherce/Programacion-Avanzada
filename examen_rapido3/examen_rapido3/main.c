//
//  main.c
//  examen_rapido3
//
//  Created by Alejandro Herce on 2/8/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int suma(int *, int, int);
void print(int *, int, int);

int main(int argc, const char * argv[]) {
    
    int n = 0;
    int i = 0;
    float prom;
    int estado;
    
    printf("Ingresa el numero de procesos a crear \n");
    scanf("%d", &n);
    
    pid_t pid;
    
    
    for(i = 0; i < n; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            printf("Error al crear el proceso hijo. Hay %d procesos creados. \n", i);
            break;
        }
        else if (pid == 0)
        {
            prom = (getpid() + getppid())/2;
            printf("--- Promedio del Hijo %d ---- \n", i);
            printf("%f \n", prom);
            exit(prom);
        }
        else {
            // Estamos en el padre
        }
        
    }
    
    return 0;
}
