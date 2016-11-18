//===-- XArchTargetMachine.cpp - Define TargetMachine for XArch -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "XArchTargetMachine.h"
#include "XArch.h"
#include "XArchFrameLowering.h"
#include "XArchInstrInfo.h"
#include "XArchISelLowering.h"
#include "XArchSelectionDAGInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options) {
  // XXX Build the triple from the arguments.
  // This is hard-coded for now for this example target.
  return "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i64:32-f64:32-a:0:32-n32";
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           Optional<Reloc::Model> RM) {
  // On ELF platforms the default static relocation model has a smart enough
  // linker to cope with referencing external symbols defined in a shared
  // library. Hence DynamicNoPIC doesn't need to be promoted to PIC.
  if (!RM.hasValue() || *RM == Reloc::DynamicNoPIC)
    return Reloc::Static;
  return *RM;
}


XArchTargetMachine::XArchTargetMachine(
    const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
    const TargetOptions &Options, Optional<Reloc::Model> RM,
    CodeModel::Model CM, CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options), TT, CPU, FS,
                        Options, getEffectiveRelocModel(TT, RM), CM, OL),
      Subtarget(TT, CPU, FS, *this),
      TLOF(make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

namespace {
/// XArch Code Generator Pass Configuration Options.
class XArchPassConfig : public TargetPassConfig {
public:
  XArchPassConfig(XArchTargetMachine *TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  XArchTargetMachine &getXArchTargetMachine() const {
    return getTM<XArchTargetMachine>();
  }

  virtual bool addPreISel() override;
  virtual bool addInstSelector() override;
  virtual void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *XArchTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new XArchPassConfig(this, PM);
}

bool XArchPassConfig::addPreISel() { return false; }

bool XArchPassConfig::addInstSelector() {
  addPass(createXArchISelDag(getXArchTargetMachine(), getOptLevel()));
  return false;
}

void XArchPassConfig::addPreEmitPass() {}

// Force static initialization.
extern "C" void LLVMInitializeXArchTarget() {
  RegisterTargetMachine<XArchTargetMachine> X(TheXArchTarget);
}
