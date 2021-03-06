//
// Created by Göksu Güvendiren on 8/14/21.
//

#pragma once

#include <string>
#include <map>

namespace glox::scanner
{
enum class token_type
{
    // Single character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens
    BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, ENOF,
};


std::string to_string(const token_type& token);
std::ostream& operator<<(std::ostream& os, const token_type& dt);

class token
{
public:
    token(token_type type, std::string lexeme, int line);

    [[nodiscard]] std::string get_lexeme() const { return lexeme; }
    [[nodiscard]] token_type get_type() const { return type; }
private:
    token_type type;
    std::string lexeme;
    int line;

    friend std::ostream& operator<<(std::ostream& os, const token& dt);
};

}
