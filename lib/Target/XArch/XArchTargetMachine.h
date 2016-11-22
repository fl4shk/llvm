//===-- XArchTargetMachine.h - Define TargetMachine for XArch ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the XArch specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "XArch.h"
#include "XArchFrameLowering.h"
#include "XArchISelLowering.h"
#include "XArchInstrInfo.h"
#include "XArchSelectionDAGInfo.h"
#include "XArchSubtarget.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class XArchTargetMachine : public LLVMTargetMachine {
  XArchSubtarget Subtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  XArchTargetMachine(const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
                     const TargetOptions &Options, Optional<Reloc::Model> RM,
                     CodeModel::Model CM, CodeGenOpt::Level OL);

  const XArchSubtarget * getSubtargetImpl() const {
    return &Subtarget;
  }

  virtual const TargetSubtargetInfo *
  getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

} // end namespace llvm
