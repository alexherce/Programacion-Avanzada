//
//  main.c
//  examen_rapido5
//
//  Created by Alejandro Herce on 2/22/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define TCP_PORT 8000

void store (int num);
void min (int *);
void max (int * );
void prom (int * );

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;
    
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int * temps;


int main(int argc, const char * argv[]) {
    temps = (int *)malloc(1 * sizeof(int));
    
    struct sockaddr_in direccion;
    char buffer[1000];
    
    int servidor, cliente;
    
    int leidos, escritos;
    
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    servidor = socket(PF_INET, SOCK_STREAM, 0);
    
    // Enlace con el socket
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Escuchar a los clientes
    listen(servidor, 10);
    
    // Comunicación
    socklen_t tamano = sizeof(direccion);
    
    cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);
    
    int fact;
    
    if (cliente >= 0) {
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        // Leer de socket y escribir en pantalla
        while (leidos = read(cliente, &buffer, sizeof(buffer))) {
            write(fileno(stdout), &buffer, leidos);
            
            store(atoi(buffer));
            
            printf("Recibi y almacene = %d\n", atoi(buffer));
            
            min(temps);
            max(temps);
            prom(temps);
            
            //leidos = write(fileno(stdin), &buffer, sizeof(buffer));
            write(cliente, &buffer, sizeof(int));
        }
    }
    
    // Cerrar el socket
    
    close(servidor);
    close(cliente);
    free(temps);
    
    return 0;
}

void store (int num)
{
    int i = 0;
    *(temps+i) = num;
    temps = (int *)realloc(temps, (i + 1) * sizeof(int));
    i++;
}

void min (int * temps)
{
    int i, min = 0;
    for(i=0;i<sizeof(temps);i++)
    {
        if(*temps>*(temps+i))
            min=*(temps+i);
    }
    printf("El minimo es: %d \n", min);
}

void max (int * temps)
{
    int i, max = 0;
    for(i=0;i<sizeof(temps);i++)
    {
        if(*temps<*(temps+i))
            max=*(temps+i);
    }
    printf("El maximo es: %d \n", max);
}

void prom (int * temps)
{
    
}
