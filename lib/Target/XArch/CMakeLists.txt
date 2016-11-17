set(LLVM_TARGET_DEFINITIONS XArch.td)

tablegen(LLVM XArchGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM XArchGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM XArchGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM XArchGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM XArchGenCallingConv.inc -gen-callingconv)
tablegen(LLVM XArchGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM XArchGenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(XArchCommonTableGen)


add_llvm_target(XArchCodeGen
  XArchSubtarget.cpp
  XArchTargetMachine.cpp
  XArchRegisterInfo.cpp
  XArchInstrInfo.cpp
  XArchFrameLowering.cpp
  XArchISelLowering.cpp
  XArchSelectionDAGInfo.cpp
  XArchISelDAGToDAG.cpp
  XArchAsmPrinter.cpp
  XArchMCInstLower.cpp
  )

add_subdirectory(TargetInfo)
add_subdirectory(AsmParser)
add_subdirectory(Disassembler)
add_subdirectory(InstPrinter)
add_subdirectory(MCTargetDesc)
add_subdirectory(Utils)
