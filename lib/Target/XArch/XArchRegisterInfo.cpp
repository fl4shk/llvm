//===-- XArchRegisterInfo.cpp - XArch Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the XArch implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "XArchRegisterInfo.h"
#include "XArch.h"
#include "XArchFrameLowering.h"
#include "XArchInstrInfo.h"
#include "XArchMachineFunctionInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#define GET_REGINFO_TARGET_DESC
#include "XArchGenRegisterInfo.inc"

using namespace llvm;

XArchRegisterInfo::XArchRegisterInfo() : XArchGenRegisterInfo(XArch::LR) {}

const uint16_t *
XArchRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const uint16_t CalleeSavedRegs[] = { XArch::R4, XArch::R5, XArch::R6,
                                              XArch::R7, XArch::R8, XArch::R9,
                                              0 };
  return CalleeSavedRegs;
}

BitVector XArchRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  Reserved.set(XArch::SP);
  Reserved.set(XArch::LR);
  return Reserved;
}

const uint32_t *XArchRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                                      CallingConv::ID) const {
  return 0;
}

bool
XArchRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
XArchRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

bool XArchRegisterInfo::useFPForScavengingIndex(const MachineFunction &MF) const {
  return false;
}

void XArchRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  MachineInstr &MI = *II;
  const MachineFunction &MF = *MI.getParent()->getParent();
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  MachineOperand &FIOp = MI.getOperand(FIOperandNum);
  unsigned FI = FIOp.getIndex();

  // Determine if we can eliminate the index from this kind of instruction.
  unsigned ImmOpIdx = 0;
  switch (MI.getOpcode()) {
  default:
    // Not supported yet.
    return;
  }

  // FIXME: check the size of offset.
  MachineOperand &ImmOp = MI.getOperand(ImmOpIdx);
  int Offset = MFI.getObjectOffset(FI) + MFI.getStackSize() + ImmOp.getImm();
  FIOp.ChangeToRegister(XArch::SP, false);
  ImmOp.setImm(Offset);
}

unsigned XArchRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return XArch::SP;
}
