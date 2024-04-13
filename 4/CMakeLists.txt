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
        src/visitor/codegen.cpp
        src/visitor/codegen.h
        src/ast/enums.h
        src/ast/expr.cpp
        src/ast/expr.h
        src/ast/prog.h
        src/ast/stmt.h
        src/ast/enums.cpp
        src/ast/prog.cpp
        src/ast/stmt.cpp
        src/SemanticException.h
        src/utils.h
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


################### Google Test ###################
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        ctest
        test.cpp
        ${SOURCES}
)
target_link_libraries(
        ctest
        GTest::gtest_main
        ${llvm_libs}
)

include(GoogleTest)
gtest_discover_tests(ctest)
