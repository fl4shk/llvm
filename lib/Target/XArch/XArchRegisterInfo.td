//===-- XArchRegisterInfo.td - XArch Register defs ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the XArch register file
//===----------------------------------------------------------------------===//

class XArchReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "XArch";
}

// CPU registers
foreach Index = 0-31 in {
  def R#Index : XArchReg <Index, "R"#Index>;
}

def SP  : XArchReg<32, "sp">;
def LR  : XArchReg<33, "lr">;

def CPSR  : XArchReg<34, "cpsr">;

// Register classes.
//
def GRRegs : RegisterClass<"XArch", [i32], 32,
  // Return values and arguments
  (add (sequence "R%u", 0, 31), SP)>;

