#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1096

int main() {
    char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, \ntapez 'exit'.\nenseash % \n";
    write(STDOUT_FILENO, buf, strlen(buf));

    return 0;
}


