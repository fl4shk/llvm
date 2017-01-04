set(LLVM_TARGET_DEFINITIONS SPCPU.td)

tablegen(LLVM SPCPUGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SPCPUGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SPCPUGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM SPCPUGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM SPCPUGenCallingConv.inc -gen-callingconv)
tablegen(LLVM SPCPUGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM SPCPUGenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(SPCPUCommonTableGen)


add_llvm_target(SPCPUCodeGen
  SPCPUSubtarget.cpp
  SPCPUTargetMachine.cpp
  SPCPURegisterInfo.cpp
  SPCPUInstrInfo.cpp
  SPCPUFrameLowering.cpp
  SPCPUISelLowering.cpp
  SPCPUSelectionDAGInfo.cpp
  SPCPUISelDAGToDAG.cpp
  SPCPUAsmPrinter.cpp
  SPCPUMCInstLower.cpp
  )

add_subdirectory(TargetInfo)
add_subdirectory(AsmParser)
add_subdirectory(Disassembler)
add_subdirectory(InstPrinter)
add_subdirectory(MCTargetDesc)
add_subdirectory(Utils)
