# minishell
Implementation of a very basic shell

Run 'make' in root folder. Then, execute 'minishell' binary.
This mini shell is able to run binaries, like ls, via fork and execve. Furthermore, environment metadata is managed via
'setenv VAR VALUE' and environment variables can be removed via 'unsetenv VAR'. To view environment write 'env'.
This minishell also includes in-builts, like 'cd', 'exit', 'echo'. If child process is ran, it can be killed by sending
SIGNIT signal by pressing ctrl+c. It also includes '~' and '$' expansions.

![alt text](https://i.imgur.com/NFcUtNm.png)
