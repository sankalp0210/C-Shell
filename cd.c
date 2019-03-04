#include<stdio.h>
#include<unistd.h>
void cd(char **s, char* home)
{
	if(s[2]!=NULL)
	{
		perror("Too many arguments to cd.\n");
		return;
	}
	if(s[1] == NULL || (s[1] != NULL && s[1][0] == '~'))
	{
		chdir(home);
		return;
	}
	int x = chdir(s[1]);
	if(x == -1)
		perror("No such file or directory.\n");
}