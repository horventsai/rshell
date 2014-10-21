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
		string command;
		cout << "$ ";
		getline(cin, command);
	}
	return 0;
}
