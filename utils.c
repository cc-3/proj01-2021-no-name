#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


//sign extends a bitfield with given size
/* You may find implementing this function helpful */
int bitSigner(unsigned int field, unsigned int size) {
    /* YOUR CODE HERE */
    signed int conSigno = field << (32 - size);
    signed int final = conSigno >> (32 - size);
    return final;
}


/* Remember that the offsets should return the offset in BYTES */


int get_branch_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  int offset = 0;
  int offset2 = 0;
  int offset_final = 0;

  unsigned int digitos_imm7 = instruction.sbtype.imm7 << 5;
  offset = 0b11111100000 & digitos_imm7;
  offset_final = offset_final | offset;

  unsigned int digitos_imm5 = 0b11110 & instruction.sbtype.imm5;
  offset_final = digitos_imm5 | offset;

  unsigned int digitos_imm7_2 = instruction.sbtype.imm7 << 6;
  offset2 = 0b1000000000000 & digitos_imm7_2;
  offset_final = offset_final | offset2;
  
  unsigned int digitos_imm5_2 = instruction.sbtype.imm5 << 11;
  int digitos_imm5_3 = 0b100000000000 & digitos_imm5_2;
  offset_final = offset_final | digitos_imm5_3;


  return bitSigner(offset_final, 13);
}



int get_jump_offset(Instruction instruction) {
  /* YOUR CODE HERE */

  unsigned int digitos_imm2 = instruction.ujtype.imm << 3;
  int digitos_imm2_2 = 0b100000000000 & digitos_imm2;
  int offset_final = digitos_imm2_2;

  unsigned int digitos_imm1 = instruction.ujtype.imm << 12;
  int digitos_imm1_2 = 0b11111111000000000000 & digitos_imm1;
  offset_final = offset_final | digitos_imm1_2;

  unsigned int digitos_Imm4 = instruction.ujtype.imm << 2;
  int digitos_Imm4_2 = 0b100000000000000000000 & digitos_Imm4;
  offset_final = offset_final | digitos_Imm4_2;


  unsigned int digitos_Imm3 = instruction.ujtype.imm >> 8;
  int digitos_Imm3_2 = 0b11111111110 & digitos_Imm3;
  offset_final = offset_final | digitos_Imm3_2;

  return bitSigner(offset_final, 21);
}


int get_store_offset(Instruction instruction) {
  /* YOUR CODE HERE */

  ////hay que modificar esto que es de otro proyecto
  
  unsigned int digitos_imm7 = instruction.stype.imm7 << 5;
  int digitos_imm7_2 = 0b111111100000 & digitos_imm7;
  int offset_final = digitos_imm7_2;

  unsigned int digitos_imm5 = 0b11111 & instruction.stype.imm5;
  offset_final = offset_final | digitos_imm5;

  return bitSigner(offset_final, 12); 
}

void handle_invalid_instruction(Instruction instruction) {
  printf("Invalid Instruction: 0x%08x\n", instruction.bits);
}


void handle_invalid_read(Address address) {
  printf("Bad Read. Address: 0x%08x\n", address);
  exit(-1);
}


void handle_invalid_write(Address address) {
  printf("Bad Write. Address: 0x%08x\n", address);
  exit(-1);
}
