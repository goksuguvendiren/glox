//
// Created by Göksu Güvendiren on 9/5/21.
//

//#include "tjs/tokens.hpp"
#include "doctest.h"
#include <optional>
#include <scanner.hpp>

namespace glox
{
static void test(const std::string& contents, const std::vector<glox::scanner::token_type>& expected_tokens)
{
    lexer lex(contents);
    REQUIRE_NOTHROW(lex.tokenize());

    for (const auto& token : expected_tokens)
    {
        auto tok = lex.advance_token();
        REQUIRE_EQ(tok.get_type(), token);
    }
}

TEST_CASE("Consume empty string, should return end of file")
{
    auto contents = "";
    test(contents, {glox::scanner::token_type::ENOF});
}

TEST_CASE("Consume binary operation")
{
    auto contents = "4 + 2";

    test(contents,
 {
         glox::scanner::token_type::NUMBER,
         glox::scanner::token_type::PLUS,
         glox::scanner::token_type::NUMBER,
         glox::scanner::token_type::ENOF,
    });
}

TEST_CASE("Lexer can parse variable declarations")
{
    auto contents = "var a = 3";

    using token_type = glox::scanner::token_type;
    std::vector<token_type> expected_tokens =
    {
        token_type::VAR,
        token_type::IDENTIFIER,
        token_type::EQUAL,
        token_type::NUMBER,
        token_type::ENOF
    };

    test(contents, expected_tokens);
}

TEST_CASE("Lexer can parse a variable, read and print it")
{
    auto contents = "var a = 3; \n print a;";

    using token_type = glox::scanner::token_type;
    std::vector<token_type> expected_tokens =
    {
        token_type::VAR,
        token_type::IDENTIFIER,
        token_type::EQUAL,
        token_type::NUMBER,
        token_type::SEMICOLON,
        token_type::PRINT,
        token_type::IDENTIFIER,
        token_type::SEMICOLON,
        token_type::ENOF
    };

    test(contents, expected_tokens);
}

TEST_CASE("Can reassign a new value to an existing variable!")
{
    auto contents = "var a = 3; a = 5;";

    using token_type = glox::scanner::token_type;
    std::vector<token_type> expected_tokens =
            {
                    token_type::VAR,
                    token_type::IDENTIFIER,
                    token_type::EQUAL,
                    token_type::NUMBER,
                    token_type::SEMICOLON,
                    token_type::IDENTIFIER,
                    token_type::EQUAL,
                    token_type::NUMBER,
                    token_type::SEMICOLON,
                    token_type::ENOF
            };

    test(contents, expected_tokens);
}

TEST_CASE("Can define an empty scope!")
{
    auto contents = "{}";

    using token_type = glox::scanner::token_type;
    std::vector<token_type> expected_tokens =
    {
        token_type::LEFT_BRACE,
        token_type::RIGHT_BRACE,
        token_type::ENOF
    };

    test(contents, expected_tokens);
}

TEST_CASE("Can define a trivial scope!")
{
    auto contents = "{ var a = 3; }";

    using token_type = glox::scanner::token_type;
    std::vector<token_type> expected_tokens =
    {
        token_type::LEFT_BRACE,
        token_type::VAR,
        token_type::IDENTIFIER,
        token_type::EQUAL,
        token_type::NUMBER,
        token_type::SEMICOLON,
        token_type::RIGHT_BRACE,
        token_type::ENOF
    };

    test(contents, expected_tokens);
}

TEST_CASE("Can lex an if statement")
{
    auto contents = "if (3) { print \"yes\"; }";

    using token_type = glox::scanner::token_type;
    std::vector<token_type> expected_tokens =
    {
        token_type::IF,
        token_type::LEFT_PAREN,
        token_type::NUMBER,
        token_type::RIGHT_PAREN,
        token_type::LEFT_BRACE,
        token_type::PRINT,
        token_type::STRING,
        token_type::SEMICOLON,
        token_type::RIGHT_BRACE,
        token_type::ENOF,
    };

    test(contents, expected_tokens);
}
}