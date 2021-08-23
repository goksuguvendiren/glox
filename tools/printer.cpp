//
// Created by Göksu Güvendiren on 8/22/21.
//

#include "printer.hpp"
#include "representer/binary.hpp"
#include "representer/opr.hpp"
#include "representer/numeric_literal.hpp"

namespace glox::tools
{
std::any printer::visit_binary_expr(const repr::binary& binary) const
{
    const auto& oprtr = binary.get_expr1();
    const auto& operator_token = oprtr.get_expr0();

    std::string result;
    result += "( ";
    result += to_string(binary.get_expr1());
    result += " ";

    result += to_string(binary.get_expr0());
    result += " ";

    result += to_string(binary.get_expr2());
    result += " ";

    result += ")";

    return result;
}

std::any printer::visit_opr_expr(const repr::opr &op) const
{
    return op.get_expr0().get_lexeme();
}

std::any printer::visit_numeric_literal_expr(const repr::numeric_literal &op) const
{
    return std::to_string(op.get_expr0());
}

}