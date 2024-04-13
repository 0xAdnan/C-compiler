# cc
C compiler

To compile:
1. `mkdir build && cd build`
2. `cmake ..`

To generate the AST:
`./cc examples/test1.c`

TODO:
1. Add pointer support
2. Add const support
3. Code generation



Compile LLVM IR to Executable
1. `llc -relocation-model=pic output.ll -filetype=obj -o output.o`
2. `clang -pie output.o -o output`
3. `./output`