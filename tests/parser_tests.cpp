//
// Created by Göksu Güvendiren on 9/5/21.
//

#include "doctest.h"
#include <scanner.hpp>
#include <parser/parser.hpp>

#include "statements/variable.hpp"
#include "statements/print.hpp"
#include "representer/numeric_literal.hpp"
#include "representer/variable.hpp"
#include "representer/assignment.hpp"

namespace glox
{

static auto get_tokens(const std::string& contents)
{
    lexer lex(contents);
    auto tokens = lex.tokenize();

    return tokens;
}

TEST_CASE("Expects a ; at the end of expression")
{
    auto contents = "var a = 3";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);

    REQUIRE_THROWS_MESSAGE(parser.parse(), "Expected ';' variable declaration!!");
}

TEST_CASE("Can define a variable")
{
    auto contents = "var a = 3;";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);
    auto statements = parser.parse();

    // should have exactly 1 statement
    REQUIRE_EQ(statements.size(), 1);

    auto statement = dynamic_cast<stmt::variable*>(statements[0].get());
    REQUIRE_EQ(statement->get_expr0().get_lexeme(), "a");
    REQUIRE_EQ(dynamic_cast<const repr::numeric_literal&>(statement->get_expr1()), repr::numeric_literal(3.0));

    REQUIRE(statement[0].initialized());
}

TEST_CASE("Can define a variable without initializing it!")
{
    auto contents = "var a;";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);
    auto statements = parser.parse();

    // should have exactdly 1 statement
    REQUIRE_EQ(statements.size(), 1);

    auto statement = dynamic_cast<stmt::variable*>(statements[0].get());
    REQUIRE_EQ(statement->get_expr0().get_lexeme(), "a");

    REQUIRE_FALSE(statement[0].initialized());
}

TEST_CASE("Can parse a variable and a print statement!")
{
    auto contents = "var a = 3; print a;";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);
    auto statements = parser.parse();
    REQUIRE_EQ(statements.size(), 2);
}

TEST_CASE("Can define a variable without initializing it!")
{
    auto contents = "var a = 3; print a;";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);
    auto statements = parser.parse();

    // should have exactdly 1 statement
    REQUIRE_EQ(statements.size(), 2);

    auto var_statement = dynamic_cast<stmt::variable*>(statements[0].get());
    REQUIRE_EQ(var_statement->get_expr0().get_lexeme(), "a");

    REQUIRE(var_statement[0].initialized());

    // returns an expression
    auto print_statement = dynamic_cast<stmt::print*>(statements[1].get());

    // can cast the value to a numeric literal
    REQUIRE_NOTHROW(const auto& a = dynamic_cast<const repr::variable&>(print_statement->get_expr0()));
}

TEST_CASE("Can reassign a new value to an existing variable!")
{
    auto contents = "var a = 3; a = 5;";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);
    auto statements = parser.parse();

    // should have exactdly 1 statement
    REQUIRE_EQ(statements.size(), 2);

    // the first statement is a variable statement
    auto var_statement = dynamic_cast<stmt::variable*>(statements[0].get());
    REQUIRE_EQ(var_statement->get_expr0().get_lexeme(), "a");

    // the second statement is an expression statement, and the expression is a assignment expression
    auto assignment_stmt = dynamic_cast<stmt::expression*>(statements[1].get());
    auto assignment_expr = dynamic_cast<const repr::assignment*>(&(assignment_stmt->get_expr0()));
    REQUIRE_EQ(assignment_expr->get_expr0().get_lexeme(), "a");
    REQUIRE_EQ(assignment_expr->get_expr0().get_type(), scanner::token_type::IDENTIFIER);
}

TEST_CASE("Can define an empty scope!")
{
    auto contents = "{}";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);

    REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("Can define an empty scope!")
{
    auto contents = "{ var a = 3; }";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);

    REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("Testing the scope with multiple variables with the same name")
{
    auto contents = "var a = \"global a\";\n"
                    "var b = \"global b\";\n"
                    "var c = \"global c\";\n"
                    "{\n"
                    "  var a = \"outer a\";\n"
                    "  var b = \"outer b\";\n"
                    "  {\n"
                    "    var a = \"inner a\";\n"
                    "    print a;\n"
                    "    print b;\n"
                    "    print c;\n"
                    "  }\n"
                    "  print a;\n"
                    "  print b;\n"
                    "  print c;\n"
                    "}\n"
                    "print a;\n"
                    "print b;\n"
                    "print c;";

    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);
    REQUIRE_NOTHROW(parser.parse());
}

}