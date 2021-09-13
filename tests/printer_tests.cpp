//
// Created by Göksu Güvendiren on 9/12/21.
//

#include "doctest.h"
#include <scanner.hpp>
#include <iostream>
#include <parser/parser.hpp>

#include "statements/variable.hpp"
#include "statements/print.hpp"
#include "statements/statement.hpp"
#include "representer/numeric_literal.hpp"
#include "representer/variable.hpp"
#include "representer/assignment.hpp"

#include "../tools/printer.hpp"

namespace glox
{
static auto get_tokens(const std::string &contents)
{
    lexer lex(contents);
    auto tokens = lex.tokenize();

    return tokens;
}

TEST_CASE("Expects a ; at the end of expression")
{
    auto contents = "var a = 3;";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);
    auto statements = parser.parse();

    tools::printer printer;
    auto result = printer.to_string(statements[0].get());

    REQUIRE_EQ(result, "var a = 3.000000");
}


TEST_CASE("Expects a ; at the end of expression")
{
    auto contents = "var a = 3;\n"
                    "print a;";
    auto tokens = get_tokens(contents);

    parser::parser parser(tokens);
    auto statements = parser.parse();

    tools::printer printer;
    auto result = printer.to_string(statements[0].get());
    REQUIRE_EQ(result, "var a = 3.000000");

    // returns an expression
    result = printer.to_string(statements[1].get());
    REQUIRE_EQ(result, "PRINT a");
}

}