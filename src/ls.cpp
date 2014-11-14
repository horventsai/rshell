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
#include <pwd.h>
#include <grp.h>


using namespace std;

void rForRec(char* rdirn)
{
	vector<char*> v;
	string base = rdirn;
	char* dirn = rdirn;
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
				exit(1);
			}

			if(direntp->d_name[0] == '.')
			{
				continue;	//skip hidden files
			}
			struct stat buf;
			if(stat(dirn, &buf) == -1)
			{
				perror("stat");
				exit(1);
			}

			char nextf[1024];
			strcpy(nextf, dirn);
			strcat(nextf, "/");
			strcat(nextf, direntp->d_name);
			cout << direntp->d_name << " ";

			if(stat(nextf, &buf) == -1)
			{
				perror("stat");
				exit(1);
			}

			if(S_ISDIR(buf.st_mode))
			{
				v.push_back(direntp->d_name);
			}
		}
		cout << endl;

		unsigned vsize = v.size();

		for(unsigned i = 0; i < vsize; i++)
		{
			string next = (base+"/"+v.at(i));
			char* n = new char[next.length() + 1];
			strncpy(n, next.c_str(),next.length());
			rForRec(n);
		}

		if(closedir(dirp) == -1)
		{
			perror("closedir");	//error check for system call
			exit(1);
		}

		return;				//to get out of function for recursion
	}
	else					//error check for system call
	{
		perror("opendir");
		exit(1);
	}
}


void raForRecA(char* rdirn)
{
	vector<char*> v;
	string base = rdirn;
	char* dirn = rdirn;
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
				exit(1);
			}
			/*
			if(direntp->d_name[0] == '.')
			{
				continue;	//skip hidden files
			}
			*/
			struct stat buf;
			if(stat(dirn, &buf) == -1)
			{
				perror("stat");
				exit(1);
			}

			char nextf[1024];
			strcpy(nextf, dirn);
			strcat(nextf, "/");
			strcat(nextf, direntp->d_name);
			cout << direntp->d_name << " ";

			if(stat(nextf, &buf) == -1)
			{
				perror("stat");
				exit(1);
			}

			if(S_ISDIR(buf.st_mode))
			{
				v.push_back(direntp->d_name);
			}
		}
		cout << endl;

		unsigned vsize = v.size();

		for(unsigned i = 0; i < vsize; i++)
		{
			string next = (base+"/"+v.at(i));
			char* n = new char[next.length() + 1];
			strncpy(n, next.c_str(),next.length());
			rForRec(n);
		}

		if(closedir(dirp) == -1)
		{
			perror("closedir");	//error check for system call
			exit(1);
		}

		return;				//to get out of function for recursion
	}
	else					//error check for system call
	{
		perror("opendir");
		exit(1);
	}
}


void rlForRecL(char* rdirn)
{
	vector<char*> v;
	string base = rdirn;
	char* dirn = rdirn;
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
				exit(1);
			}

			if(direntp->d_name[0] == '.')
			{
				continue;	//skip hidden files
			}
			struct stat buf;
			if(stat(dirn, &buf) == -1)
			{
				perror("stat");
				exit(1);
			}

			//below

								//print filetype
					if(S_ISREG(buf.st_mode))
					{
						cout << "-";	//regular file
					}
					else if(S_ISDIR(buf.st_mode))
					{
						cout << "d";	//directory
					}
					else if(S_ISCHR(buf.st_mode))
					{
						cout << "c";	//character device
					}
					else if(S_ISBLK(buf.st_mode))
					{
						cout << "b";	//block device
					}
					else if(S_ISFIFO(buf.st_mode))
					{
						cout << "p";	//named pipe
					}
					else if(S_ISLNK(buf.st_mode))
					{
						cout << "l";	//symbolic link
					}
					else if(S_ISSOCK(buf.st_mode))
					{
						cout << "s";	//socket
					}

								//user permissions
					if(buf.st_mode & S_IRUSR)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWUSR)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXUSR)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

								//group permissions
					if(buf.st_mode & S_IRGRP)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWGRP)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXGRP)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

								//general permissions
					if(buf.st_mode & S_IROTH)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWOTH)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXOTH)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

					cout << " ";

					cout << buf.st_nlink;	//number of hard links

					cout << " ";

								//user id
					string uid;
					uid = getpwuid(buf.st_uid)->pw_name;
					if(errno != 0)
					{
						perror("uid");	//error check for system call
						exit(1);
					}

								//group id
					string gid;
					gid = getgrgid(buf.st_gid)->gr_name;
					if(errno != 0)
					{
						perror("gid");	//error check for system call
						exit(1);
					}

					cout << uid;		//print user id
				       
					cout << " ";

				       	cout << gid;		//print group id

					cout << " ";

					cout << buf.st_size;	//print size of file

					cout << " ";

								//get modified time
					time_t modtime = buf.st_mtime;
					struct tm time;

					if(localtime_r(&modtime, &time) == NULL)
					{
						perror("time");	//error check for system call
						exit(1);
					}

					char timeslots[512];
					strftime(timeslots, sizeof(timeslots), "%h", &time);
					cout << timeslots;	//print month abrev.
					cout << " ";
					strftime(timeslots, sizeof(timeslots), "%d", &time);
					cout << timeslots;	//print date
					cout << " ";
					strftime(timeslots, sizeof(timeslots), "%R", &time);
					cout << timeslots;	//print 24hr
					cout << " ";
			//above

			char nextf[1024];
			strcpy(nextf, dirn);
			strcat(nextf, "/");
			strcat(nextf, direntp->d_name);

			cout << direntp->d_name;
			cout << endl;

			if(stat(nextf, &buf) == -1)
			{
				perror("stat");
				exit(1);
			}

			if(S_ISDIR(buf.st_mode))
			{
				v.push_back(direntp->d_name);
			}
		}
		cout << endl;

		unsigned vsize = v.size();

		for(unsigned i = 0; i < vsize; i++)
		{
			string next = (base+"/"+v.at(i));
			char* n = new char[next.length() + 1];
			strncpy(n, next.c_str(),next.length());
			rForRec(n);
		}

		if(closedir(dirp) == -1)
		{
			perror("closedir");	//error check for system call
			exit(1);
		}

		return;				//to get out of function for recursion
	}
	else					//error check for system call
	{
		perror("opendir");
		exit(1);
	}
}


void rlaForRecLA(char* rdirn)
{
	vector<char*> v;
	string base = rdirn;
	char* dirn = rdirn;
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
				exit(1);
			}
			
			/*
			if(direntp->d_name[0] == '.')
			{
				continue;	//skip hidden files
			}
			*/
			struct stat buf;
			if(stat(dirn, &buf) == -1)
			{
				perror("stat");
				exit(1);
			}

			char nextf[1024];
			strcpy(nextf, dirn);
			strcat(nextf, "/");
			strcat(nextf, direntp->d_name);
			//below


								//print filetype
					if(S_ISREG(buf.st_mode))
					{
						cout << "-";	//regular file
					}
					else if(S_ISDIR(buf.st_mode))
					{
						cout << "d";	//directory
					}
					else if(S_ISCHR(buf.st_mode))
					{
						cout << "c";	//character device
					}
					else if(S_ISBLK(buf.st_mode))
					{
						cout << "b";	//block device
					}
					else if(S_ISFIFO(buf.st_mode))
					{
						cout << "p";	//named pipe
					}
					else if(S_ISLNK(buf.st_mode))
					{
						cout << "l";	//symbolic link
					}
					else if(S_ISSOCK(buf.st_mode))
					{
						cout << "s";	//socket
					}

								//user permissions
					if(buf.st_mode & S_IRUSR)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWUSR)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXUSR)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

								//group permissions
					if(buf.st_mode & S_IRGRP)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWGRP)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXGRP)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

								//general permissions
					if(buf.st_mode & S_IROTH)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWOTH)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXOTH)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

					cout << " ";

					cout << buf.st_nlink;	//number of hard links

					cout << " ";

								//user id
					string uid;
					uid = getpwuid(buf.st_uid)->pw_name;
					if(errno != 0)
					{
						perror("uid");	//error check for system call
						exit(1);
					}

								//group id
					string gid;
					gid = getgrgid(buf.st_gid)->gr_name;
					if(errno != 0)
					{
						perror("gid");	//error check for system call
						exit(1);
					}

					cout << uid;		//print user id
				       
					cout << " ";

				       	cout << gid;		//print group id

					cout << " ";

					cout << buf.st_size;	//print size of file

					cout << " ";

								//get modified time
					time_t modtime = buf.st_mtime;
					struct tm time;

					if(localtime_r(&modtime, &time) == NULL)
					{
						perror("time");	//error check for system call
						exit(1);
					}

					char timeslots[512];
					strftime(timeslots, sizeof(timeslots), "%h", &time);
					cout << timeslots;	//print month abrev.
					cout << " ";
					strftime(timeslots, sizeof(timeslots), "%d", &time);
					cout << timeslots;	//print date
					cout << " ";
					strftime(timeslots, sizeof(timeslots), "%R", &time);
					cout << timeslots;	//print 24hr
					cout << " ";


			//above
			cout << direntp->d_name;;
			cout << endl;

			if(stat(nextf, &buf) == -1)
			{
				perror("stat");
				exit(1);
			}

			if(S_ISDIR(buf.st_mode))
			{
				v.push_back(direntp->d_name);
			}
		}
		cout << endl;

		unsigned vsize = v.size();

		for(unsigned i = 0; i < vsize; i++)
		{
			string next = (base+"/"+v.at(i));
			char* n = new char[next.length() + 1];
			strncpy(n, next.c_str(),next.length());
			rForRec(n);
		}

		if(closedir(dirp) == -1)
		{
			perror("closedir");	//error check for system call
			exit(1);
		}

		return;				//to get out of function for recursion
	}
	else					//error check for system call
	{
		perror("opendir");
		exit(1);
	}
}

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
		string add = ".";
		char* dirn = new char[add.length() + 1];
		strncpy(dirn, add.c_str(),add.length());
		//char* dirn = ".";

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
			//dirn = ".";
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
						exit(1);
					}

					if(direntp->d_name[0] == '.')
					{
						continue;	//skip hidden files
					}
					struct stat buf;
					if(stat(dirn, &buf) == -1)
					{
						perror("stat");
						exit(1);
					}
					cout << direntp->d_name << " ";
				}
				cout << endl;
				if(closedir(dirp) == -1)
				{
					perror("closedir");	//error check for system call
					exit(1);
				}
			}
			else					//error check for system call
			{
				perror("opendir");
				exit(1);
			}
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
						exit(1);
					}
					struct stat buf;
					if(stat(dirn, &buf) == -1)
					{
						perror("stat");
						exit(1);
					}
					cout << direntp->d_name << " ";
				}
				cout << endl;
				if(closedir(dirp) == -1)
				{
					perror("closedir");	//error check for system call
					exit(1);
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
			//dirn = ".";
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
						exit(1);
					}

					if(direntp->d_name[0] == '.')
					{
						continue;	//skip hidden files
					}
					struct stat buf;
					if(stat(dirn, &buf) == -1)
					{
						perror("stat");
						exit(1);
					}

								//print filetype
					if(S_ISREG(buf.st_mode))
					{
						cout << "-";	//regular file
					}
					else if(S_ISDIR(buf.st_mode))
					{
						cout << "d";	//directory
					}
					else if(S_ISCHR(buf.st_mode))
					{
						cout << "c";	//character device
					}
					else if(S_ISBLK(buf.st_mode))
					{
						cout << "b";	//block device
					}
					else if(S_ISFIFO(buf.st_mode))
					{
						cout << "p";	//named pipe
					}
					else if(S_ISLNK(buf.st_mode))
					{
						cout << "l";	//symbolic link
					}
					else if(S_ISSOCK(buf.st_mode))
					{
						cout << "s";	//socket
					}

								//user permissions
					if(buf.st_mode & S_IRUSR)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWUSR)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXUSR)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

								//group permissions
					if(buf.st_mode & S_IRGRP)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWGRP)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXGRP)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

								//general permissions
					if(buf.st_mode & S_IROTH)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWOTH)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXOTH)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

					cout << " ";

					cout << buf.st_nlink;	//number of hard links

					cout << " ";

								//user id
					string uid;
					uid = getpwuid(buf.st_uid)->pw_name;
					if(errno != 0)
					{
						perror("uid");	//error check for system call
						exit(1);
					}

								//group id
					string gid;
					gid = getgrgid(buf.st_gid)->gr_name;
					if(errno != 0)
					{
						perror("gid");	//error check for system call
						exit(1);
					}

					cout << uid;		//print user id
				       
					cout << " ";

				       	cout << gid;		//print group id

					cout << " ";

					cout << buf.st_size;	//print size of file

					cout << " ";

								//get modified time
					time_t modtime = buf.st_mtime;
					struct tm time;

					if(localtime_r(&modtime, &time) == NULL)
					{
						perror("time");	//error check for system call
						exit(1);
					}

					char timeslots[512];
					strftime(timeslots, sizeof(timeslots), "%h", &time);
					cout << timeslots;	//print month abrev.
					cout << " ";
					strftime(timeslots, sizeof(timeslots), "%d", &time);
					cout << timeslots;	//print date
					cout << " ";
					strftime(timeslots, sizeof(timeslots), "%R", &time);
					cout << timeslots;	//print 24hr
					cout << " ";

					cout << direntp->d_name << " ";
					cout << endl;
				}
				cout << endl;
				if(closedir(dirp) == -1)
				{
					perror("closedir");	//error check for system call
					exit(1);
				}
			}
			else					//error check for system call
			{
				perror("opendir");
				exit(1);
			}
		}
		else if(!a_flag && !l_flag && R_flag)	//only R flag is active
		{
								//needs function call b/c recursion
			rForRec(dirn);
			/*
			//dirn = ".";
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
						exit(1);
					}

					if(direntp->d_name[0] == '.')
					{
						continue;	//skip hidden files
					}
					struct stat buf;
					if(stat(dirn, &buf) == -1)
					{
						perror("stat");
						exit(1);
					}
					cout << direntp->d_name << " ";
				}
				cout << endl;
				if(closedir(dirp) == -1)
				{
					perror("closedir");	//error check for system call
					exit(1);
				}
			}
			else					//error check for system call
			{
				perror("opendir");
				exit(1);
			}
			*/
		}
		else if(a_flag && l_flag && !R_flag)	//only al flag is active
		{

			//dirn = ".";
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
						exit(1);
					}
					/*
					if(direntp->d_name[0] == '.')
					{
						continue;	//skip hidden files
					}
					*/
					struct stat buf;
					if(stat(dirn, &buf) == -1)
					{
						perror("stat");
						exit(1);
					}

								//print filetype
					if(S_ISREG(buf.st_mode))
					{
						cout << "-";	//regular file
					}
					else if(S_ISDIR(buf.st_mode))
					{
						cout << "d";	//directory
					}
					else if(S_ISCHR(buf.st_mode))
					{
						cout << "c";	//character device
					}
					else if(S_ISBLK(buf.st_mode))
					{
						cout << "b";	//block device
					}
					else if(S_ISFIFO(buf.st_mode))
					{
						cout << "p";	//named pipe
					}
					else if(S_ISLNK(buf.st_mode))
					{
						cout << "l";	//symbolic link
					}
					else if(S_ISSOCK(buf.st_mode))
					{
						cout << "s";	//socket
					}

								//user permissions
					if(buf.st_mode & S_IRUSR)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWUSR)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXUSR)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

								//group permissions
					if(buf.st_mode & S_IRGRP)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWGRP)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXGRP)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

								//general permissions
					if(buf.st_mode & S_IROTH)
					{
						cout << "r";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IWOTH)
					{
						cout << "w";
					}
					else
					{
						cout << "-";
					}
					if(buf.st_mode & S_IXOTH)
					{
						cout << "x";
					}
					else
					{
						cout << "-";
					}

					cout << " ";

					cout << buf.st_nlink;	//number of hard links

					cout << " ";

								//user id
					string uid;
					uid = getpwuid(buf.st_uid)->pw_name;
					if(errno != 0)
					{
						perror("uid");	//error check for system call
						exit(1);
					}

								//group id
					string gid;
					gid = getgrgid(buf.st_gid)->gr_name;
					if(errno != 0)
					{
						perror("gid");	//error check for system call
						exit(1);
					}

					cout << uid;		//print user id
				       
					cout << " ";

				       	cout << gid;		//print group id

					cout << " ";

					cout << buf.st_size;	//print size of file

					cout << " ";

								//get modified time
					time_t modtime = buf.st_mtime;
					struct tm time;

					if(localtime_r(&modtime, &time) == NULL)
					{
						perror("time");	//error check for system call
						exit(1);
					}

					char timeslots[512];
					strftime(timeslots, sizeof(timeslots), "%h", &time);
					cout << timeslots;	//print month abrev.
					cout << " ";
					strftime(timeslots, sizeof(timeslots), "%d", &time);
					cout << timeslots;	//print date
					cout << " ";
					strftime(timeslots, sizeof(timeslots), "%R", &time);
					cout << timeslots;	//print 24hr
					cout << " ";

					cout << direntp->d_name << " ";
					cout << endl;
				}
				cout << endl;
				if(closedir(dirp) == -1)
				{
					perror("closedir");	//error check for system call
					exit(1);
				}
			}
			else					//error check for system call
			{
				perror("opendir");
				exit(1);
			}
		}
		else if(a_flag && !l_flag && R_flag)	//only aR flag is active
		{
			raForRecA(dirn);
		}
		else if(!a_flag && l_flag && R_flag)	//only lR flag is active
		{

			rlForRecL(dirn);
		}
		else if(a_flag && l_flag && R_flag)	//all alR flags are active
		{

			rlaForRecLA(dirn);
		}
							//end of flac controls/commands
	}
	else						//if there is only 'ls'
	{
		string add = ".";
		char* dirn = new char[add.length() + 1];
		strncpy(dirn, add.c_str(),add.length());
		//char* dirn = ".";
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
					exit(1);
				}

				if(direntp->d_name[0] == '.')
				{
					continue;	//skip hidden files
				}
				struct stat buf;
				if(stat(dirn, &buf) == -1)
				{
					perror("stat");
					exit(1);
				}
				cout << direntp->d_name << " ";
			}
			cout << endl;
			if(closedir(dirp) == -1)
			{
				perror("closedir");	//error check for system call
				exit(1);
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

