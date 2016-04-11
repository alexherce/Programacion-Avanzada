//
//  main.c
//  ejercicio3
//
//  Created by Alejandro Herce on 4/5/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 8
#define PESOMAX 100
#define PESOROBOT 15
#define NROBOTS 5

void* handlerRobots(void * arg);

struct seccion {
    int id;
    sem_t peso;
};


struct robot {
    int id;
};

typedef struct robot robot;

typedef struct seccion seccion;
seccion* secciones;

int main(int argc, const char * argv[]) {
    
    srand((unsigned)time(NULL));
    int i;
    robot* robots = (robot*) malloc (NROBOTS * sizeof(robot));
    
    for(i = 0; i < NROBOTS; ++i)
    {
        (robots+i)->id = i;
    }
    secciones = (seccion*) malloc (N* sizeof(seccion));
    
    for(i = 0; i < N; ++i){
        (secciones+i)->id = i;
        sem_init(&(secciones+i)->peso, 0, PESOMAX / PESOROBOT);
    }
    
    pthread_t* pt_robot = (pthread_t*) malloc (NROBOTS * sizeof(pthread_t));
    
    for(i = 0; i < NROBOTS; ++i)
    {
        pthread_create(pt_robot+i, NULL, &handlerRobots, (void*)(robots+i));
    }
    
    for(i = 0; i< NROBOTS; ++i)
    {
        pthread_join(*(pt_robot+i), NULL);
    }
    
    
    for(i = 0; i < N; ++i)
    {
        sem_destroy(&(secciones+i)->peso);
    }
    
    free(secciones);
    free(robots);
    free(pt_robot);
    
    return 0;
}

void* handlerRobots(void* arg){
    robot* robt = (robot*) arg;
    int i;
    for (i = 0; i < N; ++i)
    {
        sem_wait(&(secciones+i)->peso);
        printf("Robot %d entrando a la seccion: %d.\n", robt->id, (secciones+i)->id);
        sleep(rand() % 7);
        printf("Robot %d saliendo de la seccion: %d.\n", robt->id, (secciones+i)->id);
        sem_post(&(secciones+i)->peso);
    }
    
    printf("Robot %d termino.\n", robt->id);
    pthread_exit(NULL);
}
