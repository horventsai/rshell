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

int main(int argc, char *argv[])
{
	while(1)
	{
		//variables
		char command[1024];
		char *pch;
		char name[1024];

		gethostname(name, 1024);
		cout << getlogin() << "@" << name <<  " $ ";
		cin.getline(command, 1024);
		
		pch = strtok(command, " \t\n\r");

		char **argv;
		argv = new char *[1024];

		int it = 0;

		while(pch != NULL)
		{
			argv[it] = command;
			for(/*iterator declared outside as 'it'*/; it < 1024; it++);
			pch = strtok(NULL, " ");
		}

		if(!strcmp(command,"exit"))
		{
			exit(0);
		}
		else
		{
			int pid_f = fork();
			if(pid_f == 0)
			{
				//begin commands here
				if(execvp(argv[0], argv) == -1)
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
