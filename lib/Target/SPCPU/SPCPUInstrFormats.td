//===-- SPCPUInstrFormats.td - SPCPU Instruction Formats ---*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//
class InstSPCPU<dag outs, dag ins, string asmstr, list<dag> pattern>
    : Instruction {
  field bits<32> Inst;

  // Mask of bits that cause an encoding to be UNPREDICTABLE.
  // If a bit is set, then if the corresponding bit in the
  // target encoding differs from its value in the "Inst" field,
  // the instruction is UNPREDICTABLE (SoftFail in abstract parlance).
  field bits<32> Unpredictable = 0;
  // SoftFail is the generic name for this field, but we alias it so
  // as to make it more obvious what it means in ARM-land.
  field bits<32> SoftFail = Unpredictable;

  let Namespace = "SPCPU";
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString   = asmstr;
  let Pattern = pattern;
  let Size = 4;
}

// SPCPU pseudo instructions format
class SPCPUPseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstSPCPU<outs, ins, asmstr, pattern> {
  let isPseudo = 1;
}

class ALUInst<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstSPCPU<outs, ins, asmstr, pattern> {

  bits<7> dst;
  bits<7> src1;
  bits<7> src2;

  let Inst{31-30} = 0b00;
  let Inst{29-26} = opcode;

  let Inst{20-14} = src1;
  let Inst{13-7} = dst;
  let Inst{6-0}   = src2;
}
