#include <iostream>
#include <vector>
#include <representer/numeric_literal.hpp>
#include "tools/code_generator.hpp"
#include "glox/representer/expression.hpp"
#include "glox/representer/opr.hpp"
#include "glox/representer/binary.hpp"
#include "glox/token.hpp"
#include "glox/glox.hpp"

#include "tools/printer.hpp"

void debug_printer()
{
    auto literal_1 = std::make_unique<glox::repr::numeric_literal>(3);
    auto literal_2 = std::make_unique<glox::repr::numeric_literal>(5);
    auto oper8or   = std::make_unique<glox::repr::opr>(std::make_unique<glox::scanner::token>(glox::scanner::token_type::STAR, "*", 0));

    auto expr = std::make_unique<glox::repr::binary>(std::move(literal_1),
            std::move(oper8or),
            std::move(literal_2));

    glox::tools::printer printer;

//    std::cerr << printer.to_string(*expr) << '\n';
}

void auto_generate()
{
    std::vector<glox::code_generator::type_definition> types =
    {
//        {"binary", {"repr::expression", "repr::opr", "repr::expression"}},
//        {"opr", {"scanner::token"}},
//        {"unary", {"scanner::token", "repr::expression"}},
//        {"grouping", {"repr::expression"}},
//        {"string_literal", {"std::string"}},
//        {"numeric_literal", {"double"}},
        {"variable", {"scanner::token"}},
    };
    glox::code_generator::generate_ast("/Users/goksuguvendiren/CLionProjects/glox/glox/representer",types);

    std::vector<glox::code_generator::type_definition> statement_types =
    {
//        {"expression", {"repr::expression"}},
//        {"print", {"repr::expression"}},
        {"variable", {"scanner::token", "repr::expression"}}
    };

//    glox::code_generator::generate_ast("/Users/goksuguvendiren/CLionProjects/glox/glox/statements",statement_types);
}

int main(int argc, const char** argv)
{
    auto_generate();
    glox::glox my_lox;
    my_lox.main(argc, argv);

    debug_printer();

    return 0;
}
