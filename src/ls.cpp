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

