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
    int n = 0;
    int c;
    int i;
    int estado;
    int tmp = 10;
    
    while ((c = getopt(argc, argv, "n:")) != -1) {
        switch (c) {
            case 'n':
                n = atoi(optarg);
                break;
            default:
                return 1;
        }
    }
    printf("Crear %d procesos \n", n);
    
    // Posicion 0 es pos de lectura y 1 es de escritura
    int tuberia[2];
    pid_t pid;
    pid_t pidPadre;
        
    // Crea el pipe
    pipe(tuberia);
    
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
            
            if (pid == -1)
            {
                printf("Error al crear el proceso hijo. \n");
            }
            else if (pid == 0)
            {
                int numero, bits;
                printf("leyendo... ");
                close(tuberia[1]);
                bits = read(tuberia[0], &numero, sizeof(int));
                printf("listo! \n");
                if(bits == sizeof(int))
                {
                    printf("Soy el hijo %d con PID: %d Recibi el testigo '%d' y lo tendre 5 segundos. \n", i + 1, getpid(), numero);
                    sleep(5);
                    close(tuberia[0]);
                    write(tuberia[1], &numero, sizeof(int));
                    printf("Soy el hijo %d con PID: %d Mande el testigo '%d' \n", i + 1, getpid(), numero);
                }
                exit(0);
            } else {
                if (waitpid(pid, &estado, 0) != -1)
                {
                    if (WIFEXITED(estado)) {
                        printf("Ya terminó el proceso hijo con PID %d \n", getpid());
                    }
                }
            }
        }
        
    } else {
        close(tuberia[0]);
        write(tuberia[1], &tmp, sizeof(int));
        if (waitpid(pidPadre, &estado, 0) != -1)
        {
            if (WIFEXITED(estado)) {
                printf("Ya terminó el proceso padre con PID %d \n", getpid());
            }
        }
    }
    return 0;
}
