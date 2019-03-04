#include<stdio.h>
#include<signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
extern int mainPID;
extern int childPID;
extern int bgcount;
extern int flagz;
extern char curProcName[100];
extern char bgProcess[400005][256];

void execCTRL_Z(int sig)
{
	flagz = 1;
}
