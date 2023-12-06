#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define BUFSIZE 1096

struct timespec start, end;
char buffer[BUFSIZE];
char Fils_Termine[BUFSIZE];
char Fils_Arrete[BUFSIZE];
char buffComplex[BUFSIZE];

int main() {
    char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, \ntapez 'exit'.\nenseash % \n";
    write(STDOUT_FILENO, buf, strlen(buf));

    while (1) {
        write(STDOUT_FILENO, "% ", strlen("% "));  // Utilisez STDOUT_FILENO pour la sortie standard

        int PID, status, commande, k = 0;

        commande = read(STDIN_FILENO, buffer, BUFSIZE);
        buffer[commande - 1] = '\0';

        if (strcmp("exit", buffer) == 0 || commande == 0) {
            write(STDOUT_FILENO, "Bye, bye...", strlen("Bye, bye..."));
            exit(EXIT_SUCCESS);  // Utilisez EXIT_SUCCESS pour une sortie réussie
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
            k = 0;
            buffComplex[k] = strtok(buffer, " ");
            while (buffComplex[k] != NULL) {
                k++;
                buffComplex[k] = strtok(NULL, " ");
            }
            execvp(buffComplex[0], buffComplex);

            if (strlen(buffer) == 0) {
                execlp("date", "date", (char *)NULL);
            }
            exit(EXIT_FAILURE);  // Utilisez EXIT_FAILURE en cas d'échec
        }
    }
    return 0;
}
   


