#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void clck(char** s)
{
	if(s[1] == NULL || s[2] == NULL || strcmp(s[1], "-t")!=0 || s[3] == NULL || s[4] == NULL || strcmp(s[3],"-n") != 0)
	{
		perror("ERROR: INVALID SYNTAX\n");
		return;
	}
	char fname[1024];
	int tm = atoi(s[2]);
	strcpy(fname, "/proc/driver/rtc");
	int n = atoi(s[4])/tm;
	do
	{
		n--;
		FILE* f = fopen(fname, "r");
		if(!f)
		{
			perror("ERROR\n");
			return;
		}
		char *buf = NULL;
		char *buf2 = NULL;
		size_t bt =0;
		char *ch;
		char pa[1024],qa[1024];
		getline(&buf,&bt,f);
		getline(&buf2,&bt,f);
		char* p = strtok(buf," ");
		while(p!=NULL) strcpy(pa,p), p = strtok(NULL," ");
		char* q = strtok(buf2," \t\r\a");
		while(q!=NULL) strcpy(qa,q), q = strtok(NULL," \t\r\a");
		int l = 0;
		for(l=0;qa[l]!='\0';l++);
		qa[l-1] = '\0';
		printf("%s, %s", qa, pa);
		if(n<0)
			sleep(atoi(s[4])%tm);
		else
			sleep(tm);
		fclose(f);
	}
	while(n>=0);
}