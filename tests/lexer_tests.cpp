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
}