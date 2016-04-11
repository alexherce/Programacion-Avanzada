//
//  main.c
//  ejercicio1
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

struct enano {
    int id;
    pthread_mutex_t comio;
};

typedef struct enano Enano;

int cont;
sem_t sillas;
sem_t ocupadas;

Enano* mesa[4];

void* handlerEnano(void * arg);
void* handlerBlancanieves(void* arg);

int main(int argc, const char * argv[]) {
    
    srand((unsigned)time(NULL));
    sem_init(&sillas, 0, 4);
    sem_init(&ocupadas, 0, 0);
    Enano* enanos = (Enano*) malloc (7 * sizeof(Enano));
    int i;
    
    for (i = 0; i < 7; ++i)
    {
        (enanos+i)->id = i+1;
        pthread_mutex_init(&(enanos+i)->comio, NULL);
    }
    
    pthread_t * enanos_pt = (pthread_t*) malloc (7 * sizeof(pthread_t));
    pthread_t blancanieves_pt;
    pthread_create(&blancanieves_pt, NULL, &handlerBlancanieves, NULL);
    
    for(i = 0; i < 7; ++i)
    {
        pthread_create(enanos_pt+i, NULL, &handlerEnano, (void*)(enanos+i));
    }
    
    pthread_join(blancanieves_pt, NULL);
    sem_destroy(&sillas);
    sem_destroy(&ocupadas);
    free(enanos_pt);
    free(enanos);
    
    return 0;
}

void* handlerEnano(void * arg){
    Enano* e = (Enano*) arg;
    printf("Enano %d se va a las minas.\n", e->id);
    sleep(rand() % 15);
    printf("Enano %d llega de las minas\n", e->id);
    int i;
    sem_wait(&sillas);
    printf("Enano %d se sienta en la mesa.\n", e->id);
    for (i = 0; i < 4; ++i)
    {
        if(mesa[i] == NULL)
        {
            mesa[i] = e;
            sem_post(&ocupadas);
            pthread_mutex_trylock(&(e->comio));
            break;
        }
    }
    pthread_mutex_lock(&(e->comio));
    sleep(2);
    printf("Enano %d termino de comer y se va las minas. \n", e->id);
    mesa[i] = NULL;
    sem_post(&sillas);
    pthread_exit(NULL);
}

void* handlerBlancanieves(void* arg){
    int cont = 0;
    int status;
    while(cont < 7)
    {
        int t, i;
        sem_getvalue(&ocupadas, &t);
        if (t > 0)
        {
            for(i = 0; i < 4; ++i)
            {
                if (mesa[i] != NULL)
                {
                    pthread_mutex_unlock(&(mesa[i]->comio));
                    printf("Blancanieves le da de comer a Enano %d. \n", mesa[i]->id);
                    sem_trywait(&ocupadas);
                    cont++;
                }
            }
        }
        else{
            printf("Blancanieves se va a dar la vuelta. \n");
            sleep(5);
        }
    }
    printf("Todos comieron. \n");
    pthread_exit(NULL);
}
