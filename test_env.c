/* COMP 530: Tar Heel SHell
 *
 * This file is a test harness for the
 * PATH table.  It just parses the PATH environment
 * variable and pretty-prints the table contents.
 * 
 * Do not change this file.
 */

#include "thsh.h"

int main() {
  int rv = init_path();

  if (rv) {
    printf("Problem setting up the path table - %d.\n", rv);
    return rv;
  }

  print_path_table();

  return rv;
}
