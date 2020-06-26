/**
 * @file instructions.h
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Functions to execute instructions.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#ifndef _EXECUTE
#define _EXECUTE

#include "../types/instruction.h"
#include "../vector/vector.h"
#include "../types/registers.h"

/**
 * @brief Executes an instruction.
 *
 * @param i Instruction to be executed.
 * @param data Pointer to data segment.
 * @param registers Pointer to CPU registers.
 */
void execute(instruction_t i, vector_t *data, cpu_t *registers);

#endif