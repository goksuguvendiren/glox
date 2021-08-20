#include <iostream>
#include <vector>
#include "glox/glox.hpp"
#include "tools/code_generator.hpp"

int main(int argc, const char** argv)
{
//    glox::glox my_lox;
//    my_lox.main(argc, argv);

    std::vector<glox::code_generator::type_definition> types =
    {
        {"binary", {"glox::repr::expression", "glox::repr::opr", "glox::repr::expression"}},
        {"opr", {"glox::scanner::token"}}
    };

    glox::code_generator::generate_ast("/Users/goksuguvendiren/CLionProjects/glox/glox/representer",
                                       "binary", types);

}
