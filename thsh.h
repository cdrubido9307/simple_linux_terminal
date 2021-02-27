#ifndef THSH_H
#define THSH_H

/* Do not change this file */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>

// Assume no input line will be longer than 1024 bytes
#define MAX_INPUT    1024

// Assume a pipeline will never be longer than 32 stages
#define MAX_PIPELINE   32

// Assume any individual command will not have more than 16 arguments
#define MAX_ARGS       16

// Helper functions

// In parse.c:
int read_one_line(int input_fd, char * buf, size_t size);
int parse_line (char *inbuf, size_t length, char *commands [MAX_PIPELINE][MAX_ARGS],
		char **infile, char **outfile);

// In builtin.c:
int init_cwd(void);
int handle_builtin(char *args[MAX_ARGS], int stdin, int stdout, int *retval);
int print_prompt(void);

// In jobs.c:
int init_path(void);
void print_path_table(void);
int run_command(char *args[MAX_ARGS], int stdin, int stdout, bool wait);

#endif // THSH_H
