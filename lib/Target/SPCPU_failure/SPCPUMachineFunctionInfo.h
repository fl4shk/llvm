//===-- SPCPUMachineFuctionInfo.h - SPCPU machine function info -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares SPCPU-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

// Forward declarations
class Function;

/// SPCPUFunctionInfo - This class is derived from MachineFunction private
/// SPCPU target-specific information for each MachineFunction.
class SPCPUFunctionInfo : public MachineFunctionInfo {
public:
  SPCPUFunctionInfo() {}

  ~SPCPUFunctionInfo() {}
};
} // End llvm namespace
