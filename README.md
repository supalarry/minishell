# minishell
minishell is a very basic shell. shell is a program making sense of what is the meaning of user input in the terminal.

## Getting Started
Run **make** in root folder. Then, execute **minishell** binary to launch minishell.
```
./minishell
```

## Functionality
![alt text](https://i.imgur.com/c2JiXol.png)

minishell is able to run binaries, like ls, by using fork and execve system calls.

![alt text](https://i.imgur.com/68JtxhI.png)

Furthermore, environment metadata is managed via **setenv VAR VALUE** and environment variables can be removed via **unsetenv VAR**. To view environment write **env**. Environment variables store additional data about the minishell and are inherited from parent process, which is the shell you will use to run minishell.

![alt text](https://i.imgur.com/zpFfrzI.png)

This minishell also includes in-builts, like **cd**, **exit**, **echo**. If child process is ran, it can be killed by sending SIGNIT signal by pressing ctrl+c. It also includes **~** and **$** expansions. By writing **cd**, minishell changes directory to home directory and **cd -** changes present directory to previous present directory. **exit** quits minishell and **echo** outputs text. **~** expansion expands to home directory, which is the same as **$HOME** expansion. **$** is used to grab environment variables. More examples can be seen in the following example.

![alt text](https://i.imgur.com/NFcUtNm.png)
