#include <iostream>
#include <vector>
#include <representer/numeric_literal.hpp>
#include "glox/glox.hpp"
#include "tools/code_generator.hpp"
#include "glox/representer/expression.hpp"
#include "glox/representer/opr.hpp"
#include "glox/representer/binary.hpp"
#include "glox/token.hpp"

#include "tools/printer.hpp"

void debug_printer()
{
    auto literal_1 = std::make_unique<glox::repr::numeric_literal>(3.);
    auto literal_2 = std::make_unique<glox::repr::numeric_literal>(5.);
    auto oper8or   = std::make_unique<glox::repr::opr>(std::make_unique<glox::scanner::token>(glox::scanner::token_type::STAR, "*", 0));

    auto expr = std::make_unique<glox::repr::binary>(std::move(literal_1),
            std::move(oper8or),
            std::move(literal_2));

    glox::tools::printer printer;

//    printer.to_string(expr);
}

int main(int argc, const char** argv)
{
//    glox::glox my_lox;
//    my_lox.main(argc, argv);

    std::vector<glox::code_generator::type_definition> types =
    {
        {"binary", {"repr::expression", "repr::opr", "repr::expression"}},
        {"opr", {"scanner::token"}},
        {"unary", {"scanner::token", "repr::expression"}},
        {"grouping", {"repr::expression"}},
        {"string_literal", {"std::string"}},
        {"numeric_literal", {"double"}},
    };

    glox::code_generator::generate_ast("/Users/goksuguvendiren/CLionProjects/glox/glox/representer",types);

    debug_printer();
}
