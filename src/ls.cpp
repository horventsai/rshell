#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
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
		char* dirn = ".";

		for(int i = 1; i < argc; i++)
		{
			v.push_back(argv[i]);		//pushes commands flags and such into vector
		}

		int vsize = v.size();			//declares and sets variable for vector size
							//after vector is "filled"

							//every possible combination of flags in v.at
		for(int i = 0; i < vsize; i++)		//loop through the vector to determine flags
		{
			/*
			if(a_flag && l_flag && R_flag)
			{
				break;				//exit loop if all flags are true
			}
			*/

			if(strcmp(v.at(i), "-a") == 0)		//if flag is a
			{
				if(!a_flag)
				{
					a_flag = true;
				}
			}
			else if(strcmp(v.at(i), "-l") == 0)	//if flag is l
			{
				if(!l_flag)
				{
					l_flag = true;
				}
			}
			else if(strcmp(v.at(i), "-R") == 0)	//if flag is R
			{
				if(!R_flag)
				{
					R_flag = true;
				}
			}
			else if(strcmp(v.at(i), "-al") == 0)	//if flag is al combo1
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
			else if(strcmp(v.at(i), "-la") == 0)	//if flag is al combo2
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
			else if(strcmp(v.at(i), "-aR") == 0)	//if flag is aR combo1
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
			else if(strcmp(v.at(i), "-Ra") == 0)	//if flag is aR combo2
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
			else if(strcmp(v.at(i), "-lR") == 0)	//if flag is lR combo1
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
			else if(strcmp(v.at(i), "-Rl") == 0)	//if flag is lR combo2
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
			else if(strcmp(v.at(i), "-alR") == 0)	//if flag is alR combo1
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
			else if(strcmp(v.at(i), "-lRa") == 0)	//if flag is alR combo2
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
			else if(strcmp(v.at(i), "-Ral") == 0)	//if flag is alR combo3
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
			else if(strcmp(v.at(i), "-aRl") == 0)	//if flag is alR combo4
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
			else if(strcmp(v.at(i), "-laR") == 0)	//if flag is alR combo5
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
			else if(strcmp(v.at(i), "-Rla") == 0)	//if flag is alR combo6
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
			else
			{
				if(argc > 1)
				{
					dirn = v.at(i);
				}
			}
		}					//end of for loop to check for flags

							//execute flag controls/commands
		if(!a_flag && !l_flag && !R_flag)	//all flags are inactive
		{
		}
		else if(a_flag && !l_flag && !R_flag)	//only a flag is active
		{
			DIR* dirp = opendir(dirn);
			//dirent *direntp;
			if(dirp != NULL)			//assume dirp does not return NULL
			{
				dirent *direntp;
				while((direntp = readdir(dirp)))
				{
					if(errno != 0)		//error check for system call
					{
						perror("readdir");
					}
					struct stat buf;
					if(stat(dirn, &buf) == -1)
					{
						perror("stat");
					}
					cout << direntp->d_name << " ";
				}
				cout << endl;
				if(closedir(dirp) == -1)
				{
					perror("closedir");	//error check for system call
				}
			}
			else					//error check for system call
			{
				perror("opendir");
				exit(1);
			}
		}
		else if(!a_flag && l_flag && !R_flag)	//only l flag is active
		{
		}
		else if(!a_flag && !l_flag && R_flag)	//only R flag is active
		{
		}
		else if(a_flag && l_flag && !R_flag)	//only al flag is active
		{
		}
		else if(a_flag && !l_flag && R_flag)	//only aR flag is active
		{
		}
		else if(!a_flag && l_flag && R_flag)	//only lR flag is active
		{
		}
		else if(a_flag && l_flag && R_flag)	//all alR flags are active
		{
		}
							//end of flac controls/commands
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
				if(errno != 0)		//error check for system call
				{
					perror("readdir");
				}

				if(direntp->d_name[0] == '.')
				{
					continue;	//skip hidden files
				}
				struct stat buf;
				if(stat(dirn, &buf) == -1)
				{
					perror("stat");
				}
				cout << direntp->d_name << " ";
			}
			cout << endl;
			if(closedir(dirp) == -1)
			{
				perror("closedir");	//error check for system call
			}
		}
		else					//error check for system call
		{
			perror("opendir");
			exit(1);
		}
	}

	return 0;

							//sample code given to us by specs
	/*
	char *dirName = ".";
	DIR *dirp = opendir(dirName);
	dirent *direntp;
	while ((direntp = readdir(dirp)))
	{
		cout << direntp->d_name << endl;	// use stat here to find attributes of file
	}		
    	closedir(dirp);
	*/
}

