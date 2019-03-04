#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

void ls(char** s)
{
	int i = 1, flagL = 0, flagA = 0, n = 0;
	char* dir[51]; 
	for(int i=0;i<51;i++) dir[i] = NULL;
	while(s[i] != NULL)
	{
		if(s[i][0] == '-')
		{
			int l = strlen(s[i]);
			for(int j=1;s[i][j] != '\0';j++)
			{
				if(s[i][j] == 'l')
					flagL = 1;
				if(s[i][j] == 'a')
					flagA = 1;
			}
		}
		else
			dir[n++] = s[i];
		i++;
	}
	i = 0;
	if(dir[0] == NULL)
		dir[0] = ".";
	while(dir[i] != NULL)
	{
	    DIR *mydir;
	    struct dirent *myfile;
	    struct stat mystat;
	    char buf[512];
	    int exist = stat(dir[i], &mystat);
	    if(exist != 0)
	    {
	    	printf("%s : No such file or directory\n", dir[i++]);
	    	continue;
	    }
	    mydir = opendir(dir[i]);
	    if(dir[1] != NULL)
	    	printf("%s:\n", dir[i]);
	    if(!flagL)
	    {
		    while((myfile = readdir(mydir)) != NULL)
		    {
		    	sprintf(buf, "%s/%s", dir[i], myfile->d_name);
		    	stat(buf, &mystat);
		    	int fileMode;
		    	fileMode = mystat.st_mode;

		    	if(!flagA && myfile->d_name[0] == '.')
		    		continue;
		       	if(S_ISDIR(fileMode))
		       		printf("\033[1;34m");
		        printf("%s\n\033[0m", myfile->d_name);
		    }
		    printf("\n");
	    } 
	    else
	    {
	    	while((myfile = readdir(mydir)) != NULL)
		    {
		    	if(!flagA && myfile->d_name[0] == '.')
		    		continue;
		    	sprintf(buf, "%s/%s", dir[i], myfile->d_name);
        		stat(buf, &mystat);
		    	int fileMode;
		    	fileMode = mystat.st_mode;

			    printf(S_ISDIR(fileMode) ? "d" : "-");
	    	    /* Check owner permissions of file */  
			    printf(fileMode & S_IRUSR ? "r" : "-");
			    printf(fileMode & S_IWUSR ? "w" : "-");
			    printf(fileMode & S_IXUSR ? "x" : "-");
			    /* Check group permissions of file */
			    printf(fileMode & S_IRGRP ? "r" : "-");
			    printf(fileMode & S_IWGRP ? "w" : "-");
			    printf(fileMode & S_IXGRP ? "x" : "-");
			    /* Check others permissions of file */
			    printf(fileMode & S_IROTH ? "r" : "-");
			    printf(fileMode & S_IWOTH ? "w" : "-");
			    printf(fileMode & S_IXOTH ? "x " : "- ");

		       	printf("%3ld ", mystat.st_nlink);

		       	struct passwd *pw = getpwuid(mystat.st_uid);
    			struct group  *gr = getgrgid(mystat.st_gid);
    			printf("%s %s ", pw->pw_name, gr->gr_name);
       			
       			printf("%8zu ",mystat.st_size);

       			char date[20];
       			strftime(date, 20, "%b %2d %H:%M", localtime(&(mystat.st_ctime)));
		       	printf("%s ", date);
		       	if(S_ISDIR(fileMode))
		       		printf("\033[1;34m");
		       	printf("%s\n\033[0m", myfile->d_name);
		    }
		    printf("\n");
	    }
	    closedir(mydir);
	    i++;
	}
}