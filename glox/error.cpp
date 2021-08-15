//
// Created by Göksu Güvendiren on 8/14/21.
//

#include <iostream>
#include "error.hpp"

glox::err::err(int line, const std::string &message)
{
    report(line, message);
}

void glox::err::report(int line, const std::string &message)
{
    std::cout << "Error happened in line: " << line << '\n';
    std::cout << "Message is: " << message << '\n';


}
