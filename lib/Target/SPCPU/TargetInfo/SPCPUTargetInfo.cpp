//===-- SPCPUTargetInfo.cpp - SPCPU Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SPCPU.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

namespace llvm
{
  Target TheSPCPUTarget;
}

extern "C" void LLVMInitializeSPCPUTargetInfo() {
  RegisterTarget<Triple::xarch> X(TheSPCPUTarget, "xarch", "SPCPU");
}
