//===-- XArch.h - Top-level interface for XArch representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// XArch back-end.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "MCTargetDesc/XArchMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TargetMachine;
class XArchTargetMachine;

FunctionPass *createXArchISelDag(XArchTargetMachine &TM,
                               CodeGenOpt::Level OptLevel);
} // end namespace llvm;
