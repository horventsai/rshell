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
#include <fcntl.h>

using namespace std;
								//GLOBAL DEFINITIONS AND MACROS
#define MAX_CAP 1024
#define SUB_MAX 256

								//HELPER FUNCTIONS

void prepiping(char **parg)
{
									//VARIABLES
	int ploc = 0;							//location of pipes
	char **before;
	char **after;
	before = new char *[SUB_MAX];
	after = new char *[SUB_MAX];

									//PROCESS
	for(int i = 0; parg[i] != '\0'; i++)
	{
		if(strcmp(parg[i], "|") == 0)
		{
			ploc = i;					//location of first pipe
			break;
		}
	}

	for(int i = 0; i < ploc; i++)
	{
		before[i] = parg[i];					//populates before array with arg before pipe
		if((i+1) == ploc)
		{
			before[i+1] = '\0';				//if whats next = pipe, null char in before array
		}
	}

	ploc++;

	for(int i = ploc; parg[i] != '\0'; i++)
	{
		after[i - ploc] = parg[i];				//populates after array with arg after pipe
		if(parg[i+1] == '\0')
		{
			after[i+1] = '\0';				//if whats next is null char, null char in after array
		}
	}

	piping(before, after);
}


								//MAIN PROCESS
int main()
{
	while(1)
	{
									//VARIABLES
		char command[MAX_CAP];					//used for user input, for the initial holding before parse
		char *pch;						//for strtok tokens(pointer)
		char name[MAX_CAP];					//used for gethostname
		bool pipe = false;					//boolean for piping
		//int ploc = 0;						//location of pipes; MOVED TO void prepiping
		//int pcnt = 0;						//counts the amount of pipes; NOT USED DELETE LATER
		bool larrow = false;
		bool rarrow = false;
		bool drarrow = false;

									//ERROR CHECKING FOR PROMPT
		char *pid_ln = getlogin();				//error check for getlogin()
		if(pid_ln == NULL)
		{
			perror("getlogin");
			exit(1);
		}
		int pid_hn = gethostname(name, MAX_CAP);		//error check for gethostname()
		if(pid_hn != 0)
		{
			perror("gethostname");
			exit(1);
		}

									//BEGINNING OF SHELL CODE
		cout << getlogin() << "@" << name <<  " $ ";		//cout user prompt, bash prompt
		cin.getline(command, MAX_CAP);				//cin user input
		

		char **arg;						//pointer to pointer of chars
		arg = new char *[MAX_CAP];				//creates new array of size DEFINED
		//arg[1023] = NULL;					//places NULL at second to last slot of array

		for(int i = 0; i < MAX_CAP; i++)
		{
			if(command[i] == '#')
			{
				command[i] = '\0';			//places NULL char when # is found in command
				break;					//ends loop if found
			}
		}

		for(int i = 0; command[i] != '\0'; i++)
		{
			if(command[i] == '|')
			{
				pipe = true;				//sets piping to true after first pipe
			}
		}

		

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
			if(pid_f == 0)					//CHILD
			{
				if(!pipe)
				{
					//begin commands here
					int pid_e = execvp(arg[0], arg);	//error check for system call:execvp()
					if(pid_e == -1)
					{
						perror("execvp");		//if execvp fails to function, exits with error code
						exit(1);
					}
				}
				else if(pipe)
				{
					/*
					for(int i = 0; arg[i] != '\0'; i++)
					{
						if(strcmp(arg[i], "|") == 0)
						{
							ploc = i;	//location of first pipe
							break;
						}
					}
					*/
					prepiping(arg);
				}
			}
			else if(pid_f == -1)				//ERROR
			{
				perror("fork");				//if fork fails to function, exits with error code
				exit(1);
			}
			else						//PARENT
			{
				wait(NULL);				//wait for child

			}
		}
	}
	return 0;
}
