//
//  main.c
//  ejercicio3
//
//  Created by Alejandro Herce on 2/11/16.
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
    int estado;
    int t = 0;
    
    printf("Ingresa el numero de procesos a crear \n");
    scanf("%d", &n);
    
    pid_t pid;
    pid_t pidPadre;
    
    // -- PARA QUE FUNCIONE EN XCODE. NO ES NECESARIO EL PIDPADRE --
    // SIN PIDPADRE, TERMINA EL PROGRAMA ANTES DE MOSTRAR LOS HIJOS.
    pidPadre = fork();
    if (pidPadre == -1)
    {
        printf("Error al crear el proceso padre. \n");
    }
    else if (pidPadre == 0)
    {
        // -- CREAR LOS HIJOS. --
        for(i = 0; i < n; i++)
        {
            pid = fork();
            
            // srand para que sea realmente aleatorio.
            srand(time(NULL) ^ (getpid()<<16));
            
            if (pid == -1)
            {
                printf("Error al crear el proceso hijo. \n");
            }
            else if (pid == 0)
            {
                
                t = rand() % 10;
                printf("Soy el hijo %d con PID: %d Esperando %d segundos. \n", i + 1, getpid(), t);
                sleep(t);
                exit(0);
            }
        }
        
        // -- MUESTRA LOS HIJOS A COMO VAN TERMINANDO --
        while ((pid = wait(&estado)) > 0) {
            printf("Termino hijo con PID: %d \n", pid);
        }
        
    } else {
        if (waitpid(pidPadre, &estado, 0) != -1)
        {
            if (WIFEXITED(estado)) {
                printf("Ya terminó el proceso padre con PID %d \n", getpid());
            }
        }
    }
    
// Date test
    
    return 0;
}
