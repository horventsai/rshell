#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>

using namespace std;

int main()
{
	while(1)
	{
		//variables
		char command[1024];					//used for user input, for the initial holding before parse
		char *pch;						//for strtok tokens(pointer)
		char name[1024];					//used for gethostname

		gethostname(name, 1024);
		cout << getlogin() << "@" << name <<  " $ ";
		cin.getline(command, 1024);
		
		pch = strtok(command, " \t\n\r");

		char **argv;						//pointer to pointer of chars
		argv = new char *[1024];				//creates new array of size DEFINED
		//argv[1023] = NULL;					//places NULL at second to last slot of array

		int it = 0;

		
		while(pch != NULL)
		{
			argv[it] = pch;
			for(/*iterator declared outside as 'it'*/; it < 1024; it++);
			pch = strtok(NULL, " ");
		}

		//argv[1023] = NULL;					//places NULL at second to last slot of array

		if(!strcmp(command,"exit"))
		{
			exit(0);
		}
		else
		{
			int pid_f = fork();				//error check for system call:fork()
			if(pid_f == 0)
			{
				//begin commands here
				int pid_e = execvp(argv[0], argv);	//error check for system call:execvp()
				if(pid_e == -1)
				{ 
					perror("execvp");
					exit(1);
				}
			}
			else if(pid_f == -1)
			{
				//exits with error code 1
				perror("fork");
				exit(1);
			}
			else
			{
				wait(NULL);
			}
		}
	}
	return 0;
}
