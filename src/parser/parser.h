/**
 * @file parser.h
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Decodes Tiny Assembly instructions from file.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#ifndef _PARSER
#define _PARSER

#include<stdio.h>

#include "../vector/vector.h"

/// The maximum length of a token.
#ifndef MAX_TOKEN_LEN
#define MAX_TOKEN_LEN 50
#endif
/// The maximum length of a literal string.
#ifndef MAX_STR_LEN
#define MAX_STR_LEN 200
#endif

/**
 * @brief Reads tas assembly file and populates the memory.
 *
 * @param file The tas file.
 * @param data The data segment to be populated.
 * @param text The text segment to be populated.
 */
void read_asm_file(FILE *file, vector_t *data, vector_t *text);

#endif
