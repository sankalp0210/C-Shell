#include <sys/wait.h>
#include <stdio.h>
#include<signal.h>
extern int bgcount;
extern char bgProcess[400005][256];
void childSignalHandler(int sign)
{
	int status;
	int i = 0;
	for(i=0;i<4e5;i++)
	{
		if(waitpid(i,&status,WNOHANG) && bgProcess[i][0]!='\0')
		{
			printf("\n%s\n", bgProcess[i]);
			bgProcess[i][0] = '\0';
			bgcount--;
		}
	}
	return;
}