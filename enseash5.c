#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define BUFSIZE 1096
struct timespec start, end;//We define start and end to measure the time between the beginning and the end of the process

char buffer[BUFSIZE];
char Fils_Termine[BUFSIZE];
char Fils_Arrete[BUFSIZE];

int main() {
    char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, \ntapez 'exit'.\nenseash % \n";
    write(STDOUT_FILENO, buf, strlen(buf));

    while (1) {

        write(1,"% ", strlen("% "));

        int PID, status, commande;

          // On utilise STDIN_FILENO pour lire depuis l'entrée standard
        commande=read(STDIN_FILENO, buffer, BUFSIZE);//L'utilisateur écrit dans buffer
        buffer[commande-1]='\0';
        if (strcmp("exit",buffer)==0||commande==0){ //on compte les différences entre le buffer et le mot "exit"
            write(1,"Bye, bye...", strlen("Bye, bye..."));
            exit(EXIT_FAILURE);
        }

        clock_gettime(CLOCK_MONOTONIC, &start);//We get the time of this line's execution just before the fork
        PID = fork();

        if (PID != 0) {
            wait(&status);
            clock_gettime(CLOCK_MONOTONIC, &end);//We get the time at the end of the child process

            long seconds = end.tv_sec - start.tv_sec; //We calculate the time span in seconds between start and end
            long nanoseconds = end.tv_nsec - start.tv_nsec;//Same with nanoseconds
            long milliseconds = seconds * 1000 + nanoseconds / 1000000;//everything gets converted to milliseconds

              if (WIFEXITED(status)) {
                sprintf(Fils_Termine,"[exit :%d|%dms]\n", WEXITSTATUS(status),milliseconds);
                write(1,Fils_Termine,strlen(Fils_Termine));
                } 
            else if (WIFSIGNALED(status)) {
                sprintf(Fils_Arrete,"[sign :%d|%dms]\n", WTERMSIG(status),milliseconds);
                write(1,Fils_Arrete,strlen(Fils_Arrete));
                }
    }
        
        else {
       
            execlp(buffer,buffer, (char*)NULL); 
            
            if (strlen(buffer)==0){
                execlp("date","date", (char*)NULL);
            }

            exit(EXIT_SUCCESS); // Utiliser EXIT_FAILURE en cas d'échec
        }
        
    }

    return 0;
}

