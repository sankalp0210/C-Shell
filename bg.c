#include <stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
extern int bgcount;
extern char bgProcess[400005][256];

void bg(char *s)
{
    if(s == NULL){
        perror("Invalid No. of arguments.\n");
        return;
    }
    if(atoi(s) > bgcount)
    {
        perror("INVALID JOB ID\n");
        return;
    }
    int j = 0;
    for(int i= 0;i<4e5;i++)
    {
        if(bgProcess[i][0] != '\0')
        {
            j++;
            if(j == atoi(s)){
                bgProcess[i][0] = '\0';
                bgcount++;
                kill(i, SIGCONT);

                return;
            }
        }
    }
}
