//
//  main.c
//  ejercicios_señales1
//
//  Created by Alejandro Herce on 2/25/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <signal.h>

void manejador(int ids)
{
    printf("--- Oprimiste Ctrl+C ...\n");
}

int main(int argc, const char * argv[]) {
    
    if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
        printf("ERROR: No se pudo establecer el manejador de la señal\n");
    }
    
    // A partir de aquí Ctrl+C no termina el programa
    
    int k = 10;
    
    while (k-- > 0) {
        printf(" +++ %d y contando\n", k);
        sleep(1);
    }
    
    return 0;
}
