//
// Created by Göksu Güvendiren on 8/22/21.
//

#pragma once

#include <string>
#include "representer/expression.hpp"

namespace glox::tools
{
class printer : repr::visitor
{
public:
    std::string to_string(const repr::expression& expr) const
    {
        return std::any_cast<std::string>(expr.accept(*this));
    }

private:
    std::any visit_binary_expr(const repr::binary& binary) const;
    std::any visit_opr_expr(const repr::opr& op) const;
    std::any visit_numeric_literal_expr(const repr::numeric_literal& op) const;
    std::any visit_string_literal_expr(const repr::string_literal& op) const;
    std::any visit_unary_expr(const repr::unary& op) const;
    std::any visit_grouping_expr(const repr::grouping& op) const;

};
}
