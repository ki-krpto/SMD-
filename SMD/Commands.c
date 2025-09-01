#include "Commands.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int handle_builtin(char **args) {
    
    // handle exit
    if (strcmp(args[0], "exit") == 0) {
        return 2;
    }

    // handle cd
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] != NULL) {
            if (chdir(args[1]) != 0) perror("chdir failed");
        }
        return 1;
    }

    //handle clear
    if (strcmp(args[0], "clear") == 0) {
        system("clear");
        return 1;
    }

    //handle help
    if (strcmp(args[0], "help") == 0) {
        printf("ls:					Show Files In Directory				usage: ls\n");
        printf("cd					Change Directory					usage: cd directory\n");
        printf("clear               clear the terminal of text          usage: clear\n");
        printf("help                Show command help                   usage: help\n");
        return 1;
    }
    
    printf("Not a builtin command");
    //if not a built in function
    return 0; 
}