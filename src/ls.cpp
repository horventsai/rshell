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
							//declared variables
		vector<char*> v;			//create vector to parse flags and commands
		bool a_flag = false;
		bool l_flag = false;
		bool R_flag = false;


		for(int i = 1; i < argc; i++)
		{
			v.push_back(argv[i]);		//pushes commands flags and such into vector
		}

		int vsize = v.size();			//declares and sets variable for vector size
							//after vector is "filled"

							//every possible combination of flags in v.at
		for(int i = 0; i < v.size(); i++)	//loop through the vector to determine flags
		{
			if(v.at(i) == "-a")		//if flag is a
			{
				if(!a_flag)
				{
					a_flag = true;
				}
			}
			else if(v.at(i) == "-l")	//if flag is l
			{
				if(!l_flag)
				{
					l_flag = true;
				}
			}
			else if(v.at(i) == "-R")	//if flag is R
			{
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-al")	//if flag is al combo1
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!l_flag)
				{
					l_flag = true;
				}
			}
			else if(v.at(i) == "-la")	//if flag is al combo2
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!l_flag)
				{
					l_flag = true;
				}
			}
			else if(v.at(i) == "-aR")	//if flag is aR combo1
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-Ra")	//if flag is aR combo2
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-lR")	//if flag is lR combo1
			{
				if(!l_flag)
				{
					l_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-Rl")	//if flag is lR combo2
			{
				if(!l_flag)
				{
					l_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-alR")	//if flag is alR combo1
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!l_flag)
				{
					l_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-lRa")	//if flag is alR combo2
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!l_flag)
				{
					l_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-Ral")	//if flag is alR combo3
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!l_flag)
				{
					l_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-aRl")	//if flag is alR combo4
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!l_flag)
				{
					l_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-laR")	//if flag is alR combo5
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!l_flag)
				{
					l_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(v.at(i) == "-Rla")	//if flag is alR combo6
			{
				if(!a_flag)
				{
					a_flag = true;
				}
				if(!l_flag)
				{
					l_flag = true;
				}
				if(!R_flag)
				{
					R_flag = true;
				}
			}
		}
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

