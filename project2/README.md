# COMP7500 Advanced Operating Systems 
## Project 2 Notes



### What is difference fprintf() printf()
printf() is used to print a formatted string to a stand ouput. fprintf() is used to print a formatted string to a specific file.

### What is file descriptor
A file descriptor is an unsigned interger used by a process to identify an open file.
stdin 0, stdout 1, stderr 2.
We can use <unistd.h>, it defined STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO.
/proc/PID/fd is stdin.

### What is difference between stdout stderr
stdout: Stands for standard output.
stderr: Stands for staandard error.
The text output of a command is stored in the "stdout" stream, while the error message from "stderr" is stored in the screnn. Which means it will directly print at the screen wiout buffer.