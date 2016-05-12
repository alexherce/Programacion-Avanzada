//
//  main.c
//  ExamenFinal
//
//  Created by Alejandro Herce on 5/12/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 16
#define S 4
#define PROCESADORES 4

int map[N][N];
int sections[S][2];
int remaining = N/S;

void fillMap();
void printMap();
void * find();
void findPath(int inicio, int end);
void finder(int x, int y, limitex, limitey);

int main(int argc, const char * argv[]) {

    printf("Hello, World!\n");
    
    fillMap();
    printMap();
    
    pthread_t * threads = (pthread_t *) malloc(PROCESADORES * sizeof(pthread_t));
    
    for (int i = 0; i < PROCESADORES; ++i)
    {
        printf("+++ Creando el hilo %d ...\n", i);
        pthread_create((threads+i), NULL, find,  i);
    }
    
//    for (int i = 0; i < PROCESADORES; ++i) {
//        
//        pthread_join(*(threads+i), NULL);
//        
//        printf("--- Terminando el hilo %d ...\n", i);
//    }
    
    printMap();
    
    free(threads);
    
    return 0;
}

void fillMap()
{
    int tmp;
    int sectx = 0;
    int secty = 0;
    srand(time(NULL));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            tmp = rand() % 100;
            if(tmp > 80)
            {
                if(i == 0 && j == 0)
                    map[i][j] = 0;
                else if (i == N - 1 && j == N - 1)
                    map[i][j] = 0;
                else
                    map[i][j] = 1;
            } else {
                map[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < S; i++)
    {
        sections[i][0] = sectx;
        sections[i][1] = secty;
        sectx += S;
        secty += S;
    }
}

void printMap()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

void * find(void * arg)
{
    int tempn = arg;
    tempn = remaining - tempn;
    int tempx = sections[tempn][0];
    int tempy = sections[tempn][1];
    
    finder(tempx, tempy, tempx + S, tempy + S);
    
    pthread_exit(NULL);
}

void findPath(int inicio, int end)
{
    
}

void finder(int x, int y, limitex, limitey)
{
    map[x][y] = 8;
    if(x == N-1 && y == N-1)
    {

    }
    
    if(map[x+1][y+1] == 0 && x < limitex && y < limitey)
    {
        finder(x++, y++, limitex, limitey);
    }
    
    if(map[x][y+1] == 0 && x < limitex && y < limitey)
    {
        finder(x, y++, limitex, limitey);
    }
    
    if(map[x+1][y] == 0 && x < limitex && y < limitey)
    {
        finder(x++, y, limitex, limitey);
    }
}