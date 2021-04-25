#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"
#include "riscv.h"


// forward declarations
void execute_rtype(Instruction, Processor *);
void execute_itype_except_load(Instruction, Processor *);
void execute_branch(Instruction, Processor *);
void execute_jalr(Instruction, Processor *);
void execute_jal(Instruction, Processor *);
void execute_load(Instruction, Processor *, Byte *);
void execute_store(Instruction, Processor *, Byte *);
void execute_ecall(Processor *, Byte *);
void execute_auipc(Instruction, Processor *);
void execute_lui(Instruction, Processor *);


void execute_instruction(Instruction instruction,Processor *processor,Byte *memory) {
  /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
  switch(instruction.opcode) { // What do we switch on?
    /* YOUR CODE HERE */

    case 0x17:
      execute_auipc(instruction, processor);
    break;

    case 0x37:
      execute_lui(instruction, processor);
    break;

    case 0x23:
      execute_store(instruction, processor, memory);
    break;

    case 0x63:
      execute_branch(instruction, processor);
    break;

    case 0x67:
      execute_jalr(instruction, processor);
    break;

    case 0x03:
      execute_load(instruction, processor, memory);
    break;

    case 0x13:
      execute_itype_except_load(instruction, processor);
    break;

    case 0x73:
      execute_ecall(processor, memory);
    break;

    case 0x6f:
      execute_jal(instruction, processor);
    break;

    case 0x33:
      execute_rtype(instruction, processor);
    break;

    default:
      handle_invalid_instruction(instruction);
      exit(-1);
    break;
  }
}



void execute_rtype(Instruction instruction, Processor *processor) {
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default:
      handle_invalid_instruction(instruction);
      exit(-1);
      break;
  }
}


void execute_itype_except_load(Instruction instruction, Processor *processor) {
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default:
        handle_invalid_instruction(instruction);
        break;
  }
}


void execute_ecall(Processor *p, Byte *memory) {
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default: // undefined ecall
      printf("Illegal ecall number %d\n", -1); // What stores the ecall arg?
      exit(-1);
      break;
  }
}


void execute_branch(Instruction instruction, Processor *processor) {
  /* Remember that the immediate portion of branches
     is counting half-words, so make sure to account for that. */
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default:
      handle_invalid_instruction(instruction);
      exit(-1);
      break;
  }
}


void execute_load(Instruction instruction, Processor *processor, Byte *memory) {
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void execute_store(Instruction instruction, Processor *processor, Byte *memory) {
  switch(0) { // What do we switch on?
    /* YOUR CODE HERE */
    default:
      handle_invalid_instruction(instruction);
      exit(-1);
      break;
  }
}


void execute_jalr(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
}


void execute_jal(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
}


void execute_auipc(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
}


void execute_lui(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
}


/* Checks that the address is aligned correctly */
int check(Address address, Alignment alignment) {
  if (address > 0 && address < MEMORY_SPACE) {
    // byte align
    if (alignment == LENGTH_BYTE) return 1;
    // half align
    if (alignment == LENGTH_HALF_WORD) return ((address % 2) == 0);
    // word align
    if (alignment == LENGTH_WORD) return ((address % 4) == 0);
  }
  return 0;
}


void store(Byte *memory, Address address, Alignment alignment, Word value, int check_align) {
  if ((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
    handle_invalid_write(address);
  }
  /* YOUR CODE HERE */
}


Word load(Byte *memory, Address address, Alignment alignment, int check_align) {
  if ((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
    handle_invalid_read(address);
  }
  /* YOUR CODE HERE */
  return 0;
}
