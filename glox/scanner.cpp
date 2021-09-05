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
        default: return false;
    }

    return true;
}

bool lexer::check_digit_tokens(char c)
{
    if (isdigit(c))
    {
        parse_digit();
        return true;
    }

    return false;
}

bool lexer::check_identifier_tokens(char c)
{
    if (isalpha(c) || c == '_')
    {
        parse_identifier();
        return true;
    }
    return false;
}

void lexer::scan_token()
{
    start = current;

    auto c = advance();
    auto res = check_single_tokens(c);
    if (res) return;

    res = check_double_tokens(c);
    if (res) return;

    res = check_more_tokens(c);
    if (res) return;

    res = check_whitespace_tokens(c);
    if (res) return;

    res = check_longer_tokens(c);
    if (res) return;

    res = check_digit_tokens(c);
    if (res) return;

    res = check_identifier_tokens(c);
    if (res) return;
    else err(line, "An unexpected character was given!");
}

char lexer::advance()
{
    return buffer[current++];
}

bool lexer::finished(int offset)
{
    return current + offset >= buffer.size();
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

char lexer::peek(int offset)
{
    if (finished(offset)) return '\0';
    return buffer[current + offset];
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

void lexer::parse_digit()
{
    while(isdigit(peek()) && !finished()) advance();

    if (peek() == '.') {
        advance();

        auto next = peek();
        if (!isdigit(next))
        {
            err(line, "The floating point number should have a digit after the dot (.)");
            return;
        }

        while(isdigit(peek())) advance();
    }

    add_token(scanner::token_type::NUMBER);
}

auto get_identifier(const std::string& name)
{
    std::map<std::string, scanner::token_type> name_token_map =
    {
        {"and",    scanner::token_type::AND},
        {"class",  scanner::token_type::CLASS},
        {"else",   scanner::token_type::ELSE},
        {"false",  scanner::token_type::FALSE},
        {"fun",    scanner::token_type::FUN},
        {"for",    scanner::token_type::FOR},
        {"if",     scanner::token_type::IF},
        {"nil",    scanner::token_type::NIL},
        {"or",     scanner::token_type::OR},
        {"print",  scanner::token_type::PRINT},
        {"return", scanner::token_type::RETURN},
        {"super",  scanner::token_type::SUPER},
        {"this",   scanner::token_type::THIS},
        {"true",   scanner::token_type::TRUE},
        {"var",    scanner::token_type::VAR},
        {"while",  scanner::token_type::WHILE},
    };

    auto token = name_token_map.find(name);
    if (token == name_token_map.end())
    {
        return scanner::token_type::IDENTIFIER;
    }

    return token->second;
}

bool can_be_identifier(char c)
{
    return (isalpha(c) || c == '_');
}

void lexer::parse_identifier()
{
    while(!finished() && can_be_identifier(peek()))
    {
        advance();
    }

    auto lexeme = buffer.substr(start, current - start);
    auto identifier = get_identifier(lexeme);

    add_token(identifier);
}

scanner::token lexer::advance_token()
{
    if (current_token >= tokens.size()) throw err(0, "Overflows the tokens!");
    return tokens[current_token++];
}

}