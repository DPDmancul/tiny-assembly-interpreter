/**
 * @file test_main.c
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Starts the Tiny Asembler Interpreter, reading input from file and stdin from arguments.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../src/asm_int.h"

int main(int argc, char* argv[]) {

  // New temp file
  char input_path[L_tmpnam];
  tmpnam(input_path);

  FILE *input = fopen(input_path,"w");

  // Put arguments in input
  for(size_t i = 2; i < argc; ++i)
    fprintf(input, " %s\n", argv[i]);

  // Use input instead of stdin
  fclose(input);
  (void) freopen(input_path, "r", stdin);

  // The real program
  FILE *in = fopen(argv[1], "r");
  execute_asm_from(in);
  fclose(in);

  // Delete temp file
  fclose(stdin);
  remove(input_path);

  return EXIT_SUCCESS;
}
