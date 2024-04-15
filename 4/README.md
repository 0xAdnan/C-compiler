# cc
C compiler

To compile:
1. `mkdir build && cd build`
2. `cmake ..`

To generate the AST:
`./cc examples/test1.c`

TODO:
1. ~~goTo~~
2. for statements
3. Arrays handle
4. Constant Propagation
5. DeadCode Removal
6. Pointer Handle - Adnan
7. Address handling
~~8. Different Assignment Handle - Adnan~~
9. Create Test for If and while statements
10. Ternary Condition handle
11. 



Compile LLVM IR to Executable
1. `llc -relocation-model=pic output.ll -filetype=obj -o output.o`
2. `clang -pie output.o -o output`
3. `./output`

