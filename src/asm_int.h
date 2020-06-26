/**
 * @file asm_int.h
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Starts the Tiny Assembly Interpreter, reading from specified file.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#ifndef __ASM_INT
#define __ASM_INT

#include<stdio.h>

/**
 * @brief Starts the Tiny Assembly Interpreter, reading from specified file.
 *
 * @param file input file stream
 */
void execute_asm_from(FILE *file);

#endif