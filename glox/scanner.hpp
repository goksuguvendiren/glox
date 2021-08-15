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

    void add_token(scanner::token_type type);
    void add_token(const scanner::token& token);

    char advance();
    bool finished();

    int current;
    int start;
    int line;
};
}
