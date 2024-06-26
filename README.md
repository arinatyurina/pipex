# Pipex Project

## Introduction

The pipex project is part of the 42 School curriculum. It focuses on understanding and implementing Unix-like pipe and redirection functionalities in C. The goal of this project is to execute two commands in sequence, where the output of the first command is used as the input for the second command, similar to the behavior of the shell pipeline (|) and redirection operators (<, >).

## Setup

1. Clone the repository:

    ```sh
    git clone https://github.com/arinatyurina/pipex.git
    ```

2. Compile the program:

    ```sh
    make
    ```

## Usage

To run the pipex program, use the following command:
```sh
./pipex file1 cmd1 cmd2 file2
```
+ **file1**: The input file.
+ **cmd1**: The first command to execute.
+ **cmd2**: The second command to execute.
+ **file2**: The output file.

### Example
```sh
./pipex infile "ls -l" "grep hello" outfile
```
This command will execute ls -l on infile, pipe its output to grep hello, and write the result to outfile.

## Terminology
### Pipe
**Definition**: A pipe is a method of inter-process communication that directs the output of one process to the input of another.

**Usage in pipex**: In pipex, a pipe is used to link the output of cmd1 to the input of cmd2.

### Redirection
**Definition**: Redirection is the process of directing data to or from a different location, typically files or devices.

**Operators**:

<: Input redirection. Reads input from a file.
>: Output redirection. Writes output to a file.

## System Calls
**pipe**
```sh
int pipe(int pipefd[2]);
```
Creates a pipe and places two file descriptors in pipefd. pipefd[0] is for reading and pipefd[1] is for writing.

**fork**
```sh
pid_t fork(void);
```
Creates a new process by duplicating the calling process. The new process is referred to as the child process.

**dup2**
```sh
int dup2(int oldfd, int newfd);
```
Duplicates oldfd to newfd. Useful for redirecting input/output.

**execve**
```sh
int execve(const char *pathname, char *const argv[], char *const envp[]);
```
Replaces the current process image with a new process image specified by pathname.

### Example Workflow
**Create Pipe**: Use pipe to create a pipe.  
**Fork Process**: Use fork to create a child process.  
**Redirect Input/Output**: Use dup2 to redirect input/output as needed.  
**Execute Commands**: Use execve to execute commands in child processes.
