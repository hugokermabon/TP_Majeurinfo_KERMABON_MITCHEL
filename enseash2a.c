
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 1096    // Definition of the buffer size used to store the character string.

char buffer[BUFSIZE];   // Initialization of the character array 'buffer'.

int main() {

    // Initialization of the character array 'buf' with the welcome message.
    char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, \ntapez 'exit'.\nenseash % \n";
   
    // Using the write function to write the character string 'buf' in the shell.
    write(STDOUT_FILENO, buf, strlen(buf));

    // We use an infinite while loop so that the code can continuously read from the shell at any time.
    while (1) {

        // '%' is written before each new instruction.
        write(1,"% ", strlen("% "));

        //Initialisation of variables.
        int PID, status, commande;
       
        // Creation of two processes: Parent and Child.
        PID = fork();

        // The Parent wait for is Child
        if (PID != 0) {
            wait(&status);
        }
       
        // The child executes the command that the user will write in the shell.    
        else {

            // User write in the buffer
            commande=read(STDIN_FILENO, buffer, BUFSIZE);
            // We replace the last "enter" element with "\0" to indicate that
            // it is a character string.
            buffer[commande-1]='\0';
            // We execute the function that is specify in the buffer.
            execlp(buffer,buffer, (char*)NULL);
           
            // If the user just clic on the enter button we launch the date programm.
            if (strlen(buffer)==0){
                execlp("date","date", (char*)NULL);
            }
           

            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
