//
//  main.c
//  ejercicio_openmp1
//
//  Created by Alejandro Herce on 4/11/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <omp.h>

int main(int argc, const char * argv[]) {
    
    int nthreads, tid;
    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        printf("\nprueba");
        if(tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("\nNT: %d", nthreads);
        }
    }
    
    return 0;
}
