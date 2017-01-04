//===-- SPCPUInstrInfo.td - Target Description for SPCPU ---*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file describes the SPCPU instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

include "SPCPUInstrFormats.td"
include "SPCPUOperators.td"

//===----------------------------------------------------------------------===//
// ALU Instructions
//===----------------------------------------------------------------------===//
multiclass BinOp<bits<4> opcode, string opstr, SDNode opnode> {
  def rr : ALUInst<opcode, (outs reg_pairs:$dst),
                   (ins reg_pairs:$src1, reg_pairs:$src2),
                   !strconcat(opstr, " $dst, $src1, $src2"),
                   [(set i32:$dst, (opnode i32:$src1, i32:$src2))]> {
    bits<4> dst;
    bits<4> src1;
    bits<4> src2;
//    let Inst{25} = 0;
//    let Inst{20} = 0;  // We never update flags
//    let Inst{19-16} = src1;
//    let Inst{15-12} = dst;
//    let Inst{11-4}  = 0b00000000;
//    let Inst{3-0}   = src2;
  }
}

defm ADD  : BinOp<0b0000, "add", add>;

def SPCPUcallseq_start : SDNode<"ISD::CALLSEQ_START",
                                SDCallSeqStart<[ SDTCisVT<0, i32> ]>,
                                [SDNPHasChain, SDNPOutGlue]>;
def SPCPUcallseq_end   : SDNode<"ISD::CALLSEQ_END",
                                SDCallSeqEnd<[ SDTCisVT<0, i32>,
                                               SDTCisVT<1, i32> ]>,
                                [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

//===----------------------------------------------------------------------===//
// Pseudo Instructions
//===----------------------------------------------------------------------===//

let Defs = [sp], Uses = [sp] in {
def ADJCALLSTACKDOWN : SPCPUPseudoInst<(outs), (ins i32imm:$amt),
                                    "# ADJCALLSTACKDOWN $amt",
                                    [(SPCPUcallseq_start timm:$amt)]>;
def ADJCALLSTACKUP   : SPCPUPseudoInst<(outs), (ins i32imm:$amt1, i32imm:$amt2),
                                    "# ADJCALLSTACKUP $amt1",
                                    [(SPCPUcallseq_end timm:$amt1, timm:$amt2)]>;
}

