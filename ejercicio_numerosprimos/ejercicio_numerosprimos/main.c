//
//  main.c
//  ejercicio_numerosprimos
//
//  Created by Alejandro Herce on 4/14/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define N 10000
#define M 100

int numDigitos(int);
int ifPrimoCircular(int);
int ifPrimo(int);

int main(int argc, const char * argv[]) {
    
    int i, j, k, total = 0;
    int * primosCirculares = NULL;
    
    for (i = M; i <= N; ++i)
    {
        if (ifPrimoCircular(i))
        {
            primosCirculares = (int*)realloc(primosCirculares, ++total * sizeof(int));
            primosCirculares[total - 1] = i;
        }
    }
    
    int** numeros = (int**)malloc(N * sizeof(int*));
    int** esPrimoCircular = (int**)malloc(N * sizeof(int*));
    
    int  mod = N - M + 1;
    for (i = 0; i < N; ++i)
    {
        numeros[i] = (int*)malloc(N * sizeof(int));
        esPrimoCircular[i] = (int*)malloc(N * sizeof(int));
    }
    
#pragma omp parallel shared(numeros, esPrimoCircular, mod) private(i,j)
    {
        int semilla = omp_get_thread_num();
#pragma omp for schedule(auto)
        for (i = 0; i < N; ++i)
        {
            for (j = 0; j < N; ++j)
            {
                numeros[i][j] = (rand_r(&semilla) % mod) + M;
                esPrimoCircular[i][j] = 0;
            }
        }
    }
    
#pragma omp parallel shared(numeros, esPrimoCircular, primosCirculares, total) private(i,j,k)
    {
        
#pragma omp for schedule(auto)
        for (i = 0; i < N; ++i)
        {
            for (j = 0; j < N; ++j)
            {
                for (k = 0; k < total; ++k)
                {
                    if (numeros[i][j] == primosCirculares[k])
                    {
                        esPrimoCircular[i][j] = 1;
                        break;
                    }
                }
            }
        }
    }
    
    free(primosCirculares);
    free(numeros);
    free(esPrimoCircular);
    
    return 0;
}

int numDigitos(int num)
{
    int n = 0;
    while (num >= 1)
    {
        n++;
        num /= 10;
    }
    return n;
}

int ifPrimo(int n)
{
    int i;
    if (n < 2)
        return 0;
    for (i = 2; i <= sqrt(n); ++i)
        if (n % i == 0)
            return 0;
    return 1;
}

int ifPrimoCircular(int n)
{
    int len = numDigitos(n), i, primoCircular = 1;
    
    if (!ifPrimo(n))
        return 0;
    
    for (i = 1; i < len; ++i)
    {
        int new = (pow(10, len - i) * (n % (int)pow(10, i))) + floor(n / pow(10, i));
        if (!ifPrimo(new))
            return 0;
    }
    return 1;
}
