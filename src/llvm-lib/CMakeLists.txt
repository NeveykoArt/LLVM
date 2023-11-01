set(target_name llvm)

add_library(${target_name} STATIC
  llvm-lib/callgraph.cpp
  llvm-lib/defuse.cpp
  llvm-lib/callgraph.hpp
  llvm-lib/defuse.hpp)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

llvm_map_components_to_libnames(llvm_libs support core irreader analysis)
