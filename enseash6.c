#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define BUFSIZE 1096

//everything that will be used is defined or initialized here 
struct timespec start, end;
char buffer[BUFSIZE];
char Fils_Termine[BUFSIZE];
char Fils_Arrete[BUFSIZE];

int main() {
    char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, \ntapez 'exit'.\nenseash % \n";
    write(STDOUT_FILENO, buf, strlen(buf));

    while (1) {
        write(STDOUT_FILENO, "% ", strlen("% "));
        //Variables initializations
        int PID, status, commande;

        commande = read(STDIN_FILENO, buffer, BUFSIZE);
        buffer[commande - 1] = '\0';

        if (strcmp("exit", buffer) == 0 || commande == 0) {
            write(STDOUT_FILENO, "Bye, bye...", strlen("Bye, bye..."));
            exit(EXIT_SUCCESS);
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        PID = fork();

        if (PID != 0) {
            wait(&status);
            clock_gettime(CLOCK_MONOTONIC, &end);
            long seconds = end.tv_sec - start.tv_sec;
            long nanoseconds = end.tv_nsec - start.tv_nsec;
            long milliseconds = seconds * 1000 + nanoseconds / 1000000;

            if (WIFEXITED(status)) {
                sprintf(Fils_Termine, "[exit :%d|%ld ms]\n", WEXITSTATUS(status), milliseconds);
                write(STDOUT_FILENO, Fils_Termine, strlen(Fils_Termine));
            } else if (WIFSIGNALED(status)) {
                sprintf(Fils_Arrete, "[sign :%d|%ld ms]\n", WTERMSIG(status), milliseconds);
                write(STDOUT_FILENO, Fils_Arrete, strlen(Fils_Arrete));
            }
        } else {
            // We use strtok and execvp to differentiate the function and it's arguments 
            char *token = strtok(buffer, " ");
            char *args[BUFSIZE];
            int i = 0;

            while (token != NULL) {
                args[i] = token;
                i++;
                token = strtok(NULL, " ");
            }

            
            args[i] = NULL;

            // Replace the current process image with the specified command and arguments
            execvp(args[0], args);
            // If execvp fails, execute the "date" command as a default
            execlp("date", "date", (char *)NULL);
            // Use EXIT_FAILURE in case of failure
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

   


