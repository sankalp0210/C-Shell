#include <stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
extern int bgcount;
extern char bgProcess[400005][256];

void kjob(char **s)
{
    if((s[1] == NULL || s[2] == NULL) && s[3] != NULL){
        perror("Invalid No. of arguments.\n");
        return;
    }
    int j = 0;
    if(atoi(s[1]) > bgcount)
    {
        perror("INVALID JOB ID\n");
        return;
    }
    for(int i= 0;i<4e5;i++)
    {
        if(bgProcess[i][0] != '\0')
        {
            j++;
            if(j == atoi(s[1]))
                kill(i, atoi(s[2]));
        }
    }
}