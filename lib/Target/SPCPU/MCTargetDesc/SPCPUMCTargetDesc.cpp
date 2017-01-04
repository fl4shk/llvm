//===-- SPCPUMCTargetDesc.cpp - SPCPU Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides SPCPU specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "SPCPUMCTargetDesc.h"
#include "InstPrinter/SPCPUInstPrinter.h"
#include "SPCPUMCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "SPCPUGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "SPCPUGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "SPCPUGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createSPCPUMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitSPCPUMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createSPCPUMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitSPCPUMCRegisterInfo(X, SPCPU::LR);
  return X;
}

static MCSubtargetInfo *createSPCPUMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU,
                                                 StringRef FS) {
  return createSPCPUMCSubtargetInfoImpl(TT, CPU, FS);
}

static MCAsmInfo *createSPCPUMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT) {
  return new SPCPUMCAsmInfo(TT);
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
createSPCPUMCInstPrinter(const Triple &TT, unsigned SyntaxVariant,
                       const MCAsmInfo &MAI, const MCInstrInfo &MII,
                       const MCRegisterInfo &MRI) {
  return new SPCPUInstPrinter(MAI, MII, MRI);
}

// Force static initialization.
extern "C" void LLVMInitializeSPCPUTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfoFn X(TheSPCPUTarget, createSPCPUMCAsmInfo);

  // Register the MC codegen info.
  TargetRegistry::registerMCAdjustCodeGenOpts(TheSPCPUTarget, adjustCodeGenOpts);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheSPCPUTarget, createSPCPUMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheSPCPUTarget, createSPCPUMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheSPCPUTarget,
                                          createSPCPUMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheSPCPUTarget, createSPCPUMCInstPrinter);

  // Register the ASM Backend.
  TargetRegistry::RegisterMCAsmBackend(TheSPCPUTarget, createSPCPUAsmBackend);

  // Register the MCCodeEmitter
  TargetRegistry::RegisterMCCodeEmitter(TheSPCPUTarget, createSPCPUMCCodeEmitter);
}
