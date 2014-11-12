#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stats.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>					//used for file control on the -l flag



using namespace std;

/*
 *  * This is a BARE BONES example of how to use opendir/readdir/closedir.  Notice
 *   * that there is no error checking on these functions.  You MUST add error 
 *    * checking yourself.
 *     */

int main(int argc, char* argv[])
{
	if(argc != 1)					//if there are flags
	{
	}
	else						//if there is only 'ls'
	{
		char* dirn = ".";
		DIR* dirp = opendir(dirn);
		//dirent *direntp;
		if(dirp != NULL)			//assume dirp does not return NULL
		{
			dirent *direntp;
			while((direntp = readdir(dirp)))
			{
				cout << direntp->d_name << endl;
			}
		}
		else					//error check for system call
		{
			perror("opendir");
			exit(1);
		}
	}

	return 0;

	char *dirName = ".";
	DIR *dirp = opendir(dirName);
	dirent *direntp;
	while ((direntp = readdir(dirp)))
	{
		cout << direntp->d_name << endl;	// use stat here to find attributes of file
	}		
    	closedir(dirp);
}

