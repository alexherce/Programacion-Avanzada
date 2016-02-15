//
//  main.c
//  examen_rapido4
//
//  Created by Alejandro Herce on 2/15/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    int n = 1;
    int c;
    int i;
    int estado;
    
    while ((c = getopt(argc, argv, "n:")) != -1) {
        switch (c) {
            case 'n':
                n = atoi(optarg);
                break;
            default:
                return 1;
        }
    }
    
    // Posicion 0 es pos de lectura y 1 es de escritura
    int tuberia[2];
        pid_t pid;
        
    // Crea el pipe
    pipe(tuberia);
        
    // Hacer fork, los dos prcesos tienen conocimiento de la estructura
    pid = fork();
        
    if(pid == -1)
    {
        printf("Error al crear al proceso hijo\n");
        exit(-1);
    }
    else if(pid == 0)
    {
    int factorial, numero, bits, i;
            
            while(1)
            {
                // Cerrar escritura antes de leer, no cerrar lectura despues de leer
                close(tuberia[1]);
                bits = read(tuberia[0], &numero, sizeof(int));
                if(bits == sizeof(int))
                {
                    if(numero == 0) exit(0);
                    factorial = 1;
                    for(i = 1; i <= numero; ++i)
                    {
                        factorial *= i;
                    }
                    printf("El factorial de %d es %d\n", numero, factorial);
                }
            }
        }
        else
        {
            int num = 1;
            while(num  != 0)
            {
                scanf("%d", &num);
                // Cerrar lectura antes de escribir, no cerrar ecritura despues...
                close(tuberia[0]);
                write(tuberia[1], &num, sizeof(int));
            }
        }
    
    for(i = 0; i < n; i++)
    {
        pid = fork();
        
        if (pid == -1)
        {
            printf("Error al crear el proceso hijo. \n");
        }
        else if (pid == 0)
        {
            char bits;
            char chr;
            close(tuberia[1]);
            bits = read(tuberia[0], &chr, sizeof(int));
            printf("Soy el hijo %d con PID: %d Recibi el testigo %c que tendre por 5 segundos. \n", i + 1, getpid(), chr);
            sleep(5);
            exit(0);
        }
    }
    
    // -- MUESTRA LOS HIJOS A COMO VAN TERMINANDO --
    while ((pid = wait(&estado)) > 0) {
        printf("Termino hijo con PID: %d \n", pid);
    }
    
    
        return 0;
}
