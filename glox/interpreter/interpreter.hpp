//
// Created by Göksu Güvendiren on 8/29/21.
//

#pragma once

#include <string>
#include <list>
#include "representer/expression.hpp"
#include "statements/environment.hpp"

namespace glox::interpreter
{

class interpreter : public repr::visitor, public stmt::stmt_visitor
{
public:
    interpreter();
    std::vector<std::any> interpret(const std::vector<std::unique_ptr<stmt::statement>>& statements) const;
    std::any execute(const stmt::statement* statement) const;
    std::any evaluate(const repr::expression* expr) const;

    static const stmt::environment* get_current_environment() { return current_environment; }
    static stmt::environment *current_environment;
    static std::list<std::unique_ptr<stmt::environment>> all_envs;

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