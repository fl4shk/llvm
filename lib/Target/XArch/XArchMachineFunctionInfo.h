//===-- XArchMachineFuctionInfo.h - XArch machine function info -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares XArch-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

// Forward declarations
class Function;

/// XArchFunctionInfo - This class is derived from MachineFunction private
/// XArch target-specific information for each MachineFunction.
class XArchFunctionInfo : public MachineFunctionInfo {
public:
  XArchFunctionInfo() {}

  ~XArchFunctionInfo() {}
};
} // End llvm namespace
