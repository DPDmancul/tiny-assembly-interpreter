/**
 * @file registers.h
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Utilities for representing CPU registers.
 * @version 1.0.0
 * @date 2020-05-11
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#ifndef _REGISTERS
#define _REGISTERS

#include "instruction.h"

/// Contains CPU registers.
typedef struct{
  /// Accumulator register
  L_t accumulator;
  /// Program counter
  size_t pc;
} cpu_t;

#endif