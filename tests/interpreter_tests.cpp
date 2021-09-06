//
// Created by Göksu Güvendiren on 9/5/21.
//

#include "doctest.h"
#include <optional>
#include <scanner.hpp>
#include <parser/parser.hpp>
#include <interpreter/interpreter.hpp>

namespace glox
{

static auto get_statements(const std::string& contents)
{
    lexer lex(contents);
    auto tokens = lex.tokenize();

    parser::parser parser(tokens);
    auto statements = parser.parse();

    return statements;
}

TEST_CASE("Can define and interpret a variable!")
{
    auto contents = "var a = 3;";
    auto statements = get_statements(contents);
    interpreter::interpreter interpreter;
    auto results = interpreter.interpret(statements);

    REQUIRE_EQ(results.size(), 1);

    // should return zero
    REQUIRE_EQ(std::any_cast<int>(results[0]), 0);

    REQUIRE_EQ(interpreter::environment.size(), 1);
    REQUIRE_NOTHROW(interpreter::environment.read("a"));
    auto value_any = interpreter::environment.read("a");
    REQUIRE_NOTHROW(std::any_cast<double>(value_any));

    auto value = std::any_cast<double>(value_any);
    REQUIRE_EQ(value, 3.0);
}

TEST_CASE("Can define and interpret a variable!")
{
    auto contents = "var a = 3; print a;";
    auto statements = get_statements(contents);

    interpreter::interpreter interpreter;
    auto results = interpreter.interpret(statements);

    REQUIRE_EQ(results.size(), 2);

    // both should return zero
    REQUIRE_EQ(std::any_cast<int>(results[0]), 0);
    REQUIRE_EQ(std::any_cast<int>(results[1]), 0);

    REQUIRE_EQ(interpreter::environment.size(), 1);
    REQUIRE_NOTHROW(interpreter::environment.read("a"));
    auto value_any = interpreter::environment.read("a");
    REQUIRE_NOTHROW(std::any_cast<double>(value_any));

    auto value = std::any_cast<double>(value_any);
    REQUIRE_EQ(value, 3.0);
}

TEST_CASE("Can reassign a new value to an existing variable!")
{
    auto contents = "var a = 3; a = 5;";
    auto statements = get_statements(contents);

    interpreter::interpreter interpreter;
    auto results = interpreter.interpret(statements);

    REQUIRE_EQ(results.size(), 2);

    // both should return zero
    REQUIRE_EQ(std::any_cast<int>(results[0]), 0);
    REQUIRE_EQ(std::any_cast<int>(results[1]), 0);

    REQUIRE_EQ(interpreter::environment.size(), 1);

    REQUIRE_NOTHROW(interpreter::environment.read("a"));
    auto value_any = interpreter::environment.read("a");
    REQUIRE_NOTHROW(std::any_cast<double>(value_any));

    auto value = std::any_cast<double>(value_any);
    REQUIRE_EQ(value, 5.0);
}

TEST_CASE("Tries to assign to a variable that doesn't exist!")
{
    auto contents = "var a = 3; b = 5;";
    auto statements = get_statements(contents);

    interpreter::interpreter interpreter;
    REQUIRE_NOTHROW(interpreter.interpret(statements));

//    auto results = interpreter.interpret(statements);
//
//    REQUIRE_EQ(results.size(), 3);
//
//    // both should return zero
//    REQUIRE_EQ(std::any_cast<int>(results[0]), 0);
//    REQUIRE_EQ(std::any_cast<int>(results[1]), 0);
//
//    REQUIRE_EQ(interpreter::environment.size(), 1);
//    REQUIRE_NOTHROW(interpreter::environment.read("a"));
//    auto value_any = interpreter::environment.read("a");
//    REQUIRE_NOTHROW(std::any_cast<double>(value_any));
//
//    auto value = std::any_cast<double>(value_any);
//    REQUIRE_EQ(value, 3.0);
}

TEST_CASE("Can define a variable without initializing it!")
{
    auto contents = "var a = b = c = 3;";
//    auto tokens = get_tokens(contents);

//    parser::parser parser(tokens);
//    auto statements = parser.parse();
//
//    // should have exactdly 1 statement
//    REQUIRE_EQ(statements.size(), 2);
//
//    auto var_statement = dynamic_cast<stmt::variable*>(statements[0].get());
//    REQUIRE_EQ(var_statement->get_expr0().get_lexeme(), "a");
//
//    REQUIRE(var_statement[0].initialized());
//
//    // returns an expression
//    auto print_statement = dynamic_cast<stmt::print*>(statements[1].get());
//
//    // can cast the value to a numeric literal
//    REQUIRE_NOTHROW(const auto& a = dynamic_cast<const repr::variable&>(print_statement->get_expr0()));
}
}