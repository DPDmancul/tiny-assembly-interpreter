/**
 * @file instruction.h
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Enums and structures for machine language instructions.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#ifndef _INSTRUCTION
#define _INSTRUCTION

/// Byte
typedef char  B_t;
/// Half word
typedef short H_t;
/// Word
typedef int   W_t;
/// Long word
typedef long  L_t;

/// @brief Binary values of opcodes.
typedef enum opcdodes{
  GET   = 0b0000, ///< Reads an integer from keyboard and stores it in memory.
  PUT   = 0b0001, ///< Prints an integer from operand.

  LOAD  = 0b0010, ///< Loads the operand in the accumulator.
  STORE = 0b0011, ///< Stores accumulator in memory.

  ADD   = 0b0100, ///< Adds the operand to accumulator.
  SUB   = 0b0101, ///< Subtracts the operand from the accumulator.
  MUL   = 0b0110, ///< Multiplies the accumulator by the operand.
  DIV   = 0b0111, ///< Divides the accumulator by the operand.

  JMP   = 0b1000, ///< Jumps to operand.
  JNE   = 0b1001, ///< Jumps to operand if accumulator is negative.
  JZE   = 0b1010, ///< Jumps to operand if accumulator is zero.
  JPO   = 0b1011, ///< Jumps to operand if accumulator is positive.

  ALT   = 0b1100, ///< Stops the execution.

  GETC  = 0b1101, ///< Reads a char from keyboard and store it in memory.
  PUTC  = 0b1110, ///< Prints a char from operand.
  PUTS  = 0b1111  ///< Prints a string from memory.
} opcode_t;

/// @brief Binary values of sizes.
typedef enum sizes{
  /// Byte
  B = 0b00,
  /// Half word
  H = 0b01,
  /// Word
  W = 0b10,
  /// Long word
  L = 0b11
} tas_size_t;

typedef enum{
  /// Pointer
  PTR = 0b0,
  /// Literal
  LIT = 0b1
} type_t;

/// @brief The type of the instruction operand
typedef union{
  /// If the operand is a pointer it contains an address
  size_t ptr;
  /// If the operand is a literal it contains a long word
  W_t lit;
} operand_t;


/// A machine language instruction.
typedef struct{
  /// Binary value of the instruction opcode.
  opcode_t opcode :4;
  /// Binary value of the size of the instruction transaction.
  tas_size_t size :2;
  /// The type of the operand.
  type_t type :1;
  unsigned :0;
  /// Operand of the instruction.
  operand_t operand;
} instruction_t;

#endif
