cmake_minimum_required(VERSION 3.17)
project(glox)

set(CMAKE_CXX_STANDARD 20)

add_executable(glox main.cpp glox/glox.cpp glox/glox.hpp glox/scanner.cpp glox/scanner.hpp
        glox/token.cpp glox/token.hpp glox/error.cpp glox/error.hpp
        glox/representer/expression.hpp glox/representer/binary.hpp tools/code_generator.cpp
        tools/code_generator.hpp)