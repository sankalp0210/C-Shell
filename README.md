## RUNNING

- run "make"

- execute by using "./myShell"

- type "exit" to exit the shell

## FEATURES

#### ls command
- ls takes arguments as flags (in the form -(flagname)) and directories (in the form (directory name)) in any order.
- It lists the files of all the directories mentioned, in the form of option selected by the flags.
- If there is no directory mentioned, it lists the files of current directory

* "ls" -> lists in alphabetical order
* "ls -a" -> display hidden files
* "ls -l" -> long list
* "ls -al"/"ls -la"/"ls -l -a"/"ls -a -l" -> long list including hidden files

#### cd command
* "cd (absolute path)" - goes to absolute path
* "cd" - goes to ~/
* "cd ~" - goes to ~/
* "cd .." - goes to previous directory
* "cd ." - goes to same directory

#### echo command
* "echo" - prints no line
* "echo text" - prints text
* "echo 'text' " - prints 'text'

#### pwd command
* "pwd" - prints absolute path of present working directory

#### pinfo command
* "pinfo" : prints the process related info of the shell program 
* "pinfo <pid>" : prints the process info about given pid
- pid -- 
- Process status -- {R/S/S+/Z}
- Virtual Memory
- Executable path -- (Absolute path - includes ~/ if executable is present inside the shell directory)

#### remindme command
* "remindme <time> <msg>" : after the specified <time> interval it displays the <msg> on the terminal

#### clock command
* "clock -t <time interval> -n <time duration>" : it runs for the <time duration> and keeps on displaying date and time after the given <time duration>
