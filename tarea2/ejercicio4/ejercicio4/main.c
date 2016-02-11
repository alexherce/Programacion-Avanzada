//
//  main.c
//  ejercicio4
//
//  Created by Alejandro Herce on 2/11/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

pid_t pid;

void add_proceso(int n, int p, int nActual) {
    int i;
    int j;
    
    for (i = 0; i < p; ++i)
    {
        pid = fork();
        if (pid == -1)
        {
            printf("Error al crear proceso. \n");
        } else if (pid == 0)
        {
            if (n + 1 == nActual)
            {
                exit(0);
            }
            
            for(j = 0; j < nActual; ++j)
            {
                printf("-");
            }
            printf(" PID: %d \n", getpid());
            
            add_proceso(n, p, nActual + 1);
            exit(0);
            
        } else {
            wait(NULL);
        }
    }
}

int main(int argc, const char * argv[]) {
    
    int niveles = 0;
    int procesos = 0;
    int nActual = 1;
    int c;
    pid_t pidPadre;
    int estado;
    
    while ((c = getopt(argc, argv, "n:p:")) != -1) {
        switch (c) {
            case 'n':
                niveles = atoi(optarg);
                break;
            case 'p':
                procesos = atoi(optarg);
                break;
            default:
                abort();
        }
    }
    
    
    pidPadre = fork();
    if (pidPadre == -1)
    {
        printf("Error al crear el proceso padre. \n");
    }
    else if (pidPadre == 0)
    {
        add_proceso(niveles, procesos, nActual);
    } else {
        if (waitpid(pidPadre, &estado, 0) != -1)
        {
            if (WIFEXITED(estado)) {
                printf("Ya terminó el proceso padre con PID %d \n", getpid());
            }
        }
    }
    
    return 0;
}
