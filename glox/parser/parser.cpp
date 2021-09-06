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
#include <representer/assignment.hpp>
#include <error.hpp>

#include "token.hpp"
#include "parser/parser.hpp"
#include "representer/expression.hpp"
#include "representer/binary.hpp"
#include "representer/unary.hpp"
#include "representer/numeric_literal.hpp"
#include "representer/variable.hpp"

#include "statements/statement.hpp"
#include "statements/print.hpp"
#include "statements/expression.hpp"
#include "statements/variable.hpp"

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

/*
 * Parse the expressions
 */

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

    if (match(scanner::token_type::IDENTIFIER))
    {
        return std::make_unique<repr::variable>(std::make_unique<scanner::token>(previous()));
    }

    return nullptr;
}

std::unique_ptr<repr::expression> parser::unary()
{
    // this matches a binary operator, read a binary!
    while(match({glox::scanner::token_type::BANG, glox::scanner::token_type::MINUS}))
    {
        auto curr_operator = std::make_unique<repr::opr>(std::make_unique<scanner::token>(previous()));
        auto right_operand = unary();

        return std::make_unique<glox::repr::unary>(std::move(curr_operator), std::move(right_operand));
    }

    return primary();
}

std::unique_ptr<repr::expression> parser::factor()
{
    auto left_operand = unary();

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
    auto left_operand = factor();

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
    auto left_term = term();

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
    auto left_operand = comparison();

    // this matches a binary operator, read a binary!
    while(match({glox::scanner::token_type::BANG_EQUAL, glox::scanner::token_type::EQUAL_EQUAL}))
    {
        auto curr_operator = std::make_unique<repr::opr>(std::make_unique<scanner::token>(previous()));
        auto right_operand = comparison();

        left_operand = std::make_unique<glox::repr::binary>(std::move(left_operand), std::move(curr_operator), std::move(right_operand));
    }

    return left_operand;
}

std::unique_ptr<glox::repr::expression> parser::assignment()
{
    auto left_operand = equality();

    // this matches an assignment expression, read an assignment!
    if(match(glox::scanner::token_type::EQUAL))
    {
        auto token = previous();
        auto right_operand = assignment(); // a = b = c = 3; should be parsable

        auto variable = dynamic_cast<repr::variable*>(left_operand.get());

        if (variable)
        {
            // correct, keep on lexing
            auto name = variable->get_expr0();
            return std::make_unique<glox::repr::assignment>(std::make_unique<scanner::token>(name), std::move(right_operand));
        }
        else
        {
            throw err(0, "Invalid assignment!!");
        }
    }

    return left_operand;
}

std::unique_ptr<glox::repr::expression> parser::expression()
{
    return assignment();
}

/*
 * Parse the statements
 */

std::unique_ptr<glox::stmt::statement> parser::expression_statement()
{
    auto val = expression(); // parse the next token after `print`
    consume(scanner::token_type::SEMICOLON, "Expected ';' after expression!!");

    return std::make_unique<stmt::expression>(std::move(val));
}

std::unique_ptr<glox::stmt::statement> parser::print_statement()
{
    auto val = expression(); // parse the next token after `print`
    consume(scanner::token_type::SEMICOLON, "Expected ';' after expression!!");

    return std::make_unique<stmt::print>(std::move(val));
}

std::unique_ptr<glox::stmt::statement> parser::statement()
{
    if (match(scanner::token_type::PRINT))
        return print_statement();

    return expression_statement();
}

std::unique_ptr<stmt::statement> parser::variable_declaration()
{
    auto variable_name = consume(scanner::token_type::IDENTIFIER, "Variable declarations should have a name!");

    std::unique_ptr<repr::expression> value = nullptr;
    if (match(scanner::token_type::EQUAL))
    {
        value = expression();
    }

    consume(scanner::token_type::SEMICOLON, "Expected ';' variable declaration!!");
    return std::make_unique<stmt::variable>(std::make_unique<scanner::token>(variable_name), std::move(value));
}

std::unique_ptr<stmt::statement> parser::declaration()
{
    if (match(scanner::token_type::VAR))
        return variable_declaration();

    return statement();
}

std::vector<std::unique_ptr<stmt::statement>> parser::parse()
{
    std::vector<std::unique_ptr<stmt::statement>> statements;
    try
    {
        while(!finished() && peek().get_type() != scanner::token_type::ENOF)
        {
            auto expr = declaration();
            statements.push_back(std::move(expr));
        }
    }
    catch (const std::runtime_error& exception)
    {
        std::cerr << exception.what() << '\n';
        throw exception;
    }

    return statements;
}

/*
 * The helper functions:
 */
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
    if (peek().get_type() == tok) return advance();

    throw std::runtime_error(error_message);
}
}