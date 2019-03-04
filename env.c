#include<stdio.h>
#include<stdlib.h>

void envunset(char** s)
{
    if(s[1] == NULL || s[2] != NULL)
    {
        perror("Invalid no. of arguments\nSyntax : unsetenv var");
        return;
    }
    int x = unsetenv(s[1]);
    if(x != 0)
        perror("Could not remove environment variable.");
}
void envset(char** s)
{
    if(s[2] == NULL || s[3] != NULL)
    {
        perror("Invalid no. of arguments\nSyntax : setenv var value");
        return;
    }
    int x = setenv(s[1], s[2], 2);
    if(x != 0)
        perror("Could not create or modify environment variable.");

}