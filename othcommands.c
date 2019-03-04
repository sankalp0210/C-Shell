#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
extern int bgcount;
extern int flagc;
extern int flagz;
extern int childPID;
extern char bgProcess[400005][256];
extern void execCTRL_C(int sig);
extern void execCTRL_Z(int sig);
extern char curProcName[100];

void otherCommands(char** s)
{
	pid_t pid;
    int status;
	int flag = 0;
	int len=0;
	while(s[len]!= NULL)len++;
    if(s[len-1] != NULL && s[len-1][0] == '&')
		s[len - 1] = NULL, flag = 1;

    pid = fork();
    childPID = pid;
    if (pid < 0)
    {     
        perror("ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // flagz = 0;
    	if (execvp(s[0], s) < 0)
            perror("ERROR: exec failed\n");
    }
    else
    {
        if(!flag)
		{
            flagz = 0;
            flagc = 0;
            signal(SIGTSTP, execCTRL_Z);
	        signal(SIGINT, execCTRL_C);
	    	while (!flagz && !flagc && waitpid(pid,&status,WNOHANG) != pid);
            if(flagc){
                kill(pid,9);
                wait(NULL);
            }
            if(flagz)
            {
                setpgid(pid,pid);
                kill(pid,SIGSTOP);
			    sprintf(bgProcess[pid],"%s with pid %d exited normally.", curProcName, pid);
                bgcount++;
                signal(SIGCHLD, SIG_IGN);
            }
            flagc = 0;
            flagz = 0;
		}
		else
        {
            setpgid(pid,pid);
			signal(SIGCHLD,SIG_IGN);
			sprintf(bgProcess[pid],"%s with pid %d exited normally.", s[0], pid);
        	printf("[%d] %d\n", ++bgcount, pid);
            signal(SIGCHLD, SIG_IGN);
        }
    }   
}
