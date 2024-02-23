This project taught me how to reproduce the behavior of pipes in a shell. I learned how to fork child processes and carefully manage file descriptors.

You can run it as follows:
```
./pipex file1 cmd1 cmd2 file2
```
It must take 4 arguments:
* file1 and file2 are file names.
* cmd1 and cmd2 are shell commands with their parameters.
* If cmd parameters are used, you must use "" to keep them with their command.
* It must behave exactly the same as the shell command below:
```
$> < file1 cmd1 | cmd2 > file2
```
Here is an example with arguments:
```
./pipex file "grep main" "cat -e" output
```
This should behave the same as:
```
$> < file grep main | cat -e > output
```
