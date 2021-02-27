/* COMP 530: Tar Heel SHell
 *
 * This file implements functions related to launching
 * jobs and job control.
 */

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "thsh.h"

//Static variables
static char **path_table;

//Helper functions
char *replace_pattern(char *path_prefixes);

/* Initialize the table of PATH prefixes.
 *
 * Split the result on the parenteses, and
 * remove any trailing '/' characters.
 * The last entry should be a NULL character.
 *
 * For instance, if one's PATH environment variable is:
 *  /bin:/sbin///
 *
 * Then path_table should be:
 *  path_table[0] = "/bin"
 *  path_table[1] = "/sbin"
 *  path_table[2] = '\0'
 *
 * Hint: take a look at getenv().  If you use getenv, do NOT
 *       modify the resulting string directly, but use
 *       malloc() or another function to allocate space and copy.
 *
 * Returns 0 on success, -errno on failure.
 */

int init_path(void)
{
  //Gets the environment path
  char *path = getenv("PATH");

  //Ignore empty paths
  if ((path == NULL) || (strlen(path) == 0))
  {
    path_table = malloc(sizeof(char *));
    path_table[0] = NULL;
    return 0;
  }

  char *env_var_copy = strdup(path);
  char *path_prefixes;
  int index = 0;

  path_table = malloc(strlen(env_var_copy) * sizeof(char *));

  //Ignores trailing spaces
  path_prefixes = strtok(env_var_copy, " \t");

  //Searches for pattern "::" to replace with "./"
  path_prefixes = replace_pattern(path_prefixes);

  //Ignores trailing slashes '/'
  for (int i = strlen(path_prefixes) - 1; i >= 0; i--)
  {
    if (path_prefixes[i] != '/')
    {
      break;
    }
    else if (path_prefixes[i] == '/')
    {
      path_prefixes[i] = '\0';
    }
  }
  path_prefixes = strdup(path_prefixes);

  // Searches for the first ':' character and finds the first path prefix
  path_prefixes = strtok(path_prefixes, ":");

  // Find all the ':' characters and get all the path prefixes
  while (path_prefixes != NULL)
  {
    path_table[index] = strdup(path_prefixes);
    path_prefixes = strtok(NULL, ":");
    index++;
  }
  //Adds null to the last entry of the table
  path_table[index] = NULL;

  //Free space in memory
  free(env_var_copy);
  free(path_prefixes);

  return 0;
}

/* Debug helper function that just prints
 * the path table out.
 */
void print_path_table()
{
  if (path_table == NULL)
  {
    printf("XXXXXXX Path Table Not Initialized XXXXX\n");
    return;
  }

  printf("===== Begin Path Table =====\n");
  for (int i = 0; path_table[i]; i++)
  {
    printf("Prefix %2d: [%s]\n", i, path_table[i]);
  }
  printf("===== End Path Table =====\n");
}

//Helper function that replaces the pattern "::" with './'
char *replace_pattern(char *path_prefixes)
{
  for (int i = 0; i < (strlen(path_prefixes) - 1); i++)
  {
    if ((path_prefixes[i] == ':') && (path_prefixes[i + 1] == ':'))
    {
      char *new_path = strdup(path_prefixes);
      new_path = realloc(new_path, (strlen(new_path) + 1) * sizeof(char *));
      new_path[i + 1] = '.';

      for (int k = i + 1; k < strlen(path_prefixes); k++)
      {
        new_path[k + 1] = path_prefixes[k];
      }

      i = i + 2; //To keep checking the path after replacing the characters "::"
      free(path_prefixes);
      path_prefixes = new_path;
    }
  }
  return path_prefixes;
}
