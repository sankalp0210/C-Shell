#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
extern int homeDirSize;
extern char homeDir[1024];
void pinfo(char** s)
{
	pid_t pid;
	char name[1024];
	char state[10];
	char vsize[20];
	char execpath[1024];
	memset(execpath,'\0',sizeof(execpath));
	if(s[1] == NULL)
		pid = getpid();
	else
		pid = atoi(s[1]);
	printf("pid -- %d\n", pid);
	sprintf(name, "/proc/%d/stat", pid);
	FILE* f = fopen(name, "r");
	if(f)
	{
		int i = 0;
		while(1)
		{
			i++;
			fscanf(f, "%s", name);
			if(i==3)
				strcpy(state,name);
			if(i==23){
				strcpy(vsize,name);
				break;
			}
		}
		fclose(f);
		printf("Process Status -- %s\n", state);
		printf("- %s {Virtual Memory}\n", vsize);
		sprintf(name, "/proc/%d/exe", pid);
		int ret = 0;
		if (ret = readlink(name, execpath, 1024) == -1)
   			perror("ERROR");
  		else
  		{
			if(!strncmp(homeDir, execpath, homeDirSize))
				printf("- Executable Path  - ~%s\n", &execpath[homeDirSize]);
			else
				printf("- Executable Path  - %s\n", execpath);
  		}
	}
	else
	{
		perror("ERROR\n");
		return;
	}
}