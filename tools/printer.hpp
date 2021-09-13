//
// Created by Göksu Güvendiren on 8/22/21.
//

#pragma once

#include <string>
#include "statements/statement.hpp"
#include "representer/expression.hpp"

namespace glox::tools
{
class printer : repr::visitor, stmt::stmt_visitor
{
public:
    std::string to_string(const repr::expression* expr) const
    {
        return std::any_cast<std::string>(expr->accept(*this));
    }

    std::string to_string(const stmt::statement* expr) const
    {
        return std::any_cast<std::string>(expr->accept(*this));
    }

private:
    std::any visit_binary_expr(const repr::binary* binary) const override;
    std::any visit_opr_expr(const repr::opr* op) const override;
    std::any visit_numeric_literal_expr(const repr::numeric_literal* op) const override;
    std::any visit_string_literal_expr(const repr::string_literal* op) const override;
    std::any visit_unary_expr(const repr::unary* op) const override;
    std::any visit_grouping_expr(const repr::grouping* op) const override;
    std::any visit_variable_expr(const repr::variable* op) const override;
    std::any visit_assignment_expr(const repr::assignment* op) const override;

    std::any visit_print_statement(const stmt::print* st) const override;
    std::any visit_expression_statement(const stmt::expression* st) const override;
    std::any visit_variable_statement(const stmt::variable* st) const override;
    std::any visit_block_statement(const stmt::block* st) const override;

};
}