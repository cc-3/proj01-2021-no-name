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
  unsigned int imm = instruction.itype.imm;
  int immBits = imm & 0b11111;

  switch(instruction.itype.funct3) {
    case 0:
      print_itype_except_load("addi", instruction, bitSigner(instruction.itype.imm, 12));
    break;
    
    case 1:
      print_itype_except_load("slli", instruction, bitSigner(instruction.itype.imm, 12));
    break;
    
    case 2:
      print_itype_except_load("slti", instruction, bitSigner(instruction.itype.imm, 12));
    break;
    
    case 4:
      print_itype_except_load("xori", instruction, bitSigner(instruction.itype.imm, 12));
    break;
    
    case 5:
      if (instruction.itype.imm & 0b111111100000)
      {
        print_itype_except_load("srai", instruction, imm & 0b11111);
      }else{
        print_itype_except_load("srli", instruction, imm & 0b11111);
      }
    break;
    
    case 6:
      print_itype_except_load("ori", instruction, bitSigner(instruction.itype.imm, 12));
    break;
    
    case 7:
      print_itype_except_load("andi", instruction, bitSigner(instruction.itype.imm, 12));
    break;
    
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}

void write_load(Instruction instruction)
{  
  switch(instruction.itype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0:
        print_load("lb", instruction);
        break;

    case 1:
        print_load("lh", instruction);
        break;

    case 2:
        print_load("lw", instruction);
        break;

    default:
      handle_invalid_instruction(instruction);
      break;
  }
}

void write_store(Instruction instruction)
{
  switch(instruction.itype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0:
      print_store("sb", instruction);
    break;

    case 1:
      print_store("sh", instruction);
    break;

    case 2:
      print_store("sw", instruction);
    break;

    default:
      handle_invalid_instruction(instruction);
    break;
  }
}

void write_branch(Instruction instruction)
{
  switch(instruction.itype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0:
      print_branch("beq", instruction);
    break;

    case 1:
      print_branch("bne", instruction);
    break;
    
    default:
      handle_invalid_instruction(instruction);
    break;
  }
}

/* For the writes, probably a good idea to take a look at utils.h */

void write_auipc(Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(AUIPC_FORMAT, instruction.utype.rd, instruction.utype.imm);
}

void write_lui(Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(LUI_FORMAT, instruction.utype.rd, (sWord) instruction.utype.imm);
}

void write_jalr(Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(JALR_FORMAT, instruction.itype.rd, instruction.itype.rs1, (sWord) bitSigner(instruction.itype.imm, 11));
}

void write_jal(Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(JAL_FORMAT, instruction.ujtype.rd, get_jump_offset(instruction));
}

void write_ecall(Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(ECALL_FORMAT);
}

void print_rtype(char *name, Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(RTYPE_FORMAT, name, instruction.rtype.rd, instruction.rtype.rs1, instruction.rtype.rs2);
}

void print_itype_except_load(char *name, Instruction instruction, int imm)
{
  /* YOUR CODE HERE */
  printf(ITYPE_FORMAT, name, instruction.itype.rd, instruction.itype.rs1, (sWord) imm);
}

void print_load(char *name, Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(MEM_FORMAT, name, instruction.itype.rd, (sWord) bitSigner(instruction.itype.imm, 12), instruction.itype.rs1);
}

void print_store(char *name, Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(MEM_FORMAT, name, instruction.stype.rs2, get_store_offset(instruction), instruction.stype.rs1);
}

void print_branch(char *name, Instruction instruction)
{
  /* YOUR CODE HERE */
  printf(BRANCH_FORMAT, name, instruction.sbtype.rs1, instruction.sbtype.rs2, get_branch_offset(instruction));
}
