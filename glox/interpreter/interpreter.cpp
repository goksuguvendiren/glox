//
// Created by Göksu Güvendiren on 8/29/21.
//

#include "interpreter.hpp"

#include "representer/binary.hpp"
#include "representer/opr.hpp"
#include "representer/numeric_literal.hpp"
#include "representer/string_literal.hpp"
#include "representer/unary.hpp"
#include "representer/grouping.hpp"

namespace glox::interpreter {

std::any interpreter::evaluate(const glox::repr::expression &expr) const {
    return std::any();
}

std::any interpreter::visit_numeric_literal_expr(const glox::repr::numeric_literal &numeric) const {
    // for numeric literals, return the double value.
    return numeric.get_expr0();
}

std::any interpreter::visit_binary_expr(const glox::repr::binary &binary) const {
    return std::any();
}

std::any interpreter::visit_opr_expr(const glox::repr::opr &op) const {
    return std::any();
}

std::any interpreter::visit_string_literal_expr(const glox::repr::string_literal &op) const {
    return std::any();
}

std::any interpreter::visit_unary_expr(const glox::repr::unary &op) const {
    return std::any();
}

std::any interpreter::visit_grouping_expr(const glox::repr::grouping &op) const
{
    return std::any();
}
}