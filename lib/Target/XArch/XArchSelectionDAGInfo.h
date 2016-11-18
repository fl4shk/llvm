//===-- XArchSelectionDAGInfo.h - XArch SelectionDAG Info -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the XArch subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/CodeGen/SelectionDAGTargetInfo.h"

namespace llvm {

class XArchSelectionDAGInfo : public SelectionDAGTargetInfo {
public:
  ~XArchSelectionDAGInfo();
};
}
