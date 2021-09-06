//
// Created by Göksu Güvendiren on 8/17/21.
//

#pragma once

#include <any>

namespace glox::repr
{
class binary;
class unary;
class opr;
class numeric_literal;
class string_literal;
class grouping;
class variable;
class assignment;

class visitor
{
public:
    virtual std::any visit_binary_expr(const repr::binary& binary) const = 0;
    virtual std::any visit_opr_expr(const repr::opr& op) const = 0;
    virtual std::any visit_numeric_literal_expr(const repr::numeric_literal& op) const = 0;
    virtual std::any visit_unary_expr(const repr::unary& op) const = 0;
    virtual std::any visit_string_literal_expr(const repr::string_literal& op) const = 0;
    virtual std::any visit_grouping_expr(const repr::grouping& op) const = 0;
    virtual std::any visit_variable_expr(const repr::variable& op) const = 0;
    virtual std::any visit_assignment_expr(const repr::assignment& op) const = 0;
};

class expression
{
public:
    virtual std::any accept(const visitor& visitor) const = 0;
    virtual ~expression() = default;
};
}
