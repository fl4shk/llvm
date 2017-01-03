//===-- SPCPUTargetMachine.h - Define TargetMachine for SPCPU ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the SPCPU specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "SPCPU.h"
#include "SPCPUFrameLowering.h"
#include "SPCPUISelLowering.h"
#include "SPCPUInstrInfo.h"
#include "SPCPUSelectionDAGInfo.h"
#include "SPCPUSubtarget.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class SPCPUTargetMachine : public LLVMTargetMachine {
  SPCPUSubtarget Subtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  SPCPUTargetMachine(const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
                     const TargetOptions &Options, Optional<Reloc::Model> RM,
                     CodeModel::Model CM, CodeGenOpt::Level OL);

  const SPCPUSubtarget * getSubtargetImpl() const {
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
