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
		char command[] = "test this is a string test to work with";
		char *pch;
		vector<string> holding;
		char *name;
		size_t len;

		cout << getlogin() << "@" << gethostname(name, len) <<  " $ ";
		getline(cin, command);
		
		pch = strtok(command, " \t\n\r");

		while(pch != NULL)
		{
			holding.push_back(pch);
			pch = strtok(NULL, " \t\n\r");
		}
		
		for(int i = 0; i < holding.size(); i++)
		{
			cout << holding.at(i) << " ";
		}
		
		if(command == "exit")
		{
			exit(0);
		}
	}
	return 0;
}
