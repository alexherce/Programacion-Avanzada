//
//  main.c
//  examen_rapido2
//
//  Created by Alejandro Herce on 1/28/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct  Libro {
    
    char * titulo;
    
    int paginas;
    
};
struct Libro * libros;

typedef void (*t_direction)(void *, size_t, int);

void recorre(int n, int size);
void forward();
void backward();
void iterate(t_direction, void *, size_t, int len);

int main(int argc, const char * argv[]) {
    
    
    
    return 0;
}

void* begin(void* vector){
    return vector;
}

void* next(void* vector, size_t size){
    return (vector+size);
}

void* prev(void* vector, size_t size){
    return (vector-size);
}

void* end(void* vector,size_t size, int len){
    return (vector+(size*len));
}

void forward(void * vector, size_t size)
{
    void * start = vector;
    void * aux = start;
    void * last = start + (size);

}

void backward(void * vector, size_t size)
{
    void * start = vector + (size);
    void * aux = start;
    void * last = vector;
}

void iterate(t_direction option, void * vector, size_t size, int len)
{
    (*option)(vector, size, len);
}

void recorre(int n, int len)
{
    if(n == 0)
    {
        iterate(forward, libros, sizeof(*libros),len);
    } else if (n == 1) {
        iterate(backward, libros, sizeof(*libros),len);
    }
}

