#include <llvm-lib/callgraph.hpp>
#include <llvm-lib/defuse.hpp>

#include <fstream>
#include <iostream>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>

int main(int argc, char **argv) {
    /* setup args */
    llvm::cl::opt<std::string> output(
        "output",
        llvm::cl::desc("An ouput file. Default stdout"),
        llvm::cl::value_desc("filename"));
    llvm::cl::opt<std::string> input(
        "input",
        llvm::cl::desc("An input file"),
        llvm::cl::value_desc("filename"));
    llvm::cl::opt<bool> callgraph(
        "dot-callgraph", llvm::cl::desc("Boolean flag. Output call graph"));
    llvm::cl::opt<bool> defuse(
        "dot-def-use", llvm::cl::desc("Boolean flag. Output def-use graph"));
    llvm::cl::ParseCommandLineOptions(argc, argv);
    llvm::SMDiagnostic err;
    llvm::LLVMContext ctx;
    std::cout << input.getValue() << std::endl;
    auto ir_module = llvm::parseIRFile(input.getValue(), err, ctx);
    std::string result;
    if (callgraph.getValue()) {
        result = llvmgraph::build_callgraph(ir_module.get());
    } else if (defuse.getValue()) {
        result = llvmgraph::build_defuse_graph(ir_module.get());
    } else {
        std::cout << "invalid graph type to build\n";
        return 0;
    }
    if (result.empty()) {
        std::cout << "invalid input data\n";
        return 0;
    }
    if (output.getValue().empty()) {
        std::cout << result << std::endl;
    } else {
        std::ofstream file(output.getValue());
        file << result;
    }
    return 0;
}
