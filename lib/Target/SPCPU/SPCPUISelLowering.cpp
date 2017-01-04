//===-- SPCPUISelLowering.cpp - SPCPU DAG Lowering Implementation ---------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the SPCPUTargetLowering class.
//
//===----------------------------------------------------------------------===//

#include "SPCPUISelLowering.h"
#include "SPCPU.h"
#include "SPCPUMachineFunctionInfo.h"
#include "SPCPUSubtarget.h"
#include "SPCPUTargetMachine.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalAlias.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

const char *SPCPUTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  default:
    return NULL;
  }
}

SPCPUTargetLowering::SPCPUTargetLowering(SPCPUTargetMachine &SPCPUTM)
    : TargetLowering(SPCPUTM), Subtarget(*SPCPUTM.getSubtargetImpl()) {
  // Set up the register classes.
  addRegisterClass(MVT::i32, &SPCPU::GRRegsRegClass);

  // Compute derived properties from the register classes
  computeRegisterProperties(Subtarget.getRegisterInfo());

  setStackPointerRegisterToSaveRestore(SPCPU::SP);

  setSchedulingPreference(Sched::Source);

  // Nodes that require custom lowering
  setOperationAction(ISD::GlobalAddress, MVT::i32, Custom);
}

SDValue SPCPUTargetLowering::LowerOperation(SDValue Op, SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  default:
    llvm_unreachable("Unimplemented operand");
  case ISD::GlobalAddress:
    return LowerGlobalAddress(Op, DAG);
  }
}

SDValue SPCPUTargetLowering::LowerGlobalAddress(SDValue Op, SelectionDAG& DAG) const
{
  EVT VT = Op.getValueType();
  GlobalAddressSDNode *GlobalAddr = cast<GlobalAddressSDNode>(Op.getNode());
  SDValue TargetAddr =
      DAG.getTargetGlobalAddress(GlobalAddr->getGlobal(), Op, MVT::i32);
  return DAG.getNode(SPCPUISD::LOAD_SYM, Op, VT, TargetAddr);
}

//===----------------------------------------------------------------------===//
//                      Calling Convention Implementation
//===----------------------------------------------------------------------===//

#include "SPCPUGenCallingConv.inc"

//===----------------------------------------------------------------------===//
//                  Call Calling Convention Implementation
//===----------------------------------------------------------------------===//

/// SPCPU call implementation
SDValue SPCPUTargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
                                     SmallVectorImpl<SDValue> &InVals) const {
  llvm_unreachable("Unimplemented");
}

SDValue SPCPUTargetLowering::LowerCallResult(
    SDValue Chain, SDValue InGlue, CallingConv::ID CallConv, bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, SDLoc dl, SelectionDAG &DAG,
    SmallVectorImpl<SDValue> &InVals) const {
  llvm_unreachable("Unimplemented");
}

//===----------------------------------------------------------------------===//
//             Formal Arguments Calling Convention Implementation
//===----------------------------------------------------------------------===//

/// SPCPU formal arguments implementation
SDValue SPCPUTargetLowering::LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                             bool isVarArg,
                             const SmallVectorImpl<ISD::InputArg> &Ins,
                             const SDLoc &DL, SelectionDAG &DAG,
                             SmallVectorImpl<SDValue> &InVals) const {
  llvm_unreachable("Unimplemented");
}

//===----------------------------------------------------------------------===//
//               Return Value Calling Convention Implementation
//===----------------------------------------------------------------------===//

bool SPCPUTargetLowering::CanLowerReturn(
    CallingConv::ID CallConv, MachineFunction &MF, bool isVarArg,
    const SmallVectorImpl<ISD::OutputArg> &Outs, LLVMContext &Context) const {
  llvm_unreachable("Unimplemented");
}

SDValue SPCPUTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                    const SmallVectorImpl<ISD::OutputArg> &Outs,
                    const SmallVectorImpl<SDValue> &OutVals, const SDLoc &DL,
                    SelectionDAG &DAG) const {
  llvm_unreachable("Unimplemented");
}
