#include<stdio.h>
#include<signal.h>
#include <sys/types.h>
#include <unistd.h>
extern int mainPID;
extern int childPID;
extern int bgcount;
extern int flagc;
extern char bgProcess[400005][256];
void execCTRL_C(int sig)
{
	flagc = 1;
	// printf("\n");
    // pid_t pid = getpid();
	// if(pid != mainPID)
	// 	return;

	// if(childPID != -1)
	// {
    //     if(bgProcess[childPID][0] != '\0')
	// 	    kill(childPID, SIGINT);
	// }
	// signal(SIGINT, execCTRL_C);	
}
