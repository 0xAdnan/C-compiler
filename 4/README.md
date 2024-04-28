# cc - A C compiler for COL728

#### Tested on:
1. `CMake v3.16.3`
2. `Boost v1.71.0`
3. `llvm-19 / llvm-17`

##### Build Instructions:
1. `mkdir build && cd build`
2. `cmake ..`
3. `make`

Compile from source to LLVM IR
1. `./cc --in input.c`            Run with default options no optimization, input file is "input.c"
3. `./cc --in input.c --all-opt`   Enable all optimizations, input file is "input.c"
3. `./cc --help` to see all options

Run LLVM IR:
1. `lli-17 input.c.ll`

##### Supported Constructs
1. Declaration: `int i; int i=0; int i=0, j;`
2. Binary/Unary/Assignment Expressions on int/float; Strict typing, can't add int and float.
3. Statements: `if, if else, while, for, goto`
4. Non-void Functions & Global variables

##### Optimizations Performed
1. Algebraic Simplification. `Adding 0, Multiplying 0/1...`
2. DeadCode Removal. `if(1) then remove else. if(0) then remove if. while(0) remove while.`
3. Constant Propagation.
 `Only supported propagation in the same block. x=1; y=x+1; => y=2`