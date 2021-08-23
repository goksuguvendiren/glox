//
// Created by Göksu Güvendiren on 8/22/21.
//

#pragma once

#include <vector>
#include "representer/expression.hpp"
#include "token.hpp"

namespace glox::parser
{

/*
 * expression     → equality ;
 * equality       → comparison ( ( "!=" | "==" ) comparison )* ;
 * comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
 * term           → factor ( ( "-" | "+" ) factor )* ;
 * factor         → unary ( ( "/" | "*" ) unary )* ;
 * unary          → ( "!" | "-" ) unary
 *                  | primary ;
 * primary        → NUMBER | STRING | "true" | "false" | "nil"
 *                  | "(" expression ")" ;
 */

class parser
{
public:
    explicit parser(const std::vector<scanner::token>& tokens);

    std::unique_ptr<repr::expression> parse();

private:
    std::vector<scanner::token> buffer;

    std::unique_ptr<repr::expression> primary();
    std::unique_ptr<repr::expression> unary();
    std::unique_ptr<repr::expression> factor();
    std::unique_ptr<repr::expression> term();
    std::unique_ptr<repr::expression> comparison();
    std::unique_ptr<repr::expression> equality();
    std::unique_ptr<repr::expression> expression();

    bool match(std::vector<scanner::token_type> tok);
    bool match(scanner::token_type tok);
    scanner::token peek(int offset = 0);

    // get the next token
    scanner::token advance();

    // get the previous token
    scanner::token previous();

    // consume until you see the token `tok`, repor error if you don't see it
    scanner::token consume(scanner::token_type tok, const std::string& error_message);

    bool finished(int offset = 0);

    int current = 0;
};
}