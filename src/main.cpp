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

		//gethostname(name, 1024);
									//ERROR CHECKING FOR PROMPT
		char *pid_ln = getlogin();				//error check for getlogin()
		if(pid_ln == NULL)
		{
			perror("getlogin");
			exit(1);
		}
		int pid_hn = gethostname(name, 1024);			//error check for gethostname()
		if(pid_hn != 0)
		{
			perror("gethostname");
			exit(1);
		}

		cout << getlogin() << "@" << name <<  " $ ";
		cin.getline(command, 1024);
		
		//pch = strtok(command, " \t");				//parse user input into string tokens, taking input from 'command'

		char **arg;						//pointer to pointer of chars
		arg = new char *[1024];					//creates new array of size DEFINED
		//arg[1023] = NULL;					//places NULL at second to last slot of array

		int it = 0;
		for(pch = strtok(command, " \t");
			pch != NULL;
			pch = strtok(NULL, " \t"))			//for-loop to move tokens into arg array
		{
			arg[it] = pch;					//at iterator it place token
			it++;						//increase iterator by one
		}
		arg[it] = NULL;						//places NULL at slot in array right after parse finishes

		if(!strcmp(command,"exit"))				//if 'command' only holds exit,
		{
			delete []arg;					//delete []arg on exit prompt
			exit(0);					//exit without loading error code; exit code: 0
		}
		else
		{
			int pid_f = fork();				//error check for system call:fork()
			if(pid_f == 0)
			{
				//begin commands here
				int pid_e = execvp(arg[0], arg);	//error check for system call:execvp()
				if(pid_e == -1)
				{
					perror("execvp");		//if execvp fails to function, exits with error code
					exit(1);
				}
			}
			else if(pid_f == -1)
			{
				perror("fork");				//if fork fails to function, exits with error code
				exit(1);
			}
			else
			{
				wait(NULL);				//wait for child
			}
		}
	}
	return 0;
}
