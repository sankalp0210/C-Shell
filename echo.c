#include <stdio.h>
void echo(char** s)
{
	int i = 1;
	while(s[i]!=NULL)
		printf("%s ", s[i++]);
	printf("\n");
}