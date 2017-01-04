add_llvm_library(LLVMSPCPUDisassembler
  SPCPUDisassembler.cpp
  )

add_dependencies(LLVMSPCPUDisassembler SPCPUCommonTableGen)
