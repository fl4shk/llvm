//===-- XArchMCAsmInfo.h - XArch asm properties --------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the XArchMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#pragma once
#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class StringRef;
class Target;
class Triple;

class XArchMCAsmInfo : public MCAsmInfoELF {
  virtual void anchor();

public:
  explicit XArchMCAsmInfo(const Triple &TT);
};

} // namespace llvm
