//
// Created by Göksu Güvendiren on 8/14/21.
//

#pragma once

#include <vector>
#include "token.hpp"

namespace glox
{
class lexer
{
public:
    explicit lexer(std::string buf);
    std::vector<scanner::token> tokenize();

private:
    std::string buffer;
    std::vector<scanner::token> tokens;

    void scan_token();
    bool check_single_tokens(char c);
    bool check_double_tokens(char c);
    bool check_more_tokens(char c);
    bool check_whitespace_tokens(char c);
    bool check_longer_tokens(char c);
    bool check_digit_token(char c);

    void parse_string();
    void parse_digit();

    void add_token(scanner::token_type type);
    void add_token(const scanner::token& token);

    bool match(char c);
    char peek(int offset = 0);
    char advance();
    bool finished(int offset = 0);

    int current;
    int start;
    int line;
};
}
