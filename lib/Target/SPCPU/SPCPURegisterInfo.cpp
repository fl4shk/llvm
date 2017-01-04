//===-- SPCPURegisterInfo.cpp - SPCPU Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the SPCPU implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "SPCPURegisterInfo.h"
#include "SPCPU.h"
#include "SPCPUFrameLowering.h"
#include "SPCPUInstrInfo.h"
#include "SPCPUMachineFunctionInfo.h"
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
#include "SPCPUGenRegisterInfo.inc"

using namespace llvm;

SPCPURegisterInfo::SPCPURegisterInfo() : SPCPUGenRegisterInfo(SPCPU::lr) {}

const uint16_t *
SPCPURegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const uint16_t CalleeSavedRegs[] 
	= { SPCPU::r4p, SPCPU::r6p, SPCPU::r8p,
		SPCPU::lr, 0 };
  return CalleeSavedRegs;
}

BitVector SPCPURegisterInfo::getReservedRegs(const MachineFunction &MF) 
const
{
  BitVector Reserved(getNumRegs());

  Reserved.set(SPCPU::sp);
  Reserved.set(SPCPU::pc);
  return Reserved;
}

const uint32_t *SPCPURegisterInfo::getCallPreservedMask
	(const MachineFunction &MF, CallingConv::ID) const
{
	return 0;
}

bool
SPCPURegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
SPCPURegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

bool SPCPURegisterInfo::useFPForScavengingIndex(const MachineFunction &MF) const {
  return false;
}

void SPCPURegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
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
  FIOp.ChangeToRegister(SPCPU::sp, false);
  ImmOp.setImm(Offset);
}

unsigned SPCPURegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return SPCPU::sp;
}
