//===-- XArchTargetInfo.cpp - XArch Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "XArch.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

namespace llvm
{
  Target TheXArchTarget;
}

extern "C" void LLVMInitializeXArchTargetInfo() {
  RegisterTarget<Triple::xarch> X(TheXArchTarget, "xarch", "XArch");
}
