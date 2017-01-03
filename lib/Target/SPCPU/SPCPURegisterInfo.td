//===-- SPCPURegisterInfo.td - SPCPU Register defs ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the SPCPU register file
//===----------------------------------------------------------------------===//

class SPCPUReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "SPCPU";
}

// CPU registers
foreach Index = 0-31 in {
  def R#Index : SPCPUReg <Index, "R"#Index>;
}

def SP  : SPCPUReg<32, "sp">;
def LR  : SPCPUReg<33, "lr">;

def CPSR  : SPCPUReg<34, "cpsr">;

// Register classes.
//
def GRRegs : RegisterClass<"SPCPU", [i32], 32,
  // Return values and arguments
  (add (sequence "R%u", 0, 31), SP)>;

