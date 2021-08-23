//
// Created by Göksu Güvendiren on 8/22/21.
//

#include "printer.hpp"

namespace glox::tools
{
std::string to_string_with_paranthesis()
{

}

std::any printer::visit_binary_expr(const repr::binary& binary) const
{

}

std::any printer::visit_opr_expr(const repr::opr &op) const
{
    return std::string();
}

std::any printer::visit_numeric_literal_expr(const repr::numeric_literal &op) const
{
    return std::string();
}

}