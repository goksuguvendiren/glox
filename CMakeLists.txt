cmake_minimum_required(VERSION 3.17)
project(glox)

set(CMAKE_CXX_STANDARD 20)

include_directories(glox)

add_executable(glox main.cpp glox/glox.cpp glox/glox.hpp glox/scanner.cpp glox/scanner.hpp
        glox/token.cpp glox/token.hpp glox/error.cpp glox/error.hpp
        glox/representer/expression.hpp glox/representer/binary.hpp tools/code_generator.cpp
        tools/code_generator.hpp tools/printer.cpp tools/printer.hpp glox/representer/grouping.hpp glox/representer/unary.hpp glox/representer/string_literal.hpp glox/representer/numeric_literal.hpp glox/parser/parser.hpp glox/parser/parser.cpp glox/interpreter/interpreter.cpp glox/interpreter/interpreter.hpp glox/statements/statement.hpp)