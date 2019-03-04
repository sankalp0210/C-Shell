int bgcount;
char bgProcess[400005][256];
char userName[51], currDir[1024], homeDir[1024], hostname[1024];
int homeDirSize;
int mainPID;
int childPID;
int flagz =0;
int flagc =0;
char curProcName[100];
// Function declarations.
void break_commands();
void printDir();
void command(char* s);
void cd(char **s, char* home);
void pwd(char* currDir);
void echo(char** s);
void ls(char** s);
void pinfo(char** s);
void remindme(char** s);
void otherCommands(char** s);
void childSignalHandler(int sign);
void clck(char** s);
void envset(char** s);
void overkill();
void envunset(char** s);
void kjob(char** s);
void jobs();
void fg(char* s);
void bg(char* s);
void execCTRL_C(int sig);
void execCTRL_Z(int sig);