//===-- XArchSubtarget.cpp - XArch Subtarget Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the XArch specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "XArchSubtarget.h"
#include "XArch.h"
#include "llvm/Support/TargetRegistry.h"

#define DEBUG_TYPE "leg-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "XArchGenSubtargetInfo.inc"

using namespace llvm;

void XArchSubtarget::anchor() {}

XArchSubtarget::XArchSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                           XArchTargetMachine &TM)
    : XArchGenSubtargetInfo(TT, CPU, FS),
      DL("e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i64:32-f64:32-a:0:32-n32"),
      InstrInfo(), TLInfo(TM), TSInfo(), FrameLowering() {}
