/**
 * @file parser.c
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Decodes Tiny Assembly instructions from file.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#include<stdlib.h>
#include<string.h>
#include<stdint.h>

#include "parser.h"
#include "../types/instruction.h"
#include "../map/map.h"

/// @brief Casts two chars into an u_int16
#define CHR_TO_UINT16(C1, C2) (((uint16_t)(C1) << 8) + (uint16_t)(C2))

#define STR(M) #M
#define XSTR(M) STR(M)
#define TOKEN_STR "%"XSTR(MAX_TOKEN_LEN)"s"

/// Represents the section type.
typedef enum {DATA, TEXT} section_t;

typedef struct{
  char *string;
  size_t index;
} pair_string_index_t;

/// @brief Given a character e returns '\e'
static char escape_char(char e){
  switch(e){
    case '0':
      return '\0';
    case 'a':
      return '\a';
    case 'b':
      return '\b';
    case 'f':
      return '\f';
    case 'n':
      return '\n';
    case 'r':
      return '\r';
    case 't':
      return '\t';
    case 'v':
      return '\v';
    case '\\':
      return '\\';
    case '\'':
      return '\'';
    case '\"':
      return '\"';
    case '\?':
      return '\?';
    default:
      return e;
  }
}

/// @ brief Reads the section name (after a dot) from file.
static section_t read_section(FILE *file){
  char s[5];
  if(fscanf(file,"%4s",s)){
    if(!strcmp(s,"data"))
      return DATA;
    if(!strcmp(s,"text"))
      return TEXT;
  }
  fprintf(stderr,"Unexpected token .%s.\n",s);
  exit(EXIT_FAILURE);
}

/// Reads the operand for instruction from file,
/// puts them in text and puts potentials required labels in the lookup table.
static void read_operand(const char *instruction, FILE *file, vector_t *text, vector_t *lut){
  if(!strcmp(instruction, "alt")){
    // ALT is the unique instruction without operand
    vector_push(text, &(instruction_t){ALT});
    return;
  }

  // Read operand

  // The first character is reserved for data/text flag
  char operand[MAX_TOKEN_LEN+2];

  if(!fscanf(file, TOKEN_STR, operand+1)){
    fprintf(stderr, "Couldn't read operand.\n");
    exit(EXIT_FAILURE);
  }

  // Decode instruction
  instruction_t inst;
  if(!instruction[0] || !instruction[1] || !instruction[2]){
    //if the mnemonic is shorter than three chars
    fprintf(stderr,"Mnemonic %s too short.\n", instruction);
    exit(EXIT_FAILURE);
  }
  /*
   The switch compares the first two characters (16 bits).
   Since all instructions have at least three characters and the first two are always different
   (except for get and getC, put, putC and putS), it could be done.

   *(uint16_t*)instruction cannot been used instead of CHR_TO_UINT16(instruction[0], instruction[1])
   because the first depend of the architecture endianness.
  */
  switch(CHR_TO_UINT16(instruction[0], instruction[1])){
    case CHR_TO_UINT16('g','e'): // get, getC
      inst.opcode = instruction[3] == 'C' ? GETC
                  :                         GET;
      break;
    case CHR_TO_UINT16('p','u'): // put, putC, putS
      inst.opcode = instruction[3] == 'C' ? PUTC
                  : instruction[3] == 'S' ? PUTS
                  :                         PUT;
      break;
    case CHR_TO_UINT16('l','o'): // load
      inst.opcode = LOAD;
      break;
    case CHR_TO_UINT16('s','t'): // store
      inst.opcode = STORE;
      break;
    case CHR_TO_UINT16('a','d'): // add
      inst.opcode = ADD;
      break;
    case CHR_TO_UINT16('s','u'): // sub
      inst.opcode = SUB;
      break;
    case CHR_TO_UINT16('m','u'): // mul
      inst.opcode = MUL;
      break;
    case CHR_TO_UINT16('d','i'): // div
      inst.opcode = DIV;
      break;
    case CHR_TO_UINT16('j','m'): // jmp
      inst.opcode = JMP;
      break;
    case CHR_TO_UINT16('j','n'): // jne
      inst.opcode = JNE;
      break;
    case CHR_TO_UINT16('j','z'): // jze
      inst.opcode = JZE;
      break;
    case CHR_TO_UINT16('j','p'): // jpo
      inst.opcode = JPO;
      break;
    default:
      fprintf(stderr,"Unknown mnemonic %s.\n", instruction);
      exit(EXIT_FAILURE);
  }

  operand[0] = (inst.opcode & 0b1100) == JMP /*jump*/ ? 't'/*text*/ : 'd'/*data*/;

  inst.type = PTR;
  switch(inst.opcode){
    case PUT:
    case LOAD:
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case PUTC:{
      // Check if the operand is a literal or a label
      long lit;
      if(sscanf(operand+1, "%li", &lit)){
        // Integer literal
        inst.type = LIT;
        inst.operand.lit = (W_t)lit;
      }else if(operand[1] == '\'')
        // Char literal
        switch(operand[2]){
          case '\0':
            // The next character is a space which was ignored by scanf
            operand[3] = fgetc(file);
            if(fgetc(file) != '\''){
              operand[4] ='\0';
              fprintf(stderr, "Missing closing char quote in %s.\n", operand);
              exit(EXIT_FAILURE);
            }
          case '\\':
            operand[2] = escape_char(operand[3]);
          default:
            inst.type = LIT;
            inst.operand.lit = operand[2];
        }
    }
  }

  if(inst.type == PTR && ! (inst.opcode & 0b1000 /* jump */)){
    switch(instruction[strlen(instruction)-1]){
      case 'B':
        inst.size = B;
        break;
      case 'H':
        inst.size = H;
        break;
      case 'W':
        inst.size = W;
        break;
      case 'L':
        inst.size = L;
        break;
      default:
        fprintf(stderr, "Missing size for instruction %s.\n", instruction);
        exit(EXIT_FAILURE);
    }
  }

  if(inst.type == PTR)
    // Put the label of the operand in the lookup table
    vector_push(lut, &(pair_string_index_t){strcln(operand), text->size});

  vector_push(text, &inst);
}

/**
 * @brief Case for switch on operand type
 *
 * @param C Operand type in char.
 * @param T Operand type in enum.
 *
 * If the switch enters in this case, it gets an integer (if exists) from file and puts it in data.
 */
#define READ_DATA_INTEGER(C,T) case C:{\
  long getted;\
  fscanf(file, "%li", &getted);\
  T##_t value = (T##_t)getted;\
  VECTOR_T_PUSH(data, T##_t, &value);\
  break;\
}

/// Reads a potential data initialization from file,
/// puts it in data, after the space allocation.
static void read_data(const char *instruction, FILE *file, vector_t *data){
  // Assert it is a "new" instruction
  if(instruction[0]!='n' || instruction[1]!='e' ||instruction[2]!='w'){
    fprintf(stderr, "Only \"new\" is allowed in data section. %s was found instead.\n", instruction);
    exit(EXIT_FAILURE);
  }
  switch(instruction[3]){
    case 'S':{
      // New string
      if(fgetc(file) != '"'){
        fprintf(stderr, "Missing required string literal for newS.\n");
        exit(EXIT_FAILURE);
      }
      int c;
      // Read string literal
      while(c = fgetc(file), c != '"'){
        if(c == '\n' || c == EOF){
          fprintf(stderr, "Missing string closing quote symbol.\n");
          exit(EXIT_FAILURE);
        }
        if(c == '\\')
          c = escape_char(fgetc(file));
        VECTOR_T_PUSH(data, char, &c);
      }
      c = '\0';
      VECTOR_T_PUSH(data, char, &c);
      break;
    }
    case 'C':{
      // New char
      int c = fgetc(file);
      if(c == '\''){
        // If there is an initial value read it
        c = fgetc(file);
        if(c == '\n' || c == EOF){
          fprintf(stderr, "Missing char literal.\n");
          exit(EXIT_FAILURE);
        }
        if(c == '\\')
          c = escape_char(fgetc(file));
        if(fgetc(file) != '\''){
          fprintf(stderr, "Missing char closing quote symbol.\n");
          exit(EXIT_FAILURE);
        }
      }else
        // Since there is no literal, reput the char into the stream
        ungetc(c, file);
      VECTOR_T_PUSH(data, char, &c);
      break;
    }
    // New integer
    READ_DATA_INTEGER('B',B)
    READ_DATA_INTEGER('H',H)
    READ_DATA_INTEGER('W',W)
    READ_DATA_INTEGER('L',L)
    default:
      fprintf(stderr, "Unknown directive %s.\n", instruction);
      exit(EXIT_FAILURE);
  }
}

void read_asm_file(FILE *file, vector_t *data, vector_t *text){

  section_t section = TEXT;

  int c;

  // Lookup table for label require points
  vector_t lut = {.element_size = sizeof(pair_string_index_t)};

  // Map for labels.
  map_t labels;
  map_init(&labels);

  // The first character is reserved for data/text flag
  char token[MAX_TOKEN_LEN+2];
  size_t token_pointer = 1;

  // Scan file char by char
  while(c = fgetc(file), c != EOF && c != '\0')
    switch(c){
      case ';':
        // Comment
        do
          c = fgetc(file);
        while (c != '\n' && c != '\r' && c != EOF);
        break;

      case ' ':
      case '\t':
      case '\n':
      case '\r':
        // Ignore spaces
        if(token_pointer > 1)
          switch(section){
            case TEXT:
              read_operand(token+1, file, text, &lut);
              break;
            case DATA:
              read_data(token+1, file, data);
          }
        token_pointer = 1;
        break;

      case ':':
        // Label end
        if(token_pointer > 1){
          token[0] = section == DATA ? 'd' : 't';
          map_insert(&labels, token, section == DATA ? data->size : text->size);
        }else{
          fprintf(stderr,"Unexpected colon.\n");
          exit(EXIT_FAILURE);
        }
        token_pointer = 1;
        break;

      case '.':
        // Change section
        section = read_section(file);
        break;

      default:
        // Token
        if(token_pointer == MAX_TOKEN_LEN){
          fprintf(stderr,"Token too long: \"%s\".\n",token);
          exit(EXIT_FAILURE);
        }
        token[token_pointer] = c;
        token[++token_pointer] = '\0';
    }

  // Lookup label addresses
  for(size_t i = 0; i < lut.size; ++i){
    pair_string_index_t * subst= (pair_string_index_t*)vector_at(&lut, i);
    map_item_t *item = map_find(&labels, subst->string);
    if(item)
      ((instruction_t*)vector_at(text, subst->index))->operand.ptr = item->value;
    else{
      fprintf(stderr, "Label %s not defined.\n", subst->string+1);
      exit(EXIT_FAILURE);
    }
    free(subst->string);
  }

  vector_deallocate(&lut);
  map_deallocate(&labels);
}
