//
// Created by Göksu Güvendiren Bakir on 8/14/21.
//

#pragma once

#include <any>

namespace glox {

enum class value_type
{
    DOUBLE,
    STRING
};

std::string to_string(const value_type& value);

class glox {
public:
    int main(int argc, const char **argv);

private:
    int runPrompt();
    int runFile(const std::string& filename);

    bool had_error = false;

    void error(int line, const std::string &message);
    void report(int line, const std::string& where, const std::string& message);

    value_type to_value(const std::any& value) const;
};
}