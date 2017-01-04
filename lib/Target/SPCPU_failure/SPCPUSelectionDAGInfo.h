//===-- SPCPUSelectionDAGInfo.h - SPCPU SelectionDAG Info -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the SPCPU subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/CodeGen/SelectionDAGTargetInfo.h"

namespace llvm {

class SPCPUSelectionDAGInfo : public SelectionDAGTargetInfo {
public:
  ~SPCPUSelectionDAGInfo();
};
}
