//
//  main.c
//  ejercicio_openmp2
//
//  Created by Alejandro Herce on 4/14/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    int i = 0;
    int array[6];
    int suma = 0;
    srand(time(NULL));
    
#pragma omp parallel shared(suma) private(i)
    {
#pragma omp sections
        {
#pragma omp section
            {
                omp_set_nested(1);
#pragma omp parallel num_threads(4)
                {
#pragma omp critical
                    {
                        printf("Proceso: %d\n", omp_get_thread_num());
                    }
                    
#pragma omp master
                    printf("Total Procesos: %d\n", omp_get_num_threads());
                }
            }
#pragma omp section
            {
#pragma omp parallel for
                for (i = 0; i < 6; i++)
                {
                    array[i] = rand() % 10;
                    printf("Numero %d: %d\n", i,array[i]);
                    suma += array[i];
                }
            }
        }
    }
    
    printf("Total suma: %d\n", suma);
    
    return 0;
}
