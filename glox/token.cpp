//
// Created by Göksu Güvendiren on 8/14/21.
//

#include "token.hpp"

#include <utility>
#include <iostream>

namespace glox::scanner
{
std::ostream &operator<<(std::ostream &os, const token &dt)
{
    os << dt.type << " (" << dt.lexeme << ")";
    return os;
}

token::token(token_type type, std::string lexeme, int line) :
    type(type), lexeme(std::move(lexeme)), line(line)
{}

std::ostream& operator<<(std::ostream &os, const token_type &token)
{
    os << to_string(token);
    return os;
}

std::string to_string(const token_type &token)
{
    switch (token) {
        case token_type::LEFT_PAREN:
            return "LEFT_PAREN";
        case token_type::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case token_type::LEFT_BRACE:
            return "LEFT_BRACE";
        case token_type::RIGHT_BRACE:
            return "RIGHT_BRACE";
        case token_type::COMMA:
            return "COMMA";
        case token_type::DOT:
            return "DOT";
        case token_type::MINUS:
            return "MINUS";
        case token_type::PLUS:
            return "PLUS";
        case token_type::SEMICOLON:
            return "SEMICOLON";
        case token_type::SLASH:
            return "SLASH";
        case token_type::STAR:
            return "STAR";

        case token_type::BANG:
            return "BANG";
        case token_type::BANG_EQUAL:
            return "BANG_EQUAL";
        case token_type::EQUAL:
            return "EQUAL";
        case token_type::EQUAL_EQUAL:
            return "EQUAL_EQUAL";
        case token_type::GREATER:
            return "GREATER";
        case token_type::GREATER_EQUAL:
            return "GREATER_EQUAL";
        case token_type::LESS:
            return "LESS";
        case token_type::LESS_EQUAL:
            return "LESS_EQUAL";

        case token_type::IDENTIFIER:
            return "IDENTIFIER";
        case token_type::STRING:
            return "STRING";
        case token_type::NUMBER:
            return "NUMBER";

        case token_type::AND:
            return "AND";
        case token_type::CLASS:
            return "CLASS";
        case token_type::ELSE:
            return "ELSE";
        case token_type::FALSE:
            return "FALSE";
        case token_type::FUN:
            return "FUN";
        case token_type::FOR:
            return "FOR";
        case token_type::IF:
            return "IF";
        case token_type::NIL:
            return "NIL";
        case token_type::OR:
            return "OR";
        case token_type::PRINT:
            return "PRINT";
        case token_type::RETURN:
            return "RETURN";
        case token_type::SUPER:
            return "SUPER";
        case token_type::THIS:
            return "THIS";
        case token_type::TRUE:
            return "TRUE";
        case token_type::VAR:
            return "VAR";
        case token_type::WHILE:
            return "WHILE";
        case token_type::ENOF:
            return "ENOF";

        default:
            std::cerr << "No such token_type exists!!!\n";
            assert(false);
    }
}
}