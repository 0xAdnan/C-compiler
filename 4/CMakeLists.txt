cmake_minimum_required(VERSION 3.0)
project(CCompiler)

find_package(LLVM REQUIRED CONFIG)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/ast)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/visitor)


##################### FLEX-BISON ####################
FLEX_TARGET(Lexer c.l ${CMAKE_CURRENT_BINARY_DIR}/c.lex.cpp)
BISON_TARGET(Parser c.y ${CMAKE_CURRENT_BINARY_DIR}/c.tab.cpp COMPILE_FLAGS --debug DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/c.tab.hpp)
add_flex_bison_dependency(Lexer Parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(SOURCES ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS}
        src/ast/base.cpp
        src/ast/base.h
        src/ast/decl.cpp
        src/ast/decl.h
        src/visitor/visitor.h
        src/visitor/codegen.h
        src/visitor/decl_codegen.cpp
        src/visitor/expr_codegen.cpp
        src/visitor/stmt_codegen.cpp
        src/ast/enums.h
        src/ast/expr.cpp
        src/ast/expr.h
        src/ast/prog.h
        src/ast/stmt.h
        src/ast/enums.cpp
        src/ast/prog.cpp
        src/ast/stmt.cpp
        src/visitor/printer.h
        src/visitor/algebra_simplification_opt.cpp
        src/visitor/algebra_simplification_opt.h
        src/visitor/const_prop_opt.cpp
        src/visitor/const_prop_opt.h
        src/visitor/dead_code_opt.cpp
        src/visitor/dead_code_opt.h
        src/visitor/opt_utils.h
)
add_executable(cc cc.cpp ${SOURCES})


####################### LLVM #########################
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(cc ${llvm_libs})


##################### BOOST #########################
find_package(Boost COMPONENTS program_options REQUIRED)
target_include_directories( cc PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries( cc ${Boost_LIBRARIES} )
