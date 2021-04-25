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
  Word rd = instruction.rtype.rd;
  Word rs1 = (*processor).R[instruction.rtype.rs1];
  Word rs2 = (*processor).R[instruction.rtype.rs2];
  Double rs1_double = (*processor).R[instruction.rtype.rs1];
  Double rs2_double = (*processor).R[instruction.rtype.rs2];
  sWord rs1_signed = (*processor).R[instruction.rtype.rs1];
  sWord rs2_signed = (*processor).R[instruction.rtype.rs2];
  sDouble rs1_signed_double = (*processor).R[instruction.rtype.rs1];
  sDouble rs2_signed_double = (*processor).R[instruction.rtype.rs2];
  sWord pc = (*processor).PC;
  switch(instruction.rtype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
      if (instruction.rtype.funct7 == 0)
      {
        (*processor).R[rd] = (Word)(rs1_signed + rs2_signed);
      }
      else if (instruction.rtype.funct7 == 0x1)
      {
        (*processor).R[rd] = (Word)(rs1_signed * rs2_signed);
      }
      else
      {
        (*processor).R[rd] = (Word)(rs1_signed - rs2_signed);
      }
    break;

    case 0x1:
      if (instruction.rtype.funct7 != 0) {
        sDouble resp = (rs1_signed_double * rs2_signed_double) & 0xFFFFFFFF00000000;
        (*processor).R[rd] = (sWord)(resp >> 32);
      } else {
        (*processor).R[rd] = rs1 << rs2;
      }
    break;

    case 0x2:
      (*processor).R[rd] = (rs1_signed < rs2_signed)? 1 : 0;
    break;

    case 0x4:
      if (instruction.rtype.funct7 == 0x00) {
        (*processor).R[rd] = rs1 ^ rs2;
      } else {
        if (rs2 == 0)
        {
          (*processor).R[rd] =(sWord)  -1;
        }
        else
        {
          (*processor).R[rd] = (sWord) ((rs1_signed_double) / (rs1_signed_double));
        }
        
      }
    break;

    case 0x5:
      if (instruction.rtype.funct7 != 0) {
        (*processor).R[rd] = (rs1_signed >> rs2);
      } else {
        (*processor).R[rd] = (Word) (rs1 >> rs2);
      }
    break;

    case 0x6:
      if (instruction.rtype.funct7 != 0) {
        if (rs2 != 0)
        {
          (*processor).R[rd] = (sWord)((rs1_signed_double) % (rs1_signed_double));
        }
        else
        {
          (*processor).R[rd] = rs1;
        }
      } else {
        (*processor).R[rd] = rs1 | rs2;
      }
    break;

    case 0x7:
      (*processor).R[rd] = rs1 & rs2;
    break;

    default:
      handle_invalid_instruction(instruction);
      exit(-1);
    break;
  }
  (*processor).PC = pc + 4;
}


void execute_itype_except_load(Instruction instruction, Processor *processor) {
  Word rd = instruction.itype.rd;
  Word imm = instruction.itype.imm;
  Word imm_signed = bitSigner(imm, 12);
  Word rs1 = (*processor).R[instruction.itype.rs1];
  sWord rs1_signed = (*processor).R[instruction.itype.rs1];
  sWord pc = (*processor).PC;

  switch(instruction.itype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
      (*processor).R[rd] = (Word) ( rs1_signed + imm_signed);
    break;

    case 0x1:
      (*processor).R[rd] = rs1 << imm_signed;
    break;

    case 0x2:
      (*processor).R[rd] = (rs1_signed < (int)imm_signed)? 1: 0;
    break;

    case 0x4:
      (*processor).R[rd] = rs1 ^ imm_signed;
    break;

    case 0x5:
      if ((instruction.itype.imm & 4064) != 0) {
        (*processor).R[rd] = (rs1_signed >> (imm & 0b11111));
      } else {
        (*processor).R[rd] = rs1 >> (imm & 0b11111);
      }
    break;

    case 0x6:
      (*processor).R[rd] = rs1 | imm_signed;
    break;

    case 0x7:
      (*processor).R[rd] = rs1 & imm_signed;
    break;

    default:
      handle_invalid_instruction(instruction);
    break;
  }
  (*processor).PC = pc + 4;
}

void execute_ecall(Processor *p, Byte *memory) {
  sWord pc = (*p).PC;
  if ((*p).R[10] == 10)
  {
    printf("exiting the simulator\n");
    exit(0);
  }
  else if ((*p).R[10] == 1)
  {
    printf("%d", (*p).R[11]);
    p->PC = pc + 4;
  }
  else
  {
    printf("Illegal ecall number %d\n", (*p).R[10]); // What stores the ecall arg?
    exit(-1);
  }
  
}

void execute_branch(Instruction instruction, Processor *processor) {
  Double rs1 = (*processor).R[instruction.rtype.rs1];
  Double rs2 = (*processor).R[instruction.rtype.rs2];
  sHalf offset = (sHalf)get_branch_offset(instruction);
  sHalf salto = 4;

    /* Remember that the immediate portion of branches
       is counting half-words, so make sure to account for that. */
  switch(instruction.sbtype.funct3) { // What do we switch on?
      /* YOUR CODE HERE */
    case 0x0:
      if (rs1 == rs2)
      {
        salto = offset;
      }
    break;

    case 0x1:
      if (rs1 != rs2)
      {
        salto = offset;
      }
    break;

    default:
      handle_invalid_instruction(instruction);
      exit(-1);
    break;
  }
  
  (*processor).PC = (*processor).PC + salto;
    
}


void execute_load(Instruction instruction, Processor *processor, Byte *memory) {
  Word rd = instruction.itype.rd;
  sWord rs1 = processor->R[instruction.itype.rs1];
  sWord imm = bitSigner(instruction.itype.imm, 12);
  Address direccion_memoria = rs1 + imm;
  Word carga = 0;
  switch(instruction.itype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */

    case 0x1:
      carga = load(memory, (direccion_memoria), LENGTH_HALF_WORD, 0);
      processor->R[rd] = bitSigner(carga, 16);
    break;

    case 0x2:
      carga = load(memory, (direccion_memoria), LENGTH_WORD, 0);
      processor->R[rd] = carga;
    break;

    case 0x0:
      carga = load(memory, (direccion_memoria), LENGTH_BYTE, 0);
      processor->R[rd] = bitSigner(carga, 8);
    break;

    default:
      handle_invalid_instruction(instruction);
    break;
  }
  processor->PC += 4;
}

void execute_store(Instruction instruction, Processor *processor, Byte *memory) {

  int offset = get_store_offset(instruction);
  Word rs1 = (*processor).R[instruction.stype.rs1];
  sWord address = rs1 + get_store_offset(instruction);
  Word rs2 = (*processor).R[instruction.stype.rs2];
  sWord pc = (*processor).PC;

  switch(instruction.stype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */

    case 0x1:
      store(memory, address, LENGTH_HALF_WORD, rs2, 0);
    break;

    case 0x2:
      store(memory, address, LENGTH_WORD, rs2, 0);
    break;
    
    case 0x0:
      store(memory, address, LENGTH_BYTE, rs2, 0);
    break;

    default:
      handle_invalid_instruction(instruction);
      exit(-1);
    break;
  }
  (*processor).PC = pc + 4;
}


void execute_jalr(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  Word rd = instruction.itype.rd;
  Word pc = (*processor).PC;
  int imm_signed = bitSigner(instruction.itype.imm, 12);
  int nuevo_pc = (*processor).R[instruction.itype.rs1] + imm_signed;

  (*processor).R[rd] = pc + 4;
  (*processor).PC = nuevo_pc;
}


void execute_jal(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  Word rd = instruction.ujtype.rd;
  Word pc = (*processor).PC;
  int offset = get_jump_offset(instruction);

  (*processor).R[rd] = pc + 4;
  (*processor).PC = pc + offset;
}

void execute_lui(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  Word pc = (*processor).PC;
  Word rd = instruction.utype.rd;
  unsigned int nuevo_rd = instruction.utype.imm << 12;
  (*processor).R[rd] = nuevo_rd;
  (*processor).PC = pc + 4;
}

void execute_auipc(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  Word rd = instruction.utype.rd;
  Word pc = (*processor).PC;
  unsigned int nuevo_rd = instruction.utype.imm << 12;

  (*processor).R[rd] = pc + nuevo_rd;
  (*processor).PC = pc + 4;
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

void store(Byte *memory,Address address,Alignment alignment,Word value, int check_align) {
    if((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
        handle_invalid_write(address);
    }
    /* YOUR CODE HERE */
    Word a;
    Word b;
    Word c;
    switch(alignment) {
        case LENGTH_BYTE:
          memory[address] = (Byte) (value & 0b11111111);
        break;

        case LENGTH_HALF_WORD:
          a = value >> 8;
          memory[address] = (Byte) (value & 0b11111111);
          memory[address + 1] = (Byte) (a & 0b11111111);
        break;

        case LENGTH_WORD:
          a = value >> 8;
          b = value >> 16;
          c = value >> 24;
          memory[address] = (Byte) (value & 0b11111111);
          memory[address + 1] = (Byte) (a & 0b11111111);
          memory[address + 2] = (Byte) (b & 0b11111111);
          memory[address + 3] = (Byte) (c & 0b11111111);
        break;
        default:
            return;
            break;
    }
}


Word load(Byte *memory,Address address,Alignment alignment, int check_align) {
    if((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
    handle_invalid_read(address);
    }  
    /* YOUR CODE HERE */

    switch(alignment) {
      case LENGTH_BYTE:
        return memory[address];
      break;
      
      case LENGTH_HALF_WORD:
        return memory[address] | (memory[address + 1] << 8);
      break;

      case LENGTH_WORD:
        return memory[address] | (memory[address + 1] << 8) | (memory[address + 2] << 16) | (memory[address + 3] << 24);
      break;

      default:
      break;
    }
    return 0;
}
