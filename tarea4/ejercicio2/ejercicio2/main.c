//
//  main.c
//  ejercicio2
//
//  Created by Alejandro Herce on 4/11/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

#define NPERSONAS 15

pthread_mutex_t sanitario;
int genero = -1;
int fila[2];
int ocupando;

void sanitarioMujer();
void sanitarioHombre();

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
    
    pthread_t * persona = (pthread_t*)malloc(NPERSONAS*sizeof(pthread_t));
    pthread_t * aux;
    printf("Sanitarios Vacios. \n");
    
    for(aux = persona; aux < (persona + NPERSONAS); aux++)
    {
        int temp = rand() % 2;
        if(temp == 0)
        {
            printf("LLega un hombre, hay %d en espera. \n", ++fila[0]);
            pthread_create(aux,NULL,sanitarioHombre,NULL);
        } else {
            printf("LLega una mujer, hay %d en espera. \n", ++fila[1]);
            pthread_create(aux,NULL, sanitarioMujer,NULL);
        }
        
        sleep(rand() % 3);
    }
    
    for(aux = persona; aux < (persona+NPERSONAS); aux++)
    {
        pthread_join(*aux,NULL);
    }
    
    
    free(persona);
    return 0;
}

void sanitarioMujer(){
    
    while(genero == 0);
    genero = 1;
    
    pthread_mutex_lock(&sanitario);
    
    printf("Entra una mujer, hay %d en espera. \n", --fila[1]);
    
    pthread_mutex_unlock(&sanitario);
    ocupando++;
    sleep(rand()%5);
    
    printf("Sale una mujer. \n");
    
    ocupando--;
    if(ocupando == 0)
    {
        printf("Sanitario vacio. \n");
        genero = -1;
        pthread_mutex_unlock(&sanitario);
    }
}

void sanitarioHombre(){
    
    while(genero == 1);
    genero = 0;
    
    pthread_mutex_lock(&sanitario);
    
    printf("Entra un hombre, hay %d en espera. \n", --fila[0]);
    
    pthread_mutex_unlock(&sanitario);
    ocupando++;
    sleep((rand() % 5) + 2);
    
    printf("Sale un hombre. \n");
    
    ocupando--;
    if(ocupando == 0)
    {
        printf("Sanitario vacio. \n");
        genero = -1;
        pthread_mutex_unlock(&sanitario);
    }
}

