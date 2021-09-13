//
// Created by Göksu Güvendiren on 9/5/21.
//

//#include "tjs/tokens.hpp"
#include "doctest.h"
#include <optional>
#include <scanner.hpp>

namespace glox
{
TEST_CASE("Consume empty string, should return end of file")
{
    auto contents = "";

    lexer lex(contents);
    lex.tokenize();

    auto tok = lex.advance_token();

    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::ENOF);
}

TEST_CASE("Consume binary operation")
{
    auto contents = "4 + 2";

    lexer lex(contents);
    lex.tokenize();

    auto tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::NUMBER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::PLUS);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::NUMBER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::ENOF);
}

TEST_CASE("Lexer can parse variable declarations")
{
    auto contents = "var a = 3";

    lexer lex(contents);
    lex.tokenize();

    auto tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::VAR);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::IDENTIFIER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::EQUAL);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::NUMBER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::ENOF);
}

TEST_CASE("Lexer can parse a variable, read and print it")
{
    auto contents = "var a = 3; \n print a;";

    lexer lex(contents);
    lex.tokenize();

    auto tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::VAR);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::IDENTIFIER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::EQUAL);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::NUMBER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::SEMICOLON);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::PRINT);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::IDENTIFIER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::SEMICOLON);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::ENOF);
}

TEST_CASE("Can reassign a new value to an existing variable!")
{
    auto contents = "var a = 3; a = 5;";

    lexer lex(contents);
    lex.tokenize();

    auto tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::VAR);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::IDENTIFIER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::EQUAL);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::NUMBER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::SEMICOLON);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::IDENTIFIER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::EQUAL);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::NUMBER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::SEMICOLON);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::ENOF);
}

TEST_CASE("Can define an empty scope!")
{
    auto contents = "{}";
    lexer lex(contents);
    REQUIRE_NOTHROW(lex.tokenize());

    auto tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::LEFT_BRACE);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::RIGHT_BRACE);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::ENOF);
}

TEST_CASE("Can define a trivial scope!")
{
    auto contents = "{ var a = 3; }";
    lexer lex(contents);
    REQUIRE_NOTHROW(lex.tokenize());

    auto tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::LEFT_BRACE);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::VAR);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::IDENTIFIER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::EQUAL);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::NUMBER);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::SEMICOLON);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::RIGHT_BRACE);

    tok = lex.advance_token();
    REQUIRE_EQ(tok.get_type(), glox::scanner::token_type::ENOF);
}
}