//
// Created by Göksu Güvendiren on 8/22/21.
//

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <representer/opr.hpp>
#include <representer/string_literal.hpp>
#include <representer/grouping.hpp>

#include "token.hpp"
#include "parser/parser.hpp"
#include "representer/expression.hpp"
#include "representer/binary.hpp"
#include "representer/unary.hpp"
#include "representer/numeric_literal.hpp"

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

parser::parser(const std::vector<scanner::token> &tokens) : buffer(tokens) {}

std::unique_ptr<repr::expression> parser::primary()
{
    if (match(scanner::token_type::FALSE)) return std::make_unique<repr::numeric_literal>(0);
    if (match(scanner::token_type::TRUE)) return std::make_unique<repr::numeric_literal>(1);
    if (match(scanner::token_type::NIL)) return nullptr;

    if (match(scanner::token_type::NUMBER))
    {
        return std::make_unique<repr::numeric_literal>(std::atof(previous().get_lexeme().c_str()));
    }

    if (match(scanner::token_type::STRING))
    {
        return std::make_unique<repr::string_literal>(std::make_unique<std::string>(previous().get_lexeme()));
    }

    if (match(scanner::token_type::LEFT_PAREN))
    {
        auto rest = expression();
        consume(scanner::token_type::RIGHT_PAREN, "Expected ')' after expression!!");

        return std::make_unique<repr::grouping>(std::move(rest));
    }

    throw std::runtime_error("Expected expression!");
}

std::unique_ptr<repr::expression> parser::unary()
{
    // this matches a binary operator, read a binary!
    while(match({glox::scanner::token_type::BANG, glox::scanner::token_type::MINUS}))
    {
        std::cout << "Matched a BANG or a MINUS\n";
        auto curr_operator = std::make_unique<scanner::token>(previous());
        auto right_operand = unary();

        return std::make_unique<glox::repr::unary>(std::move(curr_operator), std::move(right_operand));
    }

    return primary();
}

std::unique_ptr<repr::expression> parser::factor()
{
    std::unique_ptr<glox::repr::expression> left_operand = unary();

    // this matches a binary operator, read a binary!
    while(match({glox::scanner::token_type::SLASH, glox::scanner::token_type::STAR}))
    {
        auto curr_operator = std::make_unique<repr::opr>(std::make_unique<scanner::token>(previous()));
        auto right_operand = unary();

        left_operand = std::make_unique<glox::repr::binary>(std::move(left_operand), std::move(curr_operator), std::move(right_operand));
    }

    return left_operand;
}

std::unique_ptr<repr::expression> parser::term()
{
    std::unique_ptr<glox::repr::expression> left_operand = factor();

    // this matches a binary operator, read a binary!
    while(match({glox::scanner::token_type::PLUS, glox::scanner::token_type::MINUS}))
    {
        auto curr_operator = std::make_unique<repr::opr>(std::make_unique<scanner::token>(previous()));
        auto right_operand = factor();

        left_operand = std::make_unique<glox::repr::binary>(std::move(left_operand), std::move(curr_operator), std::move(right_operand));
    }

    return left_operand;
}

std::unique_ptr<glox::repr::expression> parser::comparison()
{
    std::unique_ptr<glox::repr::expression> left_term = term();

    // this matches a binary operator, read a binary!
    while(match({glox::scanner::token_type::GREATER, glox::scanner::token_type::GREATER_EQUAL,
                     glox::scanner::token_type::LESS, glox::scanner::token_type::LESS_EQUAL}))
    {
        auto curr_operator = std::make_unique<repr::opr>(std::make_unique<scanner::token>(previous()));
        auto right_term = term();

        left_term = std::make_unique<glox::repr::binary>(std::move(left_term), std::move(curr_operator), std::move(right_term));
    }

    return left_term;
}

std::unique_ptr<glox::repr::expression> parser::equality()
{
    std::unique_ptr<glox::repr::expression> left_operand = comparison();

    // this matches a binary operator, read a binary!
    while(match({glox::scanner::token_type::BANG_EQUAL, glox::scanner::token_type::EQUAL_EQUAL}))
    {
        auto curr_operator = std::make_unique<repr::opr>(std::make_unique<scanner::token>(previous()));
        auto right_operand = comparison();

        left_operand = std::make_unique<glox::repr::binary>(std::move(left_operand), std::move(curr_operator), std::move(right_operand));
    }

    return left_operand;
}

std::unique_ptr<glox::repr::expression> parser::expression()
{
    return equality();
}

bool parser::finished(int offset)
{
    return current + offset >= buffer.size();
}

bool parser::match(scanner::token_type tok)
{
    return match(std::vector<scanner::token_type>{tok});
}

bool parser::match(std::vector<scanner::token_type> toks)
{
    if (finished()) return false;

    auto current_token = buffer[current].get_type();
    if (std::any_of(toks.begin(), toks.end(), [current_token](const scanner::token_type& tok){
        return tok == current_token;
    }))
    {
        current++;
        return true;
    }

    return false;
}

scanner::token parser::peek(int offset)
{
    if (finished(offset)) return scanner::token(scanner::token_type::ENOF, "", 0);
    return buffer[current + offset];
}

scanner::token parser::advance()
{
    return buffer[current++];
}

scanner::token parser::previous()
{
    assert(current > 0 && "The current value cannot be zero (or negative, ofc) in parser::previous() call!");
    return buffer[current - 1];
}

scanner::token parser::consume(scanner::token_type tok, const std::string& error_message)
{
    if (match(tok)) return advance();

    throw std::runtime_error(error_message);
}

std::unique_ptr<repr::expression> parser::parse()
{
    try
    {
        return expression();
    }
    catch (const std::runtime_error& expression)
    {
        std::cerr << expression.what() << '\n';
        return nullptr;
    }
}

}