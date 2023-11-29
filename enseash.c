#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

int main() {
    char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash %% ";

    write(STDOUT_FILENO, buf, strlen(buf));

    return 0;
}

