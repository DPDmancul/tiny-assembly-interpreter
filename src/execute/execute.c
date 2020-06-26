/**
 * @file execute.c
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Functions to execute instructions.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#include<stdio.h>
#include<stdlib.h>

#include "execute.h"

/**
 * @brief Switch the opcode and execute for size S.
 *
 * @param S Size.
 * @param I Instruction.
 * @param D Pointer to data.
 * @param R Pointer to CPU registers.
 */
#define EXECUTE_FOR_SIZE(S, I, D, R){\
  switch((I).opcode){\
    case GET:{\
      long t;\
      scanf("%li", &t);\
      *VECTOR_T_AT(D, S##_t, (I).operand.ptr) = (const S##_t)t;\
      break;\
    }\
    case PUT:\
      printf("%ld", (long)*VECTOR_T_AT(D, const S##_t, (I).operand.ptr));\
      break;\
    case LOAD:\
      (R)->accumulator = *VECTOR_T_AT(D, const S##_t, (I).operand.ptr);\
      break;\
    case STORE:\
      *VECTOR_T_AT(D, S##_t, (I).operand.ptr) = (const S##_t)(R)->accumulator;\
      break;\
    case ADD:\
      (R)->accumulator += *VECTOR_T_AT(D, const S##_t, (I).operand.ptr);\
      break;\
    case SUB:\
      (R)->accumulator -= *VECTOR_T_AT(D, const S##_t, (I).operand.ptr);\
      break;\
    case MUL:\
      (R)->accumulator *= *VECTOR_T_AT(D, const S##_t, (I).operand.ptr);\
      break;\
    case DIV:\
      (R)->accumulator /= *VECTOR_T_AT(D, const S##_t, (I).operand.ptr);\
      break;\
  }\
}

void execute(instruction_t i, vector_t *data, cpu_t *registers){
  ++registers->pc;
  switch(i.opcode){
    case JMP:
      registers->pc = i.operand.ptr;
      break;
    case JNE:
      if(registers->accumulator < 0)
        registers->pc = i.operand.ptr;
      break;
    case JZE:
      if(!registers->accumulator)
        registers->pc = i.operand.ptr;
      break;
    case JPO:
      if(registers->accumulator > 0)
        registers->pc = i.operand.ptr;
      break;
    case ALT:
      registers->pc = -1;
      break;
    case GETC:
      *VECTOR_T_AT(data, char, i.operand.ptr) = getchar();
      break;
    case PUTC:
      putchar(i.type == LIT ? i.operand.lit : *VECTOR_T_AT(data, const char, i.operand.ptr));
      break;
    case PUTS:
      printf("%s", (const char*)vector_at(data,i.operand.ptr));
      break;
    default:
      if(i.type == LIT)
        switch(i.opcode){
          case PUT:
            printf("%ld", (long)i.operand.lit);
            break;
          case LOAD:
            registers->accumulator = i.operand.lit;
            break;
          case ADD:
            registers->accumulator += i.operand.lit;
            break;
          case SUB:
            registers->accumulator -= i.operand.lit;
            break;
          case MUL:
            registers->accumulator *= i.operand.lit;
            break;
          case DIV:
            registers->accumulator /= i.operand.lit;
            break;
          default:
            fprintf(stderr, "Unexpected literal: this instruction requires a label.\n");
            exit(EXIT_FAILURE);
        }
      else // The operand is a PTR
        switch(i.size){
          case B:
            EXECUTE_FOR_SIZE(B, i, data, registers);
            break;
          case H:
            EXECUTE_FOR_SIZE(H, i, data, registers);
            break;
          case W:
            EXECUTE_FOR_SIZE(W, i, data, registers);
            break;
          case L:
            EXECUTE_FOR_SIZE(L, i, data, registers);
            break;
        }
  }
}