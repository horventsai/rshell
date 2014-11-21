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
//exit(0) = exit with no error
//exit(1) = exit with error
//exit(2) = exit from child process

								//HELPER PROTOTYPES
void piping(char **before, char **after);
void prepiping(char **parg, bool pipe);
void depipe(char **args);
void ioredir(char **ar);
								//HELPER FUNCTIONS
void piping(char **before, char **after)
{
	bool pipes = false;

	for(int i = 0; after[i] != '\0'; i++)
	{
		if(strcmp(after[i], "|") == 0)
		{
			pipes = true;					//more pipes after
			break;
		}
	}

	int fd[2];
	if(pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}

	int pid = fork();
	if(pid == 0)							//CHILD
	{
		if(dup2(fd[1],1) == -1)
		{
			perror("dup2");
			exit(1);
		}
		if(close(fd[0]) == -1)
		{
			perror("close");
			exit(1);
		}
		if(execvp(before[0], before) == -1)
		{
			perror("execvp");
			exit(1);
		}
		exit(2);
	}
	else if(pid == -1)						//ERROR
	{
		perror("fork");
		exit(1);
	}

	int savestdin;

	if((savestdin = dup(0)) == -1)
	{
		perror("dup");
		exit(1);
	}
	if(dup2(fd[0],0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if(close(fd[1]) == -1)
	{
		perror("close");
		exit(1);
	}
	if(wait(0) == -1)
	{
		perror("wait");
		exit(1);
	}

	prepiping(after,pipes);

	if(dup2(savestdin,0) == -1)
	{
		perror("dup2");
		exit(1);
	}
}

void prepiping(char **parg, bool pipe)
{
									//VARIABLES
	int ploc = 0;							//location of pipes
	char **before;
	char **after;
	before = new char *[SUB_MAX];
	after = new char *[SUB_MAX];

									//PROCESS
	if(pipe)
	{
		for(int i = 0; parg[i] != '\0'; i++)
		{
			if(strcmp(parg[i], "|") == 0)
			{
				ploc = i;				//location of first pipe
				break;
			}
		}

		for(int i = 0; i < ploc; i++)
		{
			before[i] = parg[i];				//populates before array with arg before pipe
			if((i+1) == ploc)
			{
				before[i+1] = '\0';			//if whats next = pipe, null char in before array
			}
		}

		ploc++;

		for(int i = ploc; parg[i] != '\0'; i++)
		{
			after[i - ploc] = parg[i];			//populates after array with arg after pipe
			if(parg[i+1] == '\0')
			{
				after[i+1] = '\0';			//if whats next is null char, null char in after array
			}
		}

		piping(before, after);
	}
	else
	{
		depipe(parg);
	}

	delete []before;
	delete []after;
}

void depipe(char **args)
{

	bool larrow = false;						//boolean for left arrow <
	bool rarrow = false;						//boolean for right arrow >
	bool drarrow = false;						//boolean for double right arrow >>
	//bool tlarrow = false;						//boolean for triple left arrow <<<

	for(int i = 0; args[i] != '\0'; i++)
	{
		if(strcmp(args[i], "<"))
		{
			larrow = true;					//sets < to true after <
		}
		if(strcmp(args[i], ">"))
		{
			rarrow = true;					//sets > to true after >
		}
		if(strcmp(args[i], ">>"))
		{
			drarrow = true;					//sets >> to true after >>
		}
	}

	if(larrow || rarrow || drarrow)
	{
		ioredir(args);
	}
	else
	{
		int pid_f = fork();					//error check for system call:fork()
		if(pid_f == 0)						//CHILD
		{
			//begin commands here
			if(execvp(args[0], args) == -1)			//error check for system call:execvp()
			{
				perror("execvp");			//if execvp fails to function, exits with error code
				exit(1);
			}
		
			exit(2);
		}
		else if(pid_f == -1)					//ERROR
		{
			perror("fork");					//if fork fails to function, exits with error code
			exit(1);
		}
		else							//PARENT
		{
			if(wait(0) == -1)				//wait for child
			{
				perror("wait");
				exit(1);
			}
		}
	}
}

void ioredir(char **ar)
{
	int pid_f = fork();						//error check for system call:fork()
	if(pid_f == 0)							//CHILD
	{
		//begin commands here
		//BELOW
		for(int i = 0; ar[i] != '\0'; i++)
		{
									//op code here for the ioredirection
			int fd;
			int chk;
			if(!strcmp(ar[i], "<"))				//<
			{
				ar[i] = '\0';
				fd = open(ar[i+1], O_RDONLY);
				if(fd == -1)
				{
					perror("open");
					exit(1);
				}
				chk = dup2(fd,0);
				if(chk == -1)
				{
					perror("dup2");
					exit(1);
				}

				break;
			}
			if(!strcmp(ar[i], ">"))				//>
			{
				ar[i] = NULL;
				fd = open(ar[i+1], O_CREAT|O_WRONLY|O_TRUNC, 0666);
				if(fd == -1)
				{
					perror("open");
					exit(1);
				}
				chk = dup2(fd,1);
				if(chk == -1)
				{
					perror("dup2");
					exit(1);
				}

				break;
			}
			if(!strcmp(ar[i], ">>"))				//>>
			{
				ar[i] = NULL;
				fd = open(ar[i+1], O_CREAT|O_WRONLY|O_APPEND, 0666);
				if(fd == -1)
				{
					perror("open");
					exit(1);
				}
				chk = dup2(fd,1);
				if(chk == -1)
				{
					perror("dup2");
					exit(1);
				}

				break;
			}
		}
		//ABOVE
		if(execvp(ar[0], ar) == -1)				//error check for system call:execvp()
		{
			perror("execvp");				//if execvp fails to function, exits with error code
			exit(1);
		}
	
		exit(2);
	}
	else if(pid_f == -1)						//ERROR
	{
		perror("fork");						//if fork fails to function, exits with error code
		exit(1);
	}
	else								//PARENT
	{
		if(wait(0) == -1)					//wait for child
		{
			perror("wait");
			exit(1);
		}
	}
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
		bool pipe = false;					//boolean for piping |
		bool larrow = false;					//boolean for left arrow <
		bool rarrow = false;					//boolean for right arrow >
		bool drarrow = false;					//boolean for double right arrow >>
		bool tlarrow = false;					//boolean for triple left arrow <<<

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
				break;
			}
		}


		for(int i = 0; command[i] != '\0'; i++)
		{
			if(command[i] == '<')
			{
				larrow = true;					//sets < to true after <
			}
			if((command[i] == '>') && (command[i+1] != '>'))
			{
				rarrow = true;					//sets > to true after >
			}
			if((command[i] == '>') && (command[i+1] == '>'))
			{
				drarrow = true;					//sets >> to true after >>
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
				if(!pipe && !larrow && !rarrow && !drarrow && !tlarrow)
				{
					//begin commands here
					if(execvp(arg[0], arg) == -1)	//error check for system call:execvp()
					{
						perror("execvp");	//if execvp fails to function, exits with error code
						exit(1);
					}
				}
				else if(pipe)
				{
					prepiping(arg,pipe);
				}
				else if(!pipe && (larrow || rarrow || drarrow || tlarrow))
				{
					ioredir(arg);
				}
				else if(pipe || larrow || rarrow || drarrow || tlarrow)
				{
					prepiping(arg,pipe);
				}
				exit(2);
			}
			else if(pid_f == -1)				//ERROR
			{
				perror("fork");				//if fork fails to function, exits with error code
				exit(1);
			}
			else						//PARENT
			{
				if(wait(0) == -1)			//wait for child
				{
					perror("wait");
					exit(1);
				}
			}
		}
	}

	return 0;
}
