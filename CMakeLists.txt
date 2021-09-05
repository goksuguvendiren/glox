cmake_minimum_required(VERSION 3.17)
project(glox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(glox)

add_library(gloxlib glox/glox.cpp glox/scanner.cpp glox/token.cpp glox/error.cpp
            glox/parser/parser.cpp
            glox/interpreter/interpreter.cpp
            tools/code_generator.cpp tools/printer.cpp)

target_include_directories(gloxlib PUBLIC glox)
target_compile_features(gloxlib PUBLIC cxx_std_20)

add_executable(glox main.cpp)
target_link_libraries(glox PRIVATE gloxlib)

enable_testing()
add_subdirectory(tests)