#include <stdio.h>  // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"

// forward declarations
void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction);
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);
void write_auipc(Instruction);
void write_lui(Instruction);
void write_jalr(Instruction);
void write_jal(Instruction);
void write_ecall(Instruction);

void decode_instruction(Instruction instruction)
{
  /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
  unsigned int opcode = instruction.opcode;
  switch (opcode)
  { // What do we switch on?
    /* YOUR CODE HERE */

  case 51:
    write_rtype(instruction);
    break;

  case 19:
    write_itype_except_load(instruction);
    break;

  case 3:
    write_load(instruction);
    break;

  case 103:
    write_jalr(instruction);
    break;

  case 115:
    write_ecall(instruction);
    break;

  case 35:
    write_store(instruction);
    break;

  case 99:
    write_branch(instruction);
    break;

  case 55:
    write_lui(instruction);
    break;

  case 111:
    write_jal(instruction);
    break;

  case 0X17:
    write_auipc(instruction);
    break;

  default: // undefined opcode
    handle_invalid_instruction(instruction);
    break;
  }
}

void write_rtype(Instruction instruction)
{
  switch (instruction.rtype.funct3)
  { // What do we switch on?
  /* YOUR CODE HERE */
  case 0:
    switch (instruction.rtype.funct7)
    {
    case 0:
      print_rtype("add", instruction);
      break;

    case 1:
      print_rtype("mul", instruction);
      break;

    case 32:
      print_rtype("sub", instruction);
      break;

    default:
      handle_invalid_instruction(instruction);
      break;
    }
    break;

  case 1:
    switch (instruction.rtype.funct7)
    {
    case 0:
      print_rtype("sll", instruction);
      break;

    case 1:
      print_rtype("mulh", instruction);
      break;

    default:
      handle_invalid_instruction(instruction);
      break;
    }
    break;

  case 2:
    print_rtype("slt", instruction);
    break;

  case 4:
    switch (instruction.rtype.funct7)
    {
    case 0:
      print_rtype("xor", instruction);
      break;

    case 1:
      print_rtype("div", instruction);
      break;

    default:
      handle_invalid_instruction(instruction);
      break;
    }
    break;

  case 5:
    switch (instruction.rtype.funct7)
    {
    case 0:
      print_rtype("srl", instruction);
      break;

    case 32:
      print_rtype("sra", instruction);
      break;
    }
    break;

  case 6:
    switch (instruction.rtype.funct7)
    {
    case 0:
      print_rtype("or", instruction);
      break;

    case 1:
      print_rtype("rem", instruction);
      break;

    default:
      handle_invalid_instruction(instruction);
      break;
    }
    break;

  case 7:
    print_rtype("and", instruction);
    break;

  default:
    handle_invalid_instruction(instruction);
    break;
  }
}

void write_itype_except_load(Instruction instruction)
{
  switch (0)
  { // What do we switch on?
  /* YOUR CODE HERE */
  default:
    handle_invalid_instruction(instruction);
    break;
  }
}

void write_load(Instruction instruction)
{
  switch (0)
  { // What do we switch on?
  /* YOUR CODE HERE */
  default:
    handle_invalid_instruction(instruction);
    break;
  }
}

void write_store(Instruction instruction)
{
  switch (0)
  { // What do we switch on?
  /* YOUR CODE HERE */
  default:
    handle_invalid_instruction(instruction);
    break;
  }
}

void write_branch(Instruction instruction)
{
  switch (0)
  { // What do we switch on?
  /* YOUR CODE HERE */
  default:
    handle_invalid_instruction(instruction);
    break;
  }
}

/* For the writes, probably a good idea to take a look at utils.h */

void write_auipc(Instruction instruction)
{
  /* YOUR CODE HERE */
}

void write_lui(Instruction instruction)
{
  /* YOUR CODE HERE */
}

void write_jalr(Instruction instruction)
{
  /* YOUR CODE HERE */
}

void write_jal(Instruction instruction)
{
  /* YOUR CODE HERE */
}

void write_ecall(Instruction instruction)
{
  /* YOUR CODE HERE */
}

void print_rtype(char *name, Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(RTYPE_FORMAT, name, instruction.rtype.rd, instruction.rtype.rs1, instruction.rtype.rs2);
}

void print_itype_except_load(char *name, Instruction instruction, int imm)
{
  /* YOUR CODE HERE */
}

void print_load(char *name, Instruction instruction)
{
  /* YOUR CODE HERE */
}

void print_store(char *name, Instruction instruction)
{
  /* YOUR CODE HERE */
}

void print_branch(char *name, Instruction instruction)
{
  /* YOUR CODE HERE */
}
