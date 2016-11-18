add_llvm_library(LLVMXArchDisassembler
  XArchDisassembler.cpp
  )

add_dependencies(LLVMXArchDisassembler XArchCommonTableGen)
