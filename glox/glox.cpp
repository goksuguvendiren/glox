//
// Created by Göksu Güvendiren on 8/14/21.
//

#include <string>
#include <iostream>
#include <fstream>

#include "glox.hpp"
#include "scanner.hpp"

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

}