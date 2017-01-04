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
  field bits<128> Inst;

  let Namespace = "SPCPU";
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString   = asmstr;
  let Pattern = pattern;
  let Size = 16;
}

// SPCPU pseudo instructions format
class SPCPUPseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstSPCPU<outs, ins, asmstr, pattern> {
  let isPseudo = 1;
}

class ALUInst<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstSPCPU<outs, ins, asmstr, pattern> {
  let Inst{127-126} = 0b00;
  let Inst{125-122} = opcode;
}
