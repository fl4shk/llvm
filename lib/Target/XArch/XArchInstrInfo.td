//===-- XArchInstrInfo.td - Target Description for XArch ---*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file describes the XArch instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

include "XArchInstrFormats.td"
include "XArchOperators.td"

//===----------------------------------------------------------------------===//
// ALU Instructions
//===----------------------------------------------------------------------===//
multiclass BinOp<bits<4> opcode, string opstr, SDNode opnode> {
  def rr : ALUInst<opcode, (outs GRRegs:$dst),
                   (ins GRRegs:$src1, GRRegs:$src2),
                   !strconcat(opstr, " $dst, $src1, $src2"),
                   [(set i32:$dst, (opnode i32:$src1, i32:$src2))]> {
  }
}

defm ADD  : BinOp<0b0000, "add", add>;
//defm ADC  : BinOp<0b0001, "adc", adde>;
defm SUB  : BinOp<0b0010, "sub", sub>;
//defm SBC  : BinOp<0b0011, "sbc", sube>;
defm LSL  : BinOp<0b0100, "lsl", shl>;
defm LSR  : BinOp<0b0101, "lsr", srl>;
defm ASR  : BinOp<0b0110, "asr", sra>;
defm ROL  : BinOp<0b0111, "rol", rotl>;
defm ROR  : BinOp<0b1000, "ror", rotr>;
defm AND  : BinOp<0b1001, "and", and>;
defm ORR  : BinOp<0b1010, "orr", or>;
defm XOR  : BinOp<0b1011, "xor", xor>;

//===----------------------------------------------------------------------===//
// Mov Instructions
//===----------------------------------------------------------------------===//
def MOVrr  : ALUInst<0b1101, (outs GRRegs:$dst), (ins GRRegs:$src),
                     "mov $dst, $src",
                     [/* No pattern */]> {
}

//def MOVi32 : InstXArch<(outs GRRegs:$dst), (ins i32imm:$src), "",
//                     [(set i32:$dst, (movei32 imm:$src))]> {
//  let isPseudo = 1;
//}

//def MOVi16 : InstXArch<(outs GRRegs:$dst), 
//	(ins i16imm:$src), 
//	"mov $dst, $src",
//	[(set i32:$dst, (i32 (zext i16imm:$src)))]>
//{
//}
//def MOVi32 : InstXArch<(outs GRRegs:$dst), 
//	(ins i32imm:$src), 
//	"movi32 $dst, $src",
//	[(set i32:$dst, imm:$src)]>;

//def MOVi16 : InstXArch<(outs GRRegs:$dst), 
//	(ins i16imm:$src), 
//	"mov $dst, $src",
//	[(set i32:$dst, (i32 (zext imm:$src)))]>
//{
//}



def i16_imm : Operand<i32>, ImmLeaf<i32, [{ return (Imm & ~0xFFFF) == 0; }]>;
def MOVLOi16 : InstXArch<(outs GRRegs:$dst), (ins i32imm:$src), 
	"movilo $dst, $src",
	[(set i32:$dst, i16_imm:$src)]> {
	bits<7> dst;
	bits<16> src;
	
	// This is an ALU op
	let Inst{31-30} = 0b00;
	let Inst{29-26} = 0b1110;
	let Inst{25-19} = dst;
	let Inst{15-0} = src;
}

//def MOVHIi16 : InstXArch<(outs GRRegs:$dst), (ins i32imm:$src), 
//	"movihi $dst, $src",
//	[(set i32:$dst, i16_imm


//===----------------------------------------------------------------------===//
// Load/Store Instructions
//===----------------------------------------------------------------------===//

def LOAD32 : InstXArch<(outs GRRegs:$dst), (ins GRRegs:$src),
	"ldr $dst, [$src]",
	[(set i32:$dst, (load i32:$src))]>
{
	bits<7> dst;
	bits<7> src;
	
	let Inst{31-30} = 0b01;
	let Inst{29-26} = 0b0001;
	let Inst{20-14} = dst;
	let Inst{13-7} = src;
	let Inst{6-0} = 0b0000000;
	
}


def STORE32 : InstXArch<(outs), (ins GRRegs:$src, GRRegs:$dst),
	"str $src, [$dst]",
	[(store i32:$src, i32:$dst)]>
{
	bits<7> dst;
	bits<7> src;
	
	let Inst{31-30} = 0b01;
	let Inst{29-26} = 0b0000;
	let Inst{20-14} = dst;
	let Inst{13-7} = src;
	let Inst{6-0} = 0b0000000;
	
}


//===----------------------------------------------------------------------===//
// Pseudo Instructions
//===----------------------------------------------------------------------===//

let Defs = [SP], Uses = [SP] in {
def ADJCALLSTACKDOWN : XArchPseudoInst<(outs), (ins i32imm:$amt),
                                    "# ADJCALLSTACKDOWN $amt",
                                    [(XArchcallseq_start timm:$amt)]>;
def ADJCALLSTACKUP   : XArchPseudoInst<(outs), (ins i32imm:$amt1, i32imm:$amt2),
                                    "# ADJCALLSTACKUP $amt1",
                                    [(XArchcallseq_end timm:$amt1, timm:$amt2)]>;
}

//===----------------------------------------------------------------------===//
// Return Instructions
//===----------------------------------------------------------------------===//

let isTerminator = 1, isReturn = 1, isBarrier = 1, Uses = [LR] in {
  def RET : InstXArch<(outs), (ins variable_ops),
                    "ret",  [(XArchRetFlag)]> {
    let Inst{29-26} = 0b1111;

  }
}

//let isCall = 1, Defs = [LR] in 
//{
//	def CALL : InstXArch<(outs), (ins
//	
//	
//}

