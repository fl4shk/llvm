//===- SPCPUDisassembler.h - Disassembler for SPCPU ---------*- C++ -*-===//
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

#pragma once

#include "llvm/MC/MCDisassembler/MCDisassembler.h"

namespace llvm {

class MCInst;
class raw_ostream;

class SPCPUDisassembler : public MCDisassembler {
public:
  SPCPUDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
    : MCDisassembler(STI, Ctx) {}

  ~SPCPUDisassembler() {}

  MCDisassembler::DecodeStatus
  getInstruction(MCInst &Instr, uint64_t &Size, ArrayRef<uint8_t> Bytes,
                 uint64_t Address, raw_ostream &VStream,
                 raw_ostream &CStream) const override;
};

} // namespace llvm
