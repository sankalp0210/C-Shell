#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include "headers.h"
void main()
{
	int i=0;
	for(i = 0;i<4e5;i++)
		bgProcess[i][0] = '\0';
	int u = getlogin_r(userName, sizeof(userName));
	getcwd(homeDir, sizeof(homeDir));
	gethostname(hostname, sizeof(hostname));
	homeDirSize = strlen(homeDir);
	int loop = 1;
	mainPID = getpid();

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);

	while(loop)
	{
		childPID = -1;
		signal(SIGCHLD, childSignalHandler);

		printf("<\033[1;32m%s@%s:\033[34;1m", userName, hostname);
		getcwd(currDir, sizeof(currDir));
		printDir();
		printf("\033[0m>");
		break_commands();
	}
	return;
}
void printDir()
{
	int homeDirSize = strlen(homeDir);
	if(!strcmp(currDir, homeDir))
		printf("~");
	else
	{
		if(!strncmp(homeDir, currDir, homeDirSize))
			printf("~%s", &currDir[homeDirSize]);
		else
			printf("%s", currDir);
	}
}
void break_commands()
{
	char s[1024];
	char* array[51];
	for(int i=0;i<sizeof(s);i++) s[i] = '\0';
	for(int i=0;i<51;i++) array[i] = NULL;

	// Taking the input.
	scanf("%[^\n]s", s);
	getchar();
	for(int i=0;i<51;i++) array[i] = NULL;
	char* p = strtok (s, ";");
	int i = 0;
	while(p != NULL) array[i++] = p, p = strtok(NULL, ";");
	i=0;
	while (array[i]!=NULL)
	{
		char* com[51];
		for(int j=0;j<51;j++) com[j] = NULL;
		char* p = strtok (array[i], "|");
		int j = 0;
		while(p != NULL) com[j++] = p, p = strtok(NULL, "|");
		j = 0;
		int fd[2];
		int fdc = 0;
		if(com[1] == NULL)
		{
			command(com[0]);
			i++;
			continue;
		}
		while(com[j]!=NULL)
		{
			pipe(fd);
			
			if(fork()==0)
			{
				dup2(fdc,0);
				if(com[j+1]!=NULL)
				{
					dup2(fd[1],1);
				}
				close(fd[0]);
				command(com[j]);
				exit(0);
			}
			else
			{
				wait(NULL);
				j++;
				fdc = dup(fd[0]);
				close(fd[1]);
			}
		}
		i++;
	}
}
void command(char *s)
{
	char* array[51];
	for(int i=0;i<51;i++) array[i] = NULL;

	// splitting command in tokens.
	int i = 0, out = 0, in = 0, app = 0, fd;
	// char ofile[10][50];
	while(s[i]==' '||s[i]=='\t') s++;
	char* p = strtok (s, " \t");
	i = 0;
	while(p != NULL) array[i++] = p, p = strtok(NULL, " \t");

	if(array[0] == NULL || strcmp(array[0],"\0")==0)
		return;
	
	int stdoutCopy = dup(1);
	int stdinCopy = dup(0);
	for(i=0;array[i]!=NULL;i++)
	{
		if(!strcmp(array[i],"<") && !in)
		{
			in = 1;
			array[i] = NULL;
			fd = open(array[i+1], O_RDONLY, 0);
			if(fd<0)
				perror("error : cannot open file");
			if(dup2(fd,0) < 0)
				perror("error : duping failed");
			close(fd);
		}
		else if(!strcmp(array[i],">") && !out)
		{
			out = 1;
			array[i] = NULL;
			fd = open(array[i+1], O_WRONLY | O_TRUNC | O_CREAT , 0644);
			if(fd<0)
				perror("error : cannot open file");
			if(dup2(fd,1)<0)
				perror("error : duping failed");
			close(fd);
		}
		else if(!strcmp( array[i],">>") && !app)
		{
			app = 1;
			array[i] = NULL;
			fd = open(array[i+1], O_WRONLY | O_APPEND | O_CREAT , 0644);
			if(fd<0)
				perror("error : cannot open file");
			if(dup2(fd,1)<0)
				perror("error : duping failed");
			close(fd);
		}
	}
	strcpy(curProcName, array[0]);
	//checking command for cd
	if(!strcmp(array[0], "cd"))
		cd(array,homeDir);
	//checking command for pwd
	else if(!strcmp(array[0], "pwd"))
		pwd(currDir);
	else if(!strcmp(array[0], "echo"))
		echo(array);
	else if(!strcmp(array[0], "ls"))
		ls(array);
	else if(!strcmp(array[0], "pinfo"))
		pinfo(array);
	else if(!strcmp(array[0], "remindme"))
		remindme(array);
	else if(!strcmp(array[0], "clock"))
		clck(array);
	else if(!strcmp(array[0], "setenv"))
		envset(array);
	else if(!strcmp(array[0], "unsetenv"))
		envunset(array);
	else if(!strcmp(array[0], "overkill"))
		overkill();
	else if(!strcmp(array[0], "jobs"))
		jobs();
	else if(!strcmp(array[0], "kjob"))
		kjob(array);
	else if(!strcmp(array[0], "fg"))
		fg(array[1]);
	else if(!strcmp(array[0], "bg"))
		bg(array[1]);
	else if(!strcmp(array[0], "exit") || !strcmp(array[0], "quit"))
		exit(0);
	else
		otherCommands(array);

	dup2(stdoutCopy,1);
	dup2(stdinCopy,0);
	close(stdoutCopy);
	close(stdinCopy);
}