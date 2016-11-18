//===-- XArchMCTargetDesc.h - XArch Target Descriptions ---------*- C++ -*-===//
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

#pragma once
#include "llvm/Support/DataTypes.h"

namespace llvm {
class Target;
class MCInstrInfo;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCContext;
class MCCodeEmitter;
class MCAsmInfo;
class MCCodeGenInfo;
class MCInstPrinter;
class MCObjectWriter;
class MCTargetOptions;
class MCAsmBackend;

class StringRef;
class raw_ostream;
class raw_pwrite_stream;
class Triple;

extern Target TheXArchTarget;

MCCodeEmitter *createXArchMCCodeEmitter(const MCInstrInfo &MCII,
                                      const MCRegisterInfo &MRI,
                                      MCContext &Ctx);

MCAsmBackend *createXArchAsmBackend(const Target &T,
                                    const MCRegisterInfo &MRI,
                                    const Triple &TT, StringRef CPU,
                                    const MCTargetOptions &Options);

MCObjectWriter *createXArchELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI);

} // End llvm namespace

// Defines symbolic names for XArch registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "XArchGenRegisterInfo.inc"

// Defines symbolic names for the XArch instructions.
//
#define GET_INSTRINFO_ENUM
#include "XArchGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "XArchGenSubtargetInfo.inc"
