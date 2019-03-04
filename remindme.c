#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
extern int bgcount;
extern char bgProcess[400005][256];

void remindme(char** s)
{
	pid_t pid;
    if(s[1] == NULL || s[2] == NULL)
    {
    	perror("ERROR:exec failed\n");
    	return;
    }
    char msg[256];
    memset(msg, '\0', sizeof(msg));
    int i = 2;
    while(s[i]!=NULL) strcat(msg,s[i]), strcat(msg," "), s[i++] = NULL;
    s[0] = "sleep";
    if ((pid = fork()) < 0)
    {     
        perror("ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
    	if (execvp(s[0], s) < 0)
            perror("ERROR: exec failed\n");
    }
    else
    {
		signal(SIGCHLD,SIG_IGN);
		sprintf(bgProcess[pid],"%s", msg);
		bgcount++;
    }
}