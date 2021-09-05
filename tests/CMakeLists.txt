enable_testing()

add_library(tests_main tests_main.cpp)
target_include_directories(tests_main PUBLIC .)

#build with: cmake .. -DCMAKE_CXX_FLAGS:STRING=-std=c++17

add_executable(lexer_tests lexer_tests.cpp)
target_link_libraries(lexer_tests PRIVATE gloxlib tests_main)
add_test(NAME lexer_tests COMMAND lexer_tests)

#add_executable(token_stream_tests token_stream_tests.cpp)
#target_link_libraries(token_stream_tests PRIVATE tjs tests_main)
#add_test(NAME token_stream_tests COMMAND token_stream_tests)
#
#add_executable(expression_parser_tests expression_parser_tests.cpp)
#target_link_libraries(expression_parser_tests PRIVATE tjs tests_main)
#add_test(NAME expression_parser_tests COMMAND expression_parser_tests)