//===- XArchDisassembler.cpp - Disassembler for XArch -------*- C++ -*-===//
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

#include "XArchDisassembler.h"
#include "XArchSubtarget.h"
#include "llvm/MC/MCFixedLenDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "aarch64-disassembler"

// Pull DecodeStatus and its enum values into the global namespace.
typedef llvm::MCDisassembler::DecodeStatus DecodeStatus;

#include "XArchGenDisassemblerTables.inc"
#include "XArchGenInstrInfo.inc"

#define Success llvm::MCDisassembler::Success
#define Fail llvm::MCDisassembler::Fail
#define SoftFail llvm::MCDisassembler::SoftFail

DecodeStatus XArchDisassembler::getInstruction(MCInst &MI, uint64_t &Size,
                                                 ArrayRef<uint8_t> Bytes,
                                                 uint64_t Address,
                                                 raw_ostream &OS,
                                                 raw_ostream &CS) const {
  CommentStream = &CS;

  Size = 0;
  // We want to read exactly 4 bytes of data.
  if (Bytes.size() < 4)
    return Fail;
  Size = 4;

  // Encoded as a small-endian 32-bit word in the stream.
  uint32_t Insn =
      (Bytes[3] << 24) | (Bytes[2] << 16) | (Bytes[1] << 8) | (Bytes[0] << 0);

  // Calling the auto-generated decoder function.
  return decodeInstruction(DecoderTable32, MI, Insn, Address, this, STI);
}

static MCDisassembler *createXArchDisassembler(const Target &T,
                                               const MCSubtargetInfo &STI,
                                               MCContext &Ctx) {
  return new XArchDisassembler(STI, Ctx);
}

extern "C" void LLVMInitializeXArchDisassembler() {
  TargetRegistry::RegisterMCDisassembler(TheXArchTarget,
                                         createXArchDisassembler);
}
