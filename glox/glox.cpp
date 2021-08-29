//
// Created by Göksu Güvendiren on 8/14/21.
//

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <typeindex>
#include <any>

#include "glox.hpp"
#include "scanner.hpp"
#include "parser/parser.hpp"
#include "interpreter/interpreter.hpp"

#include "../tools/printer.hpp"

namespace glox
{
int glox::main(int argc, const char **argv)
{
    if (argc == 1)
    {
        return runPrompt();
    }

    auto filename = std::string(argv[1]);
    // The rest is the possible args that can be passed to the program, may be implemented later.

    runFile(filename);
    return 0;
}

int glox::runPrompt()
{
    std::cout << "Running the glox online interpreter!\n";

    std::string line;
    std::cout << ">> ";
    while(std::getline(std::cin, line))
    {
        std::cout << line << '\n';
        std::cout << ">> ";

        lexer lexer(line);
        auto tokens = lexer.tokenize();

//        for (auto& token : tokens) std::cerr << token << '\n';
        if (had_error) return 1;

        parser::parser parser(tokens);
        auto expr = parser.parse();

        tools::printer printer;
        std::cout << printer.to_string(*expr) << '\n';

        interpreter::interpreter interpreter;
        auto value = interpreter.evaluate(*expr);
        auto type = to_value(value);

        std::cerr << std::type_index(typeid(double)).name() << '\n';
        std::cerr << std::type_index(value.type()).name() << '\n';

        std::cerr << "Type of the statement is: " << to_string(type) << '\n';
        std::cerr << "The value of the statement is: " << std::any_cast<const double&>(value) << '\n';

//        std::cerr << "The evaluated value is: " << std::any_cast<int>(value) << '\n';

        // set the error to false so that we don't exit the interactive program on
        // a wrong command
        had_error = false;
    }

    return 0;
}

int glox::runFile(const std::string& filename)
{
    std::cout << "Processing and executing the file: " << filename << '\n';

    std::ifstream in(filename);
    std::string contents((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());

    std::cout << contents.c_str() << '\n';

    lexer lexer(contents);
    auto tokens = lexer.tokenize();

    for (auto& token : tokens)
    {
        std::cout << token << '\n';
    }

    if (had_error) return 1;

    parser::parser parser(tokens);
    auto expr = parser.parse();

    tools::printer printer;
    std::cerr << printer.to_string(*expr) << '\n';

    return 0;
}

void glox::error(int line, const std::string &message)
{
    report(line, "", message);
}

void glox::report(int line, const std::string &where, const std::string &message)
{
    std::cout << "Error happened in line: " << line << '\n';
    std::cout << "Message is: " << message << '\n';

    had_error = true;
}

value_type glox::to_value(const std::any &value) const
{
    std::unordered_map<std::type_index, value_type> type_names;

    type_names[std::type_index(typeid(double))] = value_type::DOUBLE;
    type_names[std::type_index(typeid(std::string))] = value_type::STRING;

    return type_names[std::type_index(typeid(value))];
}

std::string to_string(const value_type &value)
{
    switch (value)
    {
        case value_type::DOUBLE:
            return "double";
        case value_type::STRING:
            return "std::string";
        default:
            std::cerr << "No such value_type exists!!!\n";
            assert(false);
    }
}
}