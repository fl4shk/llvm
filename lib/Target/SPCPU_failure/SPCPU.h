//===-- SPCPU.h - Top-level interface for SPCPU representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// SPCPU back-end.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "MCTargetDesc/SPCPUMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TargetMachine;
class SPCPUTargetMachine;

FunctionPass *createSPCPUISelDag(SPCPUTargetMachine &TM,
                               CodeGenOpt::Level OptLevel);
} // end namespace llvm;
