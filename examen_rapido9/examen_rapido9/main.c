//
//  main.c
//  examen_rapido9
//
//  Created by Alejandro Herce on 3/31/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define ASIENTOS 50
#define SALAS 3
#define COMPLEJOS 10
#define CLIENTES 10
#define BOLETOS 5

int asientos[ASIENTOS*SALAS*COMPLEJOS];
pthread_mutex_t mutexes[ASIENTOS*SALAS*COMPLEJOS] = PTHREAD_MUTEX_INITIALIZER;

void * funcionOperaciones(void *);

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
    
    pthread_t * clientes = (pthread_t *) malloc (sizeof(pthread_t) * CLIENTES);
    
    for (int i = 0; i < CLIENTES; i++) {
        printf("Creando cliente: %d \n", i+1);
        pthread_create(clientes+i, NULL, funcionOperaciones, i + 1);
    }
    ;
    
    for (int i = 0; i < CLIENTES; i++) {
        pthread_join(*(clientes+i), NULL);
    }
    
    free(clientes);
    
    return 0;
}

void * funcionOperaciones(void * arg)
{
    int id = (int) arg;
    int complejo;
    int sala;
    int asiento;
    
    int temp;
    int aux = 0;
    int nBoletos = rand() % BOLETOS + 1;
    
    complejo = rand() % COMPLEJOS;
    sala = rand() % SALAS;
    asiento = rand() % ASIENTOS;
    temp = complejo * SALAS * ASIENTOS + (sala * ASIENTOS) + asiento;
    
    while(aux < nBoletos)
    {
        sleep(rand() % 3 + 1);
        
        while(asientos[temp])
        {
            complejo = rand()%COMPLEJOS;
            sala = rand()%SALAS;
            asiento = rand()%ASIENTOS;
            temp = complejo * SALAS * ASIENTOS + (sala * ASIENTOS) + asiento;
        }
        
        pthread_mutex_lock(&(*(mutexes+temp)));
        if(!asientos[temp])
        {
            printf("[Clientes %d] Comprando asiento %d, en sala %d, en complejo %d. \n", id, asiento, sala, complejo);
            asientos[temp]++;
            aux++;
        }
        else
        {
            printf("[Cliente %d] Asiento ocupado (asiento %d, sala %d, complejo %d), comprando otro. \n", id, asiento, sala, complejo);
        }
        pthread_mutex_unlock(&(*(mutexes+temp)));
    }
    
    pthread_exit(NULL);
}
