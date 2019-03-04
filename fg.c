#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
extern int bgcount;
extern int flagc;
extern int flagz;
extern int curProcName[100];
extern char bgProcess[400005][256];
extern void execCTRL_C(int sig);
extern void execCTRL_Z(int sig);
void fg(char *s)
{
    int status;
    if(s == NULL)
    {
        perror("Invalid No. of Arguments.\n");
        return;
    }
    if(atoi(s) > bgcount)
    {
        perror("INVALID JOB ID\n");
        return;
    }
    int j = 0;
    int x = atoi(s);
    for(int i= 0;i<4e5;i++)
    {
        if(bgProcess[i][0] != '\0')
        {
            j++;
            if(j == x)
            {
                kill(i, SIGCONT);
                flagc = 0;
                flagz = 0;
                signal(SIGTSTP, execCTRL_Z);
                signal(SIGINT, execCTRL_C);
                while (flagz == 0 && flagc==0 && waitpid(i,&status,WNOHANG) != i);
                if(flagc){
                    kill(i,9);
                    wait(NULL);
                }
                if(flagz)
                {
                    setpgid(i,i);
                    kill(i,SIGSTOP);
                    signal(SIGCHLD, SIG_IGN);
                }
                flagc = 0;
                flagz = 0;
                return;
            }
        }
    }
}