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
char buffComplex[BUFSIZE];

int main() {

    char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, \ntapez 'exit'.\nenseash % \n";
    write(STDOUT_FILENO, buf, strlen(buf));

    while (1) {

        write(1,"% ", strlen("% "));

        int PID, status, commande,k=0;

        
          // On utilise STDIN_FILENO pour lire depuis l'entrée standard
        commande=read(STDIN_FILENO, buffer, BUFSIZE);//L'utilisateur écrit dans buffer
        buffer[commande-1]='\0';

        

        }
        if (strcmp("exit",buffer)==0||commande==0){ //on compte les différences entre le buffer et le mot "exit"
            write(1,"Bye, bye...", strlen("Bye, bye..."));
            exit(EXIT_FAILURE);
        }
        //We get the time of this line's execution just before the fork
        clock_gettime(CLOCK_MONOTONIC, &start);
        PID = fork();

        if (PID != 0) {
            wait(&status);

            //We get the time at the end of the child process
            //We calculate the time span in seconds between start and end
            //Same with nanoseconds
            //everything gets converted to milliseconds
            clock_gettime(CLOCK_MONOTONIC, &end);
            long seconds = end.tv_sec - start.tv_sec; 
            long nanoseconds = end.tv_nsec - start.tv_nsec;
            long milliseconds = seconds * 1000 + nanoseconds / 1000000;

              if (WIFEXITED(status)) {
                sprintf(Fils_Termine,"[exit :%d|%d ms]\n", WEXITSTATUS(status),milliseconds);
                write(1,Fils_Termine,strlen(Fils_Termine));
                } 
            else if (WIFSIGNALED(status)) {
                sprintf(Fils_Arrete,"[sign :%d|%dms]\n", WTERMSIG(status),milliseconds);
                write(1,Fils_Arrete,strlen(Fils_Arrete));
                }
    }
        
        else {
            k=0;
            buffComplex[k]=strtok(buffer," ");
            while (buffComplex[k]!=NULL){
                k++;
                buffComplex[k]=strtok(NULL," ");
                }           
            execvp(buffComplex[0],buffComplex); 
            
            if (strlen(buffer)==0){
                execlp("date","date", (char*)NULL);
            }
            // Utiliser EXIT_FAILURE en cas d'échec
            exit(EXIT_SUCCESS);
        }
      return 0;  
    }

    


