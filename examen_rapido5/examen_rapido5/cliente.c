//
//  cliente.c
//  examen_rapido5
//
//  Created by Alejandro Herce on 2/22/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define TCP_PORT 8000
#define TIME_INTERVAL 10;
#define N 2;

int main(int argc, const char * argv[]) {
    
    struct sockaddr_in direccion;
    char buffer[1000];
    
    int cliente;
    
    int leidos, escritos;
    
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    cliente = socket(PF_INET, SOCK_STREAM, 0);
    
    // Establecer conexión
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
    int estado = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Comunicación
    
    if (estado == 0) {
        printf("Conectado a %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
     
        int i = 0;
        int j = 0;
        char c [10];
        int time_int = TIME_INTERVAL;
        for(i = 0; i < 2; i++)
        {
            int * temps = (int *)malloc(10 * sizeof(int));
            
            for(j = 0; j < time_int; j++)
            {
                printf("Generando Temperatura... ");
                srand(time(NULL) ^ (i<<1));
                *(temps+j) = rand() % 50;
                printf(" %d ", *(temps+j));
                printf("done! \n ");
                sleep(1);
            }
            
            for(j = 0; j < time_int; j++)
            {
                printf("Enviando... ");
                sprintf(c,"%d",*(temps+j));
                strncpy(buffer, &c, sizeof(c));
                printf("Enviando %s... ", c);
                // Leer de teclado y escribir en socket
                    write(cliente, &buffer, 1000);
                
                    //write(fileno(stdout), &buffer, 1000);
                printf("done! \n ");
            }
            free(temps);
        }
    }
    
    // Cerrar el socket
    close(cliente);
    
    return 0;
}
