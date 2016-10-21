//
//  main.c
//  ejercicio1
//
//  Created by Alejandro Herce on 3/3/16.
//  Copyright © 2016 Alejandro Herce. All rights reserved.
//

#include	<stdlib.h>
#include    <stdio.h>
#include    <unistd.h>
#include    <signal.h>
#include    <sys/wait.h>
#include    <sys/types.h>

// Test cambio fecha 2

int x = 0;
int y = 0;
int tiempo = 3;

void handler_user();
void handler(int);
void handler_alarm();

int main (int argc, char *argv[])
{
    pid_t pid;
    int estado;
    
    struct sigaction action;
    
    pid = fork();
    
    if(pid < 0){
        printf("Error al crear el hijo. \n");
        exit(-1);
    }
    else if(pid == 0){
        printf("Soy el hijo con PID: %d\n", getpid());
        signal (SIGINT, SIG_IGN);
        signal (SIGTSTP, SIG_IGN);
        sleep(10);
        kill(getppid(), SIGUSR1);
    }
    else{
        printf("Soy el padre con PID: %d\n", getpid());
        
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigaction (SIGINT, &action, 0);
        
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigaction(SIGTSTP, &action, 0);
        
        action.sa_handler = handler_user;
        action.sa_flags = SA_RESTART;
        sigaction (SIGUSR1, &action, 0);
        
        action.sa_handler = handler_alarm;
        action.sa_flags = SA_RESTART;
        
        sigaction (SIGALRM, &action, 0);
        
        alarm(tiempo);
        
        if (waitpid(pid, &estado, 0) != -1)
            wait(NULL);
        
    }
    
    return 0;
}

void handler_user(){
    printf("Se ha pulsado %d veces CTRL+C y se ha pulsado %d veces CTRL+Z. Acabando... \n",x,y);
    signal(SIGKILL, SIG_DFL);
    raise(SIGKILL);
}

void handler(int signal){
    if (signal == SIGINT){
        x++;
        tiempo++;
    }
    else if(signal == SIGTSTP){
        y++;
        if (tiempo > 1)
            tiempo--;
    }
}

void handler_alarm(){
    printf("Aparezco cada %d, segundos. \n", tiempo);
    alarm(tiempo);
}
