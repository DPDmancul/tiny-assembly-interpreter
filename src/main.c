/**
 * @file main.c
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Starts the Tiny Asembler Interpreter, reading input from file or stdin.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 *
 * Reads instructions from file, if passed as argument, or from stdin otherwise.
 * Then starts the interpreter.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "asm_int.h"

#ifndef __TAS_VERSION__
#define __TAS_VERSION__ ""
#endif

int main(int argc, char* argv[]) {

  if(argc > 2 || argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h'){
    // Prints help

    // Takes the executable name from path
    char *exe_name = strrchr(argv[0], '/');
    if (exe_name)
      // +1 because the first character is the slash
      ++exe_name;
    else
      // if no slash was found argv[0] isn't the full path
      exe_name = argv[0];

    printf(
      "Tiny Assembly Interpreter v%s\n"
      "By Davide Peressoni\n\n"
      "usage: %s <file>.tas\n"
      "If no file is passed it will read from stdin.\n",
      __TAS_VERSION__, exe_name
    );
  }else if(argc == 2 && argv[1][0] != '\0'){
    // Read from file
    FILE *in = fopen(argv[1], "r");
    execute_asm_from(in);
    fclose(in);
  }else
    // Read from stdin
    execute_asm_from(stdin);

  return EXIT_SUCCESS;
}
