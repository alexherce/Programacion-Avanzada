//
//  main.c
//  examen_rapido7
//
//  Created by Alejandro Herce on 3/14/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <math.h>

#define N 5
#define T 4

int grabar = 1;

void handler_alarm(int);
int delete_files(char*);

int main(int argc, const char * argv[]) {
    
    int i = 0;
    char* path_dir = "./datos";
    size_t path_len = strlen(path_dir);
    
    struct stat st;
    
    if (stat(path_dir, &st) != -1){
        if(delete_files < 0){
            printf("Error al borrar! \n");
            abort();
        }
    }
    
    mkdir (path_dir, 0770);
    
    signal(SIGALRM, handler_alarm);
    char* nombre = (char*) malloc (4+path_len);
    int filedir;
    FILE* f;
    
    alarm(T);
    
    for (i; i < N; ++i){
        snprintf(nombre, 4 + path_len, "%s/a%d",path_dir, i);
        filedir = open(nombre, O_CREAT | O_RDWR, 0666);
        if((f = fdopen(filedir, "w+")) == NULL){
            printf("Error: %s ", nombre);
            printf("Error: %c%d\n", 'a', i);
        }
        sleep(3);
        while(grabar == 1){
            fprintf(f,"X");
        }
        fclose(f);
        grabar = 1;
    }
    
    i = 0;
    printf("Archivos Nuevos:\n");
    int* size = (int*)malloc(5 * sizeof(int));
    for (i; i < N; ++i){
        snprintf(nombre, 4+ path_len, "%s/a%d", path_dir, i);
        stat(nombre, &st);
        *(size+i) = st.st_size;
        printf("Archivo '%s' | Tamaño: %d \n", nombre, *(size+i));
    }

    
    return 0;
}

void handler_alarm(int sig){
    grabar = 0;
    alarm(T);
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
