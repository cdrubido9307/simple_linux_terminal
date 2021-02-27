# Simple Linux Shell: Tar Heel SHell (THSH)

## Finding Programs Binary

Provides a simple command line tool that supports automatic search for program binaries in your system. For instance, if the command `ls` is typed by the user, the shell will search throught the enviorment **PATH** until it finds the location of the `ls` binary. In this case the program `ls` will be located in  **/bin/ls**. Recall that in Linux systems the path to automatically search the program binaries is stored in the enviroment variable **PATH**.

## How to run THSH
- Clone the github repo
- In Linux, open the terminal shell prompt and go to the folder where you copied the repo
- run: make
- run: ./thsh

** Your prompt should end in **"thsh>"**. Now, you will be able to test our shell.

## Project Structure

| File | Description |
| ---- | ----------- |
| parce.c | Handles the command parsing. The function parse_line populates a two-dimensional array of commands and tokens. The array itself should be pre-allocated by the caller. The first level of the array is each stage in a pipeline, at most MAX_PIPELINE long. The second level of the array is each an argument to a given command, at most MAX_ARGS entries. In each command buffer, the entry after the last valid entry should be NULL. In each command buffer, the entry after the last valid entry should be NULL. For instacne, a simple command like "cd" should parse as: -> commands[0] = ["cd", '\0'], commands[1] = ['\0']. |
| builtin.c | Within this file is the implementation fo the builtin commands of the shell. The function handle_builtin checks if the command (args[0]) is a builtin. If so, call the appropriate handler, and return 1. If not, return 0. stdin and stdout are the file handles for standard in and standard out, respectively. These may or may not be used by individual builtin commands. Places the return value of the command in *retval. stdin and stdout should not be closed by this command. In the case of "exit", this function will not return. The print_prompt function prints the current working directory to the prompt, for example if the current directory is /home/foo then the prompt will look like: [/home/foo] thsh>. The handle_cd function will handle the change directory program. This will support all the flavors of the `cd` builtin command, such as `cd ..`, `cd -`, etc. The handle_exit function does not return, but instead calls exit(0) and terminates the shell program. The handle_goheels function prints to console a Tar Heel token designed inside goheels.txt.|
| jobs.c | The init_path function initializes the table of PATH prefixes by splitting the result on the parenteses and removing any trailing '/' characters. The last entry should be a NULL character. The function run_command tries to execute the given command listed in args . If the first argument starts with a '.' or a '/', it is an absolute or a relative path and then the command is executed as-is. Otherwise, the function searches each prefix in the path_table in order to find the path to the binary. |
| thsh.c | This file is where everything is brought together for this shell implementation (e.g., debugging mode, non-interactive script support, current directory initialization). The path table is initialized with the enviorment **PATH**. The input lines are read and passed to the parcer, which then checks if the command is valid or not. Furthermore, builtin simple commands are passed here to its respective handlers. File redirection, as well as simple and complex pipelines, can be handled by this shell implementation. |

## Builtin Commands

| Command | Description |
| ------- | ----------- |
| cd | Change directory command |
| exit | Terminates the shell program |
| goheels | Displays to console a Tar Heel token |

### Flavors of `cd`
- `cd -` switch to the last directory.
- `cd .` switch to the current directory.
- `cd ..` go up one directory.

## Redirection Support
File redirection support is also supported by this shell implementation. For instance, if the command `ls -l >newfile` is executed, the shell will redirect the output of `ls -l` to **newfile**. This is known as output file redirection. This shell also supports input file redirection. That is to say, commands like `cat < newfile` will send everything inside **newfile** to the `cat` command to be executed.

## Scripting Support
In addition to running commands interactively, this shell also supports non-interactive mode. Commands can be run from inside a file, meaning you can place the commands inside a file to create a program of shell commands, and then can execute them by running: `./thsh scriptName`.

## Simple and Complex Pipeline Support
The implementation also supports pipes. For example, the command `ls | grep .txt | wc -l` takes the output of the `ls` command and sends it to the `grep` command, which then will send its output to `wc -l `. The commands are executed in the order specified by the pipeline (from left to right). In addition, complex pipelines are supported, meaning that we can include file redirection into the pipeline, and the shell will know how to handle this as well. There is no limit to the number of pipes you can do.

## Debugging support
 If you start thsh with -d, it displays debugging info on stderr:

 Ex: ./thsh -d

- Every command executed says "RUNNING: [cmd]", where cmd is the command. For instance, if you run ls -l, thsh should print "RUNNING: [ls]"
- When the command ends it says "ENDED: [cmd] (ret=0)" and shows the return value from run_command

**Note:** Debugging support is also implemented when running a script in non-interactive mode
EX: ./thsh script -d
