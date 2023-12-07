#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

#define BUFSIZE 1096

struct timespec start, end;
char buffer[BUFSIZE];
char Fils_Termine[BUFSIZE];
char Fils_Arrete[BUFSIZE];

int main() {
    char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, \ntapez 'exit'.\nenseash % \n";
    write(STDOUT_FILENO, buf, strlen(buf));

    while (1) {
        write(STDOUT_FILENO, "% ", strlen("% "));

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
            char *token = strtok(buffer, " ");
            char *args[32];
            int i = 0;

            while (token != NULL && i < 31) {
                if (strcmp(token, "<") == 0) {
                    // Input Redirection: Set stdin to read from the specified file
                    token = strtok(NULL, " ");
                    int fd = open(token, O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                } else if (strcmp(token, ">") == 0) {
                    // Output Redirection: Set stdout to write to the specified file
                    token = strtok(NULL, " ");
                    int fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                } else {
                    // Regular Argument: Add the token as a command argument
                    args[i++] = token;
                }
                token = strtok(NULL, " ");
            }

            args[i] = NULL;
            execvp(args[0], args);

            // Utiliser EXIT_FAILURE en cas d'échec
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
