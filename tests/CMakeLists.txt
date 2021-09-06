enable_testing()

add_library(tests_main tests_main.cpp)
target_include_directories(tests_main PUBLIC .)

#build with: cmake .. -DCMAKE_CXX_FLAGS:STRING=-std=c++17

add_executable(lexer_tests lexer_tests.cpp)
target_link_libraries(lexer_tests PRIVATE gloxlib tests_main)
add_test(NAME lexer_tests COMMAND lexer_tests)

add_executable(parser_tests parser_tests.cpp)
target_link_libraries(parser_tests PRIVATE gloxlib tests_main)
add_test(NAME parser_tests COMMAND parser_tests)

add_executable(interpreter_tests interpreter_tests.cpp)
target_link_libraries(interpreter_tests gloxlib tests_main)
add_test(NAME interpreter_tests COMMAND interpreter_tests)