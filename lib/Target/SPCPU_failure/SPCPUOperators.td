//===-- SPCPUOperators.td - SPCPU-specific Operators ---*- tablegen -*-===//
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

def SPCPURetFlag : SDNode< "SPCPUISD::RET_FLAG", SDTNone,
	[ SDNPHasChain, SDNPOptInGlue, SDNPVariadic ]>;
