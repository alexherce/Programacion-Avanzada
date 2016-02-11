//
//  main.c
//  ejercicio5
//
//  Created by Alejandro Herce on 2/11/16.
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
    char* programa = NULL;
    pid_t pid;
    
    while ((c = getopt(argc, argv, "n:p:")) != -1) {
        switch (c) {
            case 'n':
                n = atoi(optarg);
                break;
            case 'p':
                programa = optarg;
                break;
            default:
                return 1;
        }
    }
    
    for(i = 0; i < n; i++)
    {
        pid = fork();
        
        if (pid == -1)
        {
            printf("Error al crear el hijo. \n");
        }
        else if (pid == 0)
        {
            execl(programa, (char*) NULL);
            exit(0);
        }
    }
    wait(NULL);
    
    return 0;
}
