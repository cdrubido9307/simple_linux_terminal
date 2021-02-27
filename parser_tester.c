/* COMP 530: Tar Heel SHell
 *
 * This file is a test harness for the lab0
 * parser.  It takes in commands from standard in,
 * passes them to the parser, and outputs the parsed
 * version in a standardized format for unit testing.
 *
 * Do not change this file.
 */
#include "thsh.h"

int main(int argc, char **argv, char **envp) {
  // flag that the program should end
  bool finished = 0;
  // buffer to hold current command
  int ret = 0;

  do {
    int length;
    char cmd[MAX_INPUT];
    // Get a pointer to cmd that type-checks with char *
    char *buf = &cmd[0];
    char *parsed_commands[MAX_PIPELINE][MAX_ARGS];
    char *infile = NULL;
    char *outfile = NULL;

    // Reset memory from the last iteration
    for(int i = 0; i < MAX_PIPELINE; i++) {
      for(int j = 0; j < MAX_ARGS; j++) {
	parsed_commands[i][j] = NULL;
      }
    }

    // Read a line of input
    length = read_one_line(0, buf, MAX_INPUT);
    if (length <= 0) {
      ret = length;
      break;
    }

    // Pass it to the parser
    ret = parse_line(buf, length, parsed_commands, &infile, &outfile);

    if (ret == -ENOSYS) {
      printf("parse_line (probably) not implemented.  Giving up.\n");
      break;
    } else if (ret < 0) {
      printf("parse_line failed (%d), exiting\n", ret);
      break;
    }

    // Pretty print everything
    for (int i = 0; parsed_commands[i][0]; i++) {
      printf("Pipeline Stage %d: ", i);
      for (int j = 0; parsed_commands[i][j]; j++) {
	printf("[%s] ", parsed_commands[i][j]);
      }
      printf("\n");
    }
    if (infile) {
      printf("Input redirection to file [%s]\n", infile);
    }
    if (outfile) {
      printf("Output redirection to file [%s]\n", outfile);
    }

    // If any commands are built-in commands, execute them.
    // Otherwise, we will handle this in lab 1
    for (int i = 0; parsed_commands[i][0]; i++) {
      int rv;
      if (handle_builtin(parsed_commands[i], 0, 1, &rv)) {
	printf("Command [%s] is a built-in, returned %d.\n", parsed_commands[i][0], rv);
      } else {
	printf("Command [%s] is not a built-in.\n", parsed_commands[i][0]);
      }
    }

  } while (!finished);

  return ret;
}
