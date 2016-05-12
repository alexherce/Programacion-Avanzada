//
//  main.c
//  ejercicio_filosofos
//
//  Created by Alejandro Herce on 3/17/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10

sem_t cuchillos;
sem_t tenedores;
sem_t sillas;

void* accion(void*);

int main(int argc, const char * argv[]) {
    
    sem_init(&tenedores, 0, 3);
    sem_init(&cuchillos, 0, 3);
    sem_init(&sillas, 0, 4);
    
    srand((int)time(NULL));
    
    pthread_t* thread = (pthread_t*)malloc(N * sizeof(pthread_t));
    pthread_t* temp;
    
    int id = 1;
    for (temp = thread; temp < (thread + N); ++temp)
    {
        pthread_create(temp, NULL, accion, (void*)id);
        id++;
    }
    
    for (temp = thread; temp < (thread + N); ++temp)
    {
        pthread_join(*temp, NULL);
    }
    
    sem_destroy(&cuchillos);
    sem_destroy(&sillas);
    sem_destroy(&tenedores);
    
    free(thread);
    
    return 0;
}

void * accion(void * p)
{
    int id = (int)p;
    
    sem_wait(&sillas);
    printf("Se sienta filosofo %d\n", id);
    
    sem_wait(&cuchillos);
    printf("Usa cuchillo %d\n", id);
    
    sem_wait(&tenedores);
    printf("Usa tenedor %d\n", id);
    
    printf("Come filosofo %d\n", id);
    sleep((rand() % 16) + 5);
    printf("Termina filosofo %d\n", id);
    
    sem_post(&cuchillos);
    sem_post(&tenedores);
    sem_post(&sillas);
    
    pthread_exit(NULL);
}