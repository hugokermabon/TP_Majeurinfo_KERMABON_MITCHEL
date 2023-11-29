#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 1096

char buffer[BUFSIZE];

int main() {
    char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, \ntapez 'exit'.\nenseash % \n";
    write(STDOUT_FILENO, buf, strlen(buf));

    while (1) {

        write(1,"% ", strlen("% "));

        int PID, status, commande;

          // Utiliser STDIN_FILENO pour lire depuis l'entrée standard
        commande=read(STDIN_FILENO, buffer, BUFSIZE);//L'utilisateur écrit dans buffer
        buffer[commande-1]='\0';
        if (strcmp("exit",buffer)==0||commande==0){ //on compte les différences entre le buffer et le mot "exit"
            write(1,"Bye, bye...", strlen("Bye, bye..."));
            exit(EXIT_FAILURE);
        }

        PID = fork();

        if (PID != 0) {
            wait(&status);
        } else {
            
            
           
            execlp(buffer,buffer, (char*)NULL); 
            
            if (strlen(buffer)==0){
                execlp("date","date", (char*)NULL);
            }
            

            exit(EXIT_SUCCESS); // Utiliser EXIT_FAILURE en cas d'échec
        }
    }

    return 0;
}

