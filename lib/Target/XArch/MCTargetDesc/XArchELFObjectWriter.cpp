//===-- XArchELFObjectWriter.cpp - XArch ELF Writer ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/XArchMCTargetDesc.h"
#include "MCTargetDesc/XArchFixupKinds.h"
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
  class XArchELFObjectWriter : public MCELFObjectTargetWriter {
  public:
    XArchELFObjectWriter(uint8_t OSABI);

    virtual ~XArchELFObjectWriter();

    unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                      const MCFixup &Fixup, bool IsPCRel) const override;
  };
}

unsigned XArchELFObjectWriter::getRelocType(MCContext &Ctx, const MCValue &Target,
                                            const MCFixup &Fixup, bool IsPCRel) const {

  unsigned Type = 0;
  switch ((unsigned)Fixup.getKind()) {
  default:
    llvm_unreachable("Unimplemented");
  }
  return Type;
}

XArchELFObjectWriter::XArchELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(/*Is64Bit*/ true, OSABI, /*ELF::EM_XArch*/ ELF::EM_ARM,
                              /*HasRelocationAddend*/ false) {}

XArchELFObjectWriter::~XArchELFObjectWriter() {}

MCObjectWriter *llvm::createXArchELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI) {
  MCELFObjectTargetWriter *MOTW = new XArchELFObjectWriter(OSABI);
  return createELFObjectWriter(MOTW, OS, /*IsLittleEndian=*/true);
}
