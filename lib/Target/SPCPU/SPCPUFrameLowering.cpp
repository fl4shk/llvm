//===-- SPCPUFrameLowering.cpp - Frame info for SPCPU Target --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains SPCPU frame information that doesn't fit anywhere else
// cleanly...
//
//===----------------------------------------------------------------------===//

#include "SPCPUFrameLowering.h"
#include "SPCPU.h"
#include "SPCPUInstrInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetLowering.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/MathExtras.h"
#include <algorithm> // std::sort

using namespace llvm;

//===----------------------------------------------------------------------===//
// SPCPUFrameLowering:
//===----------------------------------------------------------------------===//
SPCPUFrameLowering::SPCPUFrameLowering()
    : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 4, 0) {
  // Do nothing
}

bool SPCPUFrameLowering::hasFP(const MachineFunction &MF) const {
  return MF.getTarget().Options.DisableFramePointerElim(MF) ||
         MF.getFrameInfo().hasVarSizedObjects();
}

uint64_t SPCPUFrameLowering::computeStackSize(MachineFunction &MF) const {
  MachineFrameInfo &MFI = MF.getFrameInfo();
  uint64_t StackSize = MFI.getStackSize();
  unsigned StackAlign = getStackAlignment();
  if (StackAlign > 0) {
    StackSize = alignTo(StackSize, StackAlign);
  }
  return StackSize;
}

void SPCPUFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
  // XXX:
}

void SPCPUFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
  // XXX:
}

// This function eliminates ADJCALLSTACKDOWN, ADJCALLSTACKUP pseudo
// instructions
MachineBasicBlock::iterator SPCPUFrameLowering::eliminateCallFramePseudoInstr(
    MachineFunction &MF, MachineBasicBlock &MBB,
    MachineBasicBlock::iterator I) const {
  //if (I->getOpcode() == SPCPU::ADJCALLSTACKUP ||
  //    I->getOpcode() == SPCPU::ADJCALLSTACKDOWN) {
  //  return MBB.erase(I);
  //}
  //else
  //  llvm_unreachable("Couldn't reach here");
  return I;
}
