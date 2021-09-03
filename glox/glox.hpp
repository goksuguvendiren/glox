//
// Created by Göksu Güvendiren Bakir on 8/14/21.
//

#pragma once

#include <any>
#include <unordered_map>
#include <typeindex>
#include <string>

namespace glox {

enum class value_type
{
    STRING,
    DOUBLE,
    BOOLEAN
};

std::string to_string(const value_type& value);
inline std::unordered_map<std::type_index, value_type> type_names =
{
    std::make_pair(std::type_index(typeid(double)), value_type::DOUBLE),
    std::make_pair(std::type_index(typeid(std::string)), value_type::STRING),
};

class glox {
public:
    int main(int argc, const char **argv);

    static value_type to_type(const std::any& value);

private:
    int runPrompt();
    int runFile(const std::string& filename);

    bool had_error = false;

    void error(int line, const std::string &message);
    void report(int line, const std::string& where, const std::string& message);
};
}