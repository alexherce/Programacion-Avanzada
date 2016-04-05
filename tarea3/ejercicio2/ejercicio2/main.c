//
//  main.c
//  ejercicio2
//
//  Created by Alejandro Herce on 3/3/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include	<stdlib.h>
#include    <stdio.h>
#include    <sys/types.h>
#include    <string.h>
#include    <dirent.h>
#include    <sys/stat.h>
#include    <signal.h>
#include    <unistd.h>
#include    <fcntl.h>

#define N 5
#define T 4

int grabar = 1;

int delete_files(char*);
void handler_alarm(int);


int main ( int argc, char *argv[] ){
    
    char* path = "./datos";
    size_t path_len = strlen(path);
    
    struct stat st;
    
    if (stat(path, &st) != -1){
        if(delete_files < 0){
            printf("Error al borrar! \n");
            abort();
        }
    }
    
    mkdir (path, 0770);
    
    signal(SIGALRM, handler_alarm);
    int i = 0;
    char* nombre = (char*) malloc (4+path_len);
    int fd;
    FILE* f;
    
    alarm(T);
    
    for (i; i < N; ++i){
        snprintf(nombre, 4 + path_len, "%s/a%d",path, i);
        fd = open(nombre, O_CREAT | O_RDWR, 0666);
        if((f = fdopen(fd, "w+")) == NULL){
            printf("Error %s ", nombre);
            printf("Error en %c%d\n", 'a', i);
        }
        sleep(3);
        while(grabar == 1){
            fprintf(f,"x");
        }
        fclose(f);
        grabar = 1;
    }
    
    i = 0;
    printf("Archivos nuevos:\n");
    int* tamanos = (int*) malloc (5*sizeof(int));
    for (i; i < N; ++i){
        snprintf(nombre, 4+ path_len, "%s/a%d", path, i);
        stat(nombre, &st);
        *(tamanos+i) = st.st_size;
        printf("%s tamano: %d\n", nombre, *(tamanos+i));
    }
    
    
    return 0;
}

int delete_files(char* path){
    char* buffer;
    DIR *direct;
    int r = -1;
    size_t path_len = strlen(path);
    struct dirent *ep;
    direct = opendir("./datos");
    if (direct != NULL)
    {
        r = 0;
        while (ep = readdir (direct))
        {
            int r2 = -1;
            if (!strcmp(ep->d_name, ".") || !strcmp(ep->d_name, ".."))
                continue;
            
            size_t len = path_len + strlen(ep->d_name) + 2;
            buffer = (char*) malloc (len);
            if(buffer)
            {
                struct stat statbuf;
                snprintf(buffer, len, "%s/%s", path, ep->d_name);
                if(!stat(buffer, &statbuf)){
                    if(S_ISDIR(statbuf.st_mode))
                        r2 = delete_files(buffer);
                    else
                        r2 = unlink(buffer);
                }
                free(buffer);
            }
            r = r2;
        }
        closedir(direct);
    }
    if (!r)
        r = rmdir(path);
    
    return r;
}

void handler_alarm(int signal){
    grabar = 0;
    alarm(T);
}
