//===- SPCPUCallingConv.td - Calling Conventions for SPCPU -*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for SPCPU architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// SPCPU Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_SPCPU : CallingConv<[
  //// i32 are returned in registers R0, R1, R2, R3
  //CCIfType<[i32], CCAssignToReg<[R0, R1, R2, R3]>>,
  //
  //// Integer values get stored in stack slots that are 4 bytes in
  //// size and 4-byte aligned.
  //CCIfType<[i32], CCAssignToStack<4, 4>>
  
  // The first 2 integer arguments are passed in integer reg pairs
  CCIfType<[i16], CCAssignToReg<[r0p, r2p]>>,
  
  // Integer values get stored in stack slots that are 2 bytes in
  // size and 2-byte aligned.
  CCIfType<[i16], CCAssignToStack<2, 2>>
]>;

//===----------------------------------------------------------------------===//
// SPCPU Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_SPCPU : CallingConv<[
  //// Promote i8/i16 arguments to i32.
  //CCIfType<[i8, i16], CCPromoteToType<i32>>,

  //// The first 4 integer arguments are passed in integer registers.
  //CCIfType<[i32], CCAssignToReg<[R0, R1, R2, R3]>>,
  //
  //
  //// Integer values get stored in stack slots that are 4 byte in
  //// size and 4-byte aligned.
  //CCIfType<[i32], CCAssignToStack<4, 4>>
  
  
  // Promote i8 arguments to i16.
  CCIfType<[i8], CCPromoteToType<i16>>,


  // The first 2 integer arguments are passed in integer reg pairs
  CCIfType<[i16], CCAssignToReg<[r0p, r2p]>>,
  
  
  // Integer values get stored in stack slots that are 2 bytes in
  // size and 2-byte aligned.
  CCIfType<[i16], CCAssignToStack<2, 2>>
]>;
