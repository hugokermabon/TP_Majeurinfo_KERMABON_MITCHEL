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
        int PID, status;

          // Utiliser STDIN_FILENO pour lire depuis l'entrée standard

        // Supprimer le caractère de nouvelle ligne lu par read
        buffer[strcspn(buffer, "\n")] = '\0';

        PID = fork();

        if (PID != 0) {
            wait(&status);
        } else {
            read(STDIN_FILENO, buffer, BUFSIZE);
            execlp(buffer,buffer, (char*)NULL);  
            perror("enseash");  // execlp a échoué
            exit(EXIT_SUCCESS); // Utiliser EXIT_FAILURE en cas d'échec
        }
    }

    return 0;
}

