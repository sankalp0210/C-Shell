#include<stdio.h>
#include<string.h> 
extern int bgcount;
extern char bgProcess[400005][256];

void jobs()
{
    int i = 0;
    int j = 0;
    for(i=0;i<4e5;i++)
    {
        if(bgProcess[i][0]!='\0')
        {
            j++;
            printf("[%d] ",j);

        	char a[1024];
        	char b[1024];
        	char c[1024];
            char name[1024];
            sprintf(name, "/proc/%d/stat", i);
            FILE* f = fopen(name, "r");
            if(f)
            {
                int i = 0;
                fscanf(f, "%s %s %s",a,b,c);
                fclose(f);
            }
            if(!strcmp(c,"T"))
                printf("Stopped ");
            else
                printf("Running ");
            for(int k = 0;k<100;k++)
            {
                if(bgProcess[i][k] == ' ')
                    break;
                printf("%c",bgProcess[i][k]);
            }
            printf("[%d]\n",i);
        }
    }
}
