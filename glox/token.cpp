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
    std::string name;
    switch (token) {
        case token_type::LEFT_PAREN:
            name = "LEFT_PAREN"; break;
        case token_type::RIGHT_PAREN:
            name = "RIGHT_PAREN"; break;
        case token_type::LEFT_BRACE:
            name = "LEFT_BRACE"; break;
        case token_type::RIGHT_BRACE:
            name = "RIGHT_BRACE"; break;
        case token_type::COMMA:
            name = "COMMA"; break;
        case token_type::DOT:
            name = "DOT"; break;
        case token_type::MINUS:
            name = "MINUS"; break;
        case token_type::PLUS:
            name = "PLUS"; break;
        case token_type::SEMICOLON:
            name = "SEMICOLON"; break;
        case token_type::SLASH:
            name = "SLASH"; break;
        case token_type::STAR:
            name = "STAR"; break;

        case token_type::BANG:
            name = "BANG"; break;
        case token_type::BANG_EQUAL:
            name = "BANG_EQUAL"; break;
        case token_type::EQUAL:
            name = "EQUAL"; break;
        case token_type::EQUAL_EQUAL:
            name = "EQUAL_EQUAL"; break;
        case token_type::GREATER:
            name = "GREATER"; break;
        case token_type::GREATER_EQUAL:
            name = "GREATER_EQUAL"; break;
        case token_type::LESS:
            name = "LESS"; break;
        case token_type::LESS_EQUAL:
            name = "LESS_EQUAL"; break;

        case token_type::IDENTIFIER:
            name = "IDENTIFIER"; break;
        case token_type::STRING:
            name = "STRING"; break;
        case token_type::NUMBER:
            name = "NUMBER"; break;

        case token_type::AND:
            name = "AND"; break;
        case token_type::CLASS:
            name = "CLASS"; break;
        case token_type::ELSE:
            name = "ELSE"; break;
        case token_type::FALSE:
            name = "FALSE"; break;
        case token_type::FUN:
            name = "FUN"; break;
        case token_type::FOR:
            name = "FOR"; break;
        case token_type::IF:
            name = "IF"; break;
        case token_type::NIL:
            name = "NIL"; break;
        case token_type::OR:
            name = "OR"; break;
        case token_type::PRINT:
            name = "PRINT"; break;
        case token_type::RETURN:
            name = "RETURN"; break;
        case token_type::SUPER:
            name = "SUPER"; break;
        case token_type::THIS:
            name = "THIS"; break;
        case token_type::TRUE:
            name = "TRUE"; break;
        case token_type::VAR:
            name = "VAR"; break;
        case token_type::WHILE:
            name = "WHILE"; break;
        case token_type::ENOF:
            name = "ENOF"; break;

        default:
            std::cerr << "No such token_type exists!!!\n";
    }

    os << name;
    return os;
}
}