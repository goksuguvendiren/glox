//
// Created by Göksu Güvendiren on 8/14/21.
//

#include <iostream>
#include "scanner.hpp"
#include "token.hpp"
#include "glox.hpp"
#include "error.hpp"

namespace glox
{
std::vector<scanner::token> lexer::tokenize()
{
    while (!finished())
    {
        start = current;
        scan_token();
    }

    tokens.emplace_back(scanner::token_type::ENOF, "", line);

    return tokens;
}

lexer::lexer(std::string buf) : buffer(std::move(buf))
{
    current = 0;
    line = 1;
}

bool lexer::check_single_tokens(char c)
{
    switch (c)
    {
        case '(': add_token(scanner::token_type::LEFT_PAREN); break;
        case ')': add_token(scanner::token_type::RIGHT_PAREN); break;
        case '{': add_token(scanner::token_type::LEFT_BRACE); break;
        case '}': add_token(scanner::token_type::RIGHT_BRACE); break;
        case ',': add_token(scanner::token_type::COMMA); break;
        case '.': add_token(scanner::token_type::DOT); break;
        case '-': add_token(scanner::token_type::MINUS); break;
        case '+': add_token(scanner::token_type::PLUS); break;
        case ';': add_token(scanner::token_type::SEMICOLON); break;
        case '/': add_token(scanner::token_type::SLASH); break;
        case '*': add_token(scanner::token_type::STAR); break;
        default:
            return false;
    }

    return true;
}

void lexer::scan_token()
{
    auto c = advance();
    auto res = check_single_tokens(c);

    if (res)
    {
        std::cout << "Found a single character token!\n";
    }
    else
    {
        err(line, "An unexpected character was given!");
    }
}

char lexer::advance()
{
    return buffer[current++];
}

bool lexer::finished()
{
    return current >= buffer.size();
}

void lexer::add_token(scanner::token_type type)
{
    auto count = current - start;
    auto literal = buffer.substr(start, current);
    add_token(scanner::token{type, literal, line});
}

void lexer::add_token(const scanner::token& token)
{
    tokens.emplace_back(token);
}
}