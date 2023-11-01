----#Before configure

clang-13 -S -emit-llvm (filename).c

----#Configure

cmake --preset debug

cmake --preset release

----#Build

cmake --build --preset debug

cmake --build --preset release

./build/debug/bin/app --input examples/fib.ll --dot-def-use

./build/debug/bin/app --input examples/fib.ll --dot-callgraph
