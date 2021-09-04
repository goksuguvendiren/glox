//
// Created by Göksu Güvendiren on 8/29/21.
//

#pragma once

#include <string>
#include "representer/expression.hpp"

namespace glox::interpreter
{
    class interpreter : public repr::visitor, public stmt::visitor
    {
    public:
        std::any interpret(const std::vector<std::unique_ptr<stmt::statement>>& statements) const;
        std::any execute(const std::unique_ptr<stmt::statement>& statement) const;
        std::any evaluate(const repr::expression& expr) const;
    private:
        std::any visit_binary_expr(const repr::binary& binary) const override;
        std::any visit_opr_expr(const repr::opr& op) const override;
        std::any visit_numeric_literal_expr(const repr::numeric_literal& op) const override;
        std::any visit_string_literal_expr(const repr::string_literal& op) const override;
        std::any visit_unary_expr(const repr::unary& op) const override;
        std::any visit_grouping_expr(const repr::grouping& op) const override;

        std::any visit_print_statement(const stmt::print& st) const override;
        std::any visit_expression_statement(const stmt::expression& st) const override;
    };
}
