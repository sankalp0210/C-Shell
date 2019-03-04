#include<stdio.h>
#include<signal.h>
#include <sys/wait.h>
#include<sys/types.h>
extern int bgcount;
extern char bgProcess[400005][256];

void overkill()
{
    int i=0;
    for(i=0;i<4e5;i++)
    {
        if(bgProcess[i][0]!='\0')
        {
            kill(i,SIGKILL);
            wait(NULL);
            bgProcess[i][0] = '\0';
			bgcount--;
        }
    }
}