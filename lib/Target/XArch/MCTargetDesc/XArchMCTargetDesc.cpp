//===-- XArchMCTargetDesc.cpp - XArch Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides XArch specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "XArchMCTargetDesc.h"
#include "InstPrinter/XArchInstPrinter.h"
#include "XArchMCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "XArchGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "XArchGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "XArchGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createXArchMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitXArchMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createXArchMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitXArchMCRegisterInfo(X, XArch::LR);
  return X;
}

static MCSubtargetInfo *createXArchMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU,
                                                 StringRef FS) {
  return createXArchMCSubtargetInfoImpl(TT, CPU, FS);
}

static MCAsmInfo *createXArchMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT) {
  return new XArchMCAsmInfo(TT);
}

static void adjustCodeGenOpts(const Triple &TT, Reloc::Model RM,
                              CodeModel::Model &CM) {
  assert(TT.isOSBinFormatELF() &&
         "Only expect ELF targets");

  if (CM == CodeModel::Default)
    CM = CodeModel::Small;
  else if (CM != CodeModel::Small)
    report_fatal_error(
        "Only small and large code models are allowed on AArch64");
}

static MCInstPrinter *
createXArchMCInstPrinter(const Triple &TT, unsigned SyntaxVariant,
                       const MCAsmInfo &MAI, const MCInstrInfo &MII,
                       const MCRegisterInfo &MRI) {
  return new XArchInstPrinter(MAI, MII, MRI);
}

// Force static initialization.
extern "C" void LLVMInitializeXArchTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfoFn X(TheXArchTarget, createXArchMCAsmInfo);

  // Register the MC codegen info.
  TargetRegistry::registerMCAdjustCodeGenOpts(TheXArchTarget, adjustCodeGenOpts);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheXArchTarget, createXArchMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheXArchTarget, createXArchMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheXArchTarget,
                                          createXArchMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheXArchTarget, createXArchMCInstPrinter);

  // Register the ASM Backend.
  TargetRegistry::RegisterMCAsmBackend(TheXArchTarget, createXArchAsmBackend);

  // Register the MCCodeEmitter
  TargetRegistry::RegisterMCCodeEmitter(TheXArchTarget, createXArchMCCodeEmitter);
}
