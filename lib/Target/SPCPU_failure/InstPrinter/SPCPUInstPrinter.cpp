//===-- SPCPUInstPrinter.cpp - Convert SPCPU MCInst to assembly syntax ----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints an SPCPU MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "SPCPUInstPrinter.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/CodeGen/ISDOpcodes.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define GET_INSTRUCTION_NAME
#include "SPCPUGenAsmWriter.inc"

SPCPUInstPrinter::SPCPUInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                 const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {
}

void SPCPUInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
  OS << StringRef(getRegisterName(RegNo)).lower();
}

void SPCPUInstPrinter::printInst(const MCInst *MI, raw_ostream &O,
                               StringRef Annot, const MCSubtargetInfo &STI) {
  printInstruction(MI, O);
  printAnnotation(O, Annot);
}

static void printExpr(const MCExpr *Expr, raw_ostream &OS) {
  int Offset = 0;
  const MCSymbolRefExpr *SRE;

  if (const MCBinaryExpr *BE = dyn_cast<MCBinaryExpr>(Expr)) {
    SRE = dyn_cast<MCSymbolRefExpr>(BE->getLHS());
    const MCConstantExpr *CE = dyn_cast<MCConstantExpr>(BE->getRHS());
    assert(SRE && CE && "Binary expression must be sym+const.");
    Offset = CE->getValue();
  } else {
    SRE = dyn_cast<MCSymbolRefExpr>(Expr);
    assert(SRE && "Unexpected MCExpr type.");
  }
  const MCSymbolRefExpr::VariantKind Kind = SRE->getKind();
  assert(Kind == MCSymbolRefExpr::VK_None);

  OS << SRE->getSymbol();

  if (Offset) {
    if (Offset > 0) {
      OS << '+';
    }
    OS << Offset;
  }
}

// Print a 'memsrc' operand which is a (Register, Offset) pair.
void SPCPUInstPrinter::printAddrModeMemSrc(const MCInst *MI, unsigned OpNum,
                                         raw_ostream &O) {
  const MCOperand &Op1 = MI->getOperand(OpNum);
  const MCOperand &Op2 = MI->getOperand(OpNum + 1);
  O << "[";
  printRegName(O, Op1.getReg());

  unsigned Offset = Op2.getImm();
  if (Offset) {
    O << ", #" << Offset;
  }
  O << "]";
}

void SPCPUInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                  raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg()) {
    printRegName(O, Op.getReg());
    return;
  }

  if (Op.isImm()) {
    O << "#" << Op.getImm();
    return;
  }

  assert(Op.isExpr() && "unknown operand kind in printOperand");
  printExpr(Op.getExpr(), O);
}
