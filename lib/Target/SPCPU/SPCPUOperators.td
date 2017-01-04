//===-- SPCPUOperators.td - SPCPU-specific operators ------*- tblgen-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

def MoveImm32Ty : SDTypeProfile<1, 1, [
  SDTCisSameAs<0, 1>, SDTCisInt<0>
]>;


def SPCPUcallseq_start : SDNode<"ISD::CALLSEQ_START",
                                SDCallSeqStart<[ SDTCisVT<0, i32> ]>,
                                [SDNPHasChain, SDNPOutGlue]>;
def SPCPUcallseq_end   : SDNode<"ISD::CALLSEQ_END",
                                SDCallSeqEnd<[ SDTCisVT<0, i32>,
                                               SDTCisVT<1, i32> ]>,
                                [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

def SPCPURetFlag    : SDNode<"SPCPUISD::RET_FLAG", SDTNone,
                           [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def movei32 : SDNode<"SPCPUISD::MOVEi32", MoveImm32Ty>;
