//
//  main.c
//  examen_rapido8
//
//  Created by Alejandro Herce on 3/17/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <time.h>

#define nclientes 5
#define nempresas 3

typedef struct
{
    sem_t sem;
    int id;
    int cont;
} empresas;

typedef struct
{
    sem_t sem;
    int id;
    int cont;
} clientes;

empresas dineroEmpresas[nempresas];
clientes dineroClientes[nclientes];

void* atenderEmpresas(int n, int p);
void* atenderClientes(int n, int p);
void* operacionesClientes(int n);
void* operacionesEmpresas(int n);

int main(int argc, const char * argv[]) {
    
    int i = 0;
    
    for(i = 0; i < nempresas; ++i)
    {
        sem_init(&dineroEmpresas[i], 0, 1);
        dineroEmpresas[i].id = i;
        dineroEmpresas[i].cont = 0;
    }
    
    for(i = 0; i < nclientes; ++i)
    {
        sem_init(&dineroClientes[i], 0, 1);
        dineroClientes[i].id = i;
        dineroClientes[i].cont = 0;
    }
    
    pthread_t generaClientes[100];
    pthread_t generaEmpresas[50];
    
    pthread_t *temp;
    int index = 0;
    
    for(temp = generaClientes; temp < (generaClientes+100); ++temp)
        pthread_create(temp, NULL, operacionesClientes, (void*)index++);
    
    for(temp = generaClientes; temp < (generaClientes+100); ++temp)
        pthread_join(*temp, NULL);
    
    for(temp = generaEmpresas; temp < (generaEmpresas+50); ++temp)
        pthread_create(temp, NULL, operacionesEmpresas, (void*)index++);
    
    for(temp = generaEmpresas; temp < (generaEmpresas+50); ++temp)
        pthread_join(*temp, NULL);
    
    for(i = 0; i < nclientes; ++i)
        sem_destroy(&(dineroClientes[i].sem));
    
    for(i = 0; i < nempresas; ++i)
        sem_destroy(&(dineroEmpresas[i].sem));
    
    return 0;
}

void* atenderEmpresas(int n, int p)
{
    printf("Cliente empresarial %d atendido en ventana %d \n", n, p);
    dineroEmpresas[p].cont += 1;

    sleep(5);
    
    if(dineroEmpresas[p].cont == 5)
    {
        sleep(5);
        dineroEmpresas[p].cont = 0;
    }
    pthread_exit(NULL);
}

void* atenderClientes(int n, int p)
{
    printf("Cliente regular %d atendido en  ventana %d \n", n, p);
    dineroClientes[p].cont += 1;
    
    sleep(5);
    
    if(dineroClientes[p].cont == 5)
    {
        sleep(5);
        dineroClientes[p].cont = 0;
    }
    
    pthread_exit(NULL);
}

void* operacionesClientes(int n)
{
    int status = -1;
    int i = 0;
    while(status == -1)
    {
        for (i; i < nclientes; ++i)
        {
            status = sem_trywait(&dineroClientes[i].sem);
            if (status == 0)
                atenderClientes(n, i);
        }
    }
}

void* operacionesEmpresas(int n)
{
    int status = -1;
    int i = 0;
    while(status == -1)
    {
        for (i; i < nempresas; ++i)
        {
            status = sem_trywait(&dineroEmpresas[i].sem);
            if (status == 0)
                atenderEmpresas(n, i);
        }
    }
}
