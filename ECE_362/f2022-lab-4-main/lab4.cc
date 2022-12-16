#include "lab4.h"
#include <stdint.h>
#include <stdio.h>

// Assume that the least significant 11 bits of instBits
// contain the instruction bits [31-21].
// Set the output signals as follows:
//  outputSignals.Reg2Loc = 1;
void setControl(uint64_t instBits, ControlSignals& outputSignals) 
{
  // opcodes:
  // ADD:  10001011000
  // ADDI: 1001000100
  // SUB:  11001011000
  // SUBI: 1101000100
  // LDUR: 11111000010
  // STUR: 11111000000
  // ORR:  10101010000
  // CBZ:  10110100

  if (instBits == 0x458) // ADD
  {
    outputSignals.Reg2Loc = 0;
    outputSignals.Branch = 0;
    outputSignals.MemRead = 0;
    outputSignals.MemtoReg = 0;
    outputSignals.ALUOp = 0;
    outputSignals.MemWrite = 0;
    outputSignals.ALUSrc = 0;
    outputSignals.RegWrite = 1;
  }
  else if (instBits >= 0x488 && instBits <= 0x489) // ADDI
  {
    outputSignals.Reg2Loc = 0; // Dont care
    outputSignals.Branch = 0;
    outputSignals.MemRead = 0;
    outputSignals.MemtoReg = 0;
    outputSignals.ALUOp = 0;
    outputSignals.MemWrite = 0;
    outputSignals.ALUSrc = 1;
    outputSignals.RegWrite = 1;
  }
  else if (instBits == 0x658) // SUB
  {
    outputSignals.Reg2Loc = 0;
    outputSignals.Branch = 0;
    outputSignals.MemRead = 0;
    outputSignals.MemtoReg = 0;
    outputSignals.ALUOp = 2;
    outputSignals.MemWrite = 0;
    outputSignals.ALUSrc = 0;
    outputSignals.RegWrite = 1;
  }
  else if (instBits >= 0x688 && instBits <= 0x689) // SUBI
  {
    outputSignals.Reg2Loc = 0; // Dont care
    outputSignals.Branch = 0;
    outputSignals.MemRead = 0;
    outputSignals.MemtoReg = 0;
    outputSignals.ALUOp = 2;
    outputSignals.MemWrite = 0;
    outputSignals.ALUSrc = 1;
    outputSignals.RegWrite = 1;
  }
  else if (instBits == 0x7C2) // LDUR
  {
    outputSignals.Reg2Loc = 0; // Dont care
    outputSignals.Branch = 0;
    outputSignals.MemRead = 1;
    outputSignals.MemtoReg = 1;
    outputSignals.ALUOp = 0;
    outputSignals.MemWrite = 0;
    outputSignals.ALUSrc = 1;
    outputSignals.RegWrite = 1;
  }
  else if (instBits == 0x7C0) // STUR
  {
    outputSignals.Reg2Loc = 1;
    outputSignals.Branch = 0;
    outputSignals.MemRead = 0;
    outputSignals.MemtoReg = 0; // Dont care
    outputSignals.ALUOp = 0;
    outputSignals.MemWrite = 1;
    outputSignals.ALUSrc = 1;
    outputSignals.RegWrite = 0;
  }
  else if (instBits == 0x550) // ORR
  {
    outputSignals.Reg2Loc = 0;
    outputSignals.Branch = 0;
    outputSignals.MemRead = 0;
    outputSignals.MemtoReg = 0;
    outputSignals.ALUOp = 2;
    outputSignals.MemWrite = 0;
    outputSignals.ALUSrc = 0;
    outputSignals.RegWrite = 1;
  }
  else if (instBits >= 0x5A0 && instBits <= 0x5A7) // CBZ
  {
    outputSignals.Reg2Loc = 1;
    outputSignals.Branch = 1;
    outputSignals.MemRead = 0;
    outputSignals.MemtoReg = 0; // Dont care
    outputSignals.ALUOp = 3;
    outputSignals.MemWrite = 0;
    outputSignals.ALUSrc = 0;
    outputSignals.RegWrite = 0;
  }
}

// Assume that the lower 32-bits of instBits contain the instruction.
// Return the appropraite sign extended version of the embedded
// immediate, based on the instruction type.
uint64_t getExtendedBits(uint64_t instBits)
{
  uint64_t returnVal = 0;
  const uint64_t one = 1;
  
  // Find intruction type & sign extend
  uint64_t opbits = instBits >> 22; // Extract 10-bit opcode
  if (opbits == 0b1001000100 || opbits == 0b1101000100) // ADDI, SUBI
  {
    // create a 0xFFFFF....000 value
    uint64_t exclude = 0;
    for (int i = 63; i > 11; i--)
    {
      exclude |= (one << i);
    }

    // create a 0x00000....XYZ value
    returnVal = instBits >> 10;
    returnVal = returnVal & 0xfff;

    // if first bit != 0
    if ((returnVal >> 11) != 0b0)
    {
      // sign extend one
      returnVal = returnVal | exclude; // or the two values and return
    }
  }
  else
  {
    uint64_t opbits = instBits >> 21; // Extract 11-bit opcode
    if (opbits == 0b11111000010 || opbits == 0b11111000000) // LDUR, STUR
    {
      // create a 0xFFFFF....000 value
      uint64_t exclude = 0;
      for (int i = 63; i > 8; i--)
      {
        exclude |= (one << i);
      }

      // create a 0x00000....XYZ value
      returnVal = instBits >> 12;
      returnVal = returnVal & 0b111111111;

      // if first bit != 0
      if ((returnVal >> 8) != 0b0)
      {
        // sign extend one
        returnVal = returnVal | exclude; // or the two values and return
      }

    }
    else  // CBZ
    {
      // create a 0xFFFFF....000 value
      uint64_t exclude = 0;
      for (int i = 63; i > 18; i--)
      {
        exclude |= (one << i);
      }

      // create a 0x00000....XYZ value
      returnVal = instBits >> 5;
      returnVal = returnVal & 0b1111111111111111111;

      // if first bit != 0
      if ((returnVal >> 18) != 0b0)
      {
        // sign extend one
        returnVal = returnVal | exclude; // or the two values and return
      } 
    }
  }
  
  return returnVal;
}
