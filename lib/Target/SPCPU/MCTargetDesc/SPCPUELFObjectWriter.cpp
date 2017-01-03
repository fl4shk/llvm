//===-- SPCPUELFObjectWriter.cpp - SPCPU ELF Writer ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/SPCPUMCTargetDesc.h"
#include "MCTargetDesc/SPCPUFixupKinds.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  class SPCPUELFObjectWriter : public MCELFObjectTargetWriter {
  public:
    SPCPUELFObjectWriter(uint8_t OSABI);

    virtual ~SPCPUELFObjectWriter();

    unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                      const MCFixup &Fixup, bool IsPCRel) const override;
  };
}

unsigned SPCPUELFObjectWriter::getRelocType(MCContext &Ctx, const MCValue &Target,
                                            const MCFixup &Fixup, bool IsPCRel) const {

  unsigned Type = 0;
  switch ((unsigned)Fixup.getKind()) {
  default:
    llvm_unreachable("Unimplemented");
  }
  return Type;
}

SPCPUELFObjectWriter::SPCPUELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(/*Is64Bit*/ true, OSABI, /*ELF::EM_SPCPU*/ ELF::EM_ARM,
                              /*HasRelocationAddend*/ false) {}

SPCPUELFObjectWriter::~SPCPUELFObjectWriter() {}

MCObjectWriter *llvm::createSPCPUELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI) {
  MCELFObjectTargetWriter *MOTW = new SPCPUELFObjectWriter(OSABI);
  return createELFObjectWriter(MOTW, OS, /*IsLittleEndian=*/true);
}
