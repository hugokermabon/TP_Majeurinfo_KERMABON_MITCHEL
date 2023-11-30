#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1096  // Definition of the buffer size used to store the character string.

int main() {
   
    // Initialization of the character array 'buf' with the welcome message.
    char buf[BUFSIZE] = "Welcome to the ENSEA Shell. \nTo exit, \ntype 'exit'.\nenseash % \n";
   
    // Using the write function to write the character string 'buf' in the shell.
    write(STDOUT_FILENO, buf, strlen(buf));
   

    return 0;  // End of the program with a return code of 0 indicating successful execution.
}



