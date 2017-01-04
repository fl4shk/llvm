//===-- SPCPUMCAsmInfo.h - SPCPU asm properties --------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the SPCPUMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#pragma once
#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class StringRef;
class Target;
class Triple;

class SPCPUMCAsmInfo : public MCAsmInfoELF {
  virtual void anchor();

public:
  explicit SPCPUMCAsmInfo(const Triple &TT);
};

} // namespace llvm
