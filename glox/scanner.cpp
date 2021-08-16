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

bool lexer::check_double_tokens(char c)
{
    using scanner::token_type;
    switch (c)
    {
        case '!': add_token(match('=') ? token_type::BANG_EQUAL : token_type::BANG); break;
        case '=': add_token(match('=') ? token_type::EQUAL_EQUAL : token_type::EQUAL); break;
        case '>': add_token(match('=') ? token_type::GREATER_EQUAL : token_type::GREATER); break;
        case '<': add_token(match('=') ? token_type::LESS_EQUAL : token_type::LESS); break;
        default:
            return false;
    }

    return true;
}

bool lexer::check_more_tokens(char c)
{
    using scanner::token_type;
    switch (c)
    {
        case '/':
        {
            if (match('/')) // then that's a comment, go until the end of the line
            {
                while(peek() != '\n' && !finished()) advance();
            }
            else add_token(token_type::SLASH);
            break;
        }
    }
    return false;
}

bool lexer::check_whitespace_tokens(char c)
{
    switch (c)
    {
        case ' ':
        case '\t':
        case '\r':
            break;
        case '\n':
            line++;
            break;
        default:
            return false;
    }

    return true;
}

bool lexer::check_longer_tokens(char c)
{
    switch (c)
    {
        case '"': parse_string(); break;
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
        return;
    }

    res = check_double_tokens(c);
    if (res)
    {
        std::cout << "Found a double character token!\n";
        return;
    }

    res = check_more_tokens(c);
    if (res)
    {
        std::cout << "Found a one or more character token!\n";
        return;
    }

    res = check_whitespace_tokens(c);
    if (res)
    {
        std::cout << "Found a whitespace!\n";
        return;
    }

    res = check_longer_tokens(c);
    if (res)
    {
        std::cout << "Found longer tokens!\n";
        return;
    }


    if (!res)
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
    auto literal = buffer.substr(start, count);
    add_token(scanner::token{type, literal, line});
}

void lexer::add_token(const scanner::token& token)
{
    tokens.emplace_back(token);
}

bool lexer::match(char c)
{
    if (finished()) return false;
    if (buffer[current] != c) return false;

    current++;
    return true;
}

char lexer::peek()
{
    if (finished()) return '\0';
    return buffer[current];
}

void lexer::parse_string()
{
    while(peek() != '"' && !finished())
    {
        if (peek() == '\n') line++;
        advance();
    }

    if (finished()) err(line, "String not finished properly!!");

    advance(); // get rid of the next "

    add_token(scanner::token_type::STRING);
}

}