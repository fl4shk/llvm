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


//class SPCPUReg<bits<16> Enc, string n> : Register<n> {
//  let HWEncoding = Enc;
//  let Namespace = "SPCPU";
//}
//
//// CPU registers
//foreach Index = 0-31 in {
//  def R#Index : SPCPUReg <Index, "R"#Index>;
//}
//
//def SP  : SPCPUReg<32, "sp">;
//def LR  : SPCPUReg<33, "lr">;
//
//def CPSR  : SPCPUReg<34, "cpsr">;
//
//// Register classes.
////
//def GRRegs : RegisterClass<"SPCPU", [i32], 32,
//  // Return values and arguments
//  (add (sequence "R%u", 0, 31), SP)>;

class SPCPURegPair< bits<4> enc, string n > : Register<n> 
//class SPCPURegPair< bits<4> enc, string n >
{
	let HWEncoding = { 0b00000000000, enc, 0b0 };
	//bits<4> the_enc = enc;
	bits<4> hi_half_enc = { enc{3-1}, 0b0 };
	bits<4> lo_half_enc = { enc{3-1}, 0b1 };
	let Namespace = "SPCPU";
	//string Namespace = "SPCPU";
	
	
	//let NAME = !strconcat( "r", !cast<string>(enc), "p" );
	//string NAME = !strconcat( "r", !cast<string>(enc), "p" );
	string name_hi = !strconcat( "r", !cast<string>({ enc{3-1}, 0b0 }) );
	string name_lo = !strconcat( "r", !cast<string>({ enc{3-1}, 0b1 }) );
}

foreach i = [ 0, 2, 4, 6, 8 ] in
{
	def r#i#p : SPCPURegPair< i, !strconcat( "r", !cast<string>(i), "p" ) >;
}
def sp : SPCPURegPair< 10, "sp" >;
def lr : SPCPURegPair< 12, "lr" >;
def pc : SPCPURegPair< 14, "pc" >;


def reg_pairs : RegisterClass< "SPCPU", [i16], 16,
	// Return values and arguments
	(add r0p, r2p, r4p, r6p, r8p, sp, lr, pc)>;
