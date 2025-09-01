#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // fork, execvp
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait
#include "Commands.h"

int main(int argc, char *argv[])
{
	//loop forever (until break)
	while (1)
	{
		//Main line for the shell
		printf("SMD-> ");

		//Make sure to print even before waiting for input
		fflush(stdout);

		//make a buffer for input
		char input[1024];

		//Use fgets to get input from the user
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		//remove newline from input 
		input[strcspn(input, "\n")] = '\0';
		
		//skip if input is empty
		if(strlen(input) == 0)
		{
			continue;
		}

		//array to store command + arguments
		char* args[64];
		
		int i = 0;

		//Get the first word
		char* token = strtok(input, " ");

		//Loop until no more words
		while (token != NULL && i < 63)
		{
			//storing in Array for execvp
			args[i++] = token;
			token = strtok(NULL, " ");
		}

		//requries NULL at the end
		args[i] = NULL;

		// Trim args[0]
		int len = strlen(args[0]);
		while(len > 0 && (args[0][len-1] == ' ' || args[0][len-1] == '\t' || args[0][len-1] == '\r')) {
    		args[0][len-1] = '\0';
    		len--;
		}

		// Trim args[1..] if needed
		for(int j=1; args[j]!=NULL; j++) {
    		len = strlen(args[j]);
   		 	while(len > 0 && (args[j][len-1] == ' ' || args[j][len-1] == '\t' || args[j][len-1] == '\r')) {
       		args[j][len-1] = '\0';
        	len--;
    	}
}
		
		
		//Handle built in commands from "Commands.h"
		int result = handle_builtin(args);
		if (result == 1) 
		{
			continue;
		}
		if (result == 2) 
		{
			break;
		}

		// Debug: print the command to be executed
		if (args[0] != NULL) {
			printf("[DEBUG] Command: %s\n", args[0]);
		}
		

        //Fork a child process
        pid_t pid = fork();
		
		if (pid < 0)
		{
			//Error if fails
			perror("Fork Failed");
		}
		else if (pid == 0)
		{
			//Child Process
			execvp(args[0], args);

			//this only gets reached if it fails
			perror("executing failed");
			fflush(stderr);
			printf("\n");
			exit(1);
		}
		else
		{
			//Parent process wait for child to finish
			wait(NULL);
		}

	}
	
}

