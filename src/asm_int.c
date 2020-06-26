/**
 * @file asm_int.c
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Starts the Tiny Assembly Interpreter, reading from specified file.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#include<stdlib.h>

#include "asm_int.h"
#include "vector/vector.h"
#include "parser/parser.h"
#include "execute/execute.h"
#include "types/registers.h"


void execute_asm_from(FILE *file){

  if(!file){
    fprintf(stderr, "Cannot open file in %s.\n", __FILE__);
    exit(EXIT_FAILURE);
  }

  // Vector for storing data section
  vector_t data = {.element_size = 1};

  // Vector for storing text section
  vector_t text = {.element_size = sizeof(instruction_t)};

  // Parse the file
  read_asm_file(file, &data, &text);

  if(!text.p){
    fprintf(stderr, "Allocation error in %s.\n", __FILE__);
    exit(EXIT_FAILURE);
  }

  cpu_t reg;

  for(reg.pc = 0; reg.pc < text.size && reg.pc != -1;)
    // Execute the next instruction
    execute(*(instruction_t*)vector_at(&text,reg.pc), &data, &reg);

  vector_deallocate(&data);
  vector_deallocate(&text);
}