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

		if(!strcmp(command,"exit"))
		{
			exit(0);
		}
	}
	return 0;
}
