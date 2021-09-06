//
// Created by Göksu Güvendiren on 8/29/21.
//

#include <glox.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "interpreter.hpp"
#include "error.hpp"

#include "representer/binary.hpp"
#include "representer/opr.hpp"
#include "representer/numeric_literal.hpp"
#include "representer/string_literal.hpp"
#include "representer/unary.hpp"
#include "representer/grouping.hpp"
#include "representer/variable.hpp"
#include "representer/assignment.hpp"

#include "statements/print.hpp"
#include "statements/expression.hpp"
#include "statements/statement.hpp"
#include "statements/variable.hpp"

namespace glox::interpreter {

bool check_type(value_type type, const std::any& value, const std::string& message)
{
    auto type_of_value = glox::to_type(value);
    if (type_of_value == type) return true;

    throw err(0, message);
}

std::vector<std::any> interpreter::interpret(const std::vector<std::unique_ptr<stmt::statement>> &statements) const
{
    std::vector<std::any> results;
    try
    {
        for (const auto& statement : statements)
        {
            auto res = execute(statement);
            results.push_back(res);
        }
    }
    catch(const std::runtime_error& error)
    {
        throw err(0, error.what());
    }

    return results;
}

std::any interpreter::execute(const std::unique_ptr<stmt::statement>& statement) const
{
    return statement->accept(*this);
}

std::any interpreter::evaluate(const repr::expression &expr) const
{
    return expr.accept(*this);
}

std::any interpreter::visit_numeric_literal_expr(const repr::numeric_literal &numeric) const
{
    // for numeric literals, return the double value.
    check_type(value_type::DOUBLE, numeric.get_expr0(), "Numeric literal expects to get a double!");
    return numeric.get_expr0();
}

std::any interpreter::visit_binary_expr(const repr::binary &binary) const
{
    auto left_operand  = evaluate(binary.get_expr0());
    auto right_operand = evaluate(binary.get_expr2());

    const auto& oper8or = binary.get_expr1();

    switch (oper8or.get_expr0().get_type())
    {
        case scanner::token_type::MINUS:
            check_type(value_type::DOUBLE, left_operand, "Binary expressions expect to get a double as left operand!");
            check_type(value_type::DOUBLE, right_operand, "Binary expressions expect to get a double as right operand!");
            return std::any_cast<double>(left_operand) - std::any_cast<double>(right_operand);

        case scanner::token_type::SLASH:
            check_type(value_type::DOUBLE, left_operand, "Binary expressions expect to get a double as left operand!");
            check_type(value_type::DOUBLE, right_operand, "Binary expressions expect to get a double as right operand!");
            return std::any_cast<double>(left_operand) / std::any_cast<double>(right_operand);

        case scanner::token_type::STAR:
            check_type(value_type::DOUBLE, left_operand, "Binary expressions expect to get a double as left operand!");
            check_type(value_type::DOUBLE, right_operand, "Binary expressions expect to get a double as right operand!");
            return std::any_cast<double>(left_operand) * std::any_cast<double>(right_operand);

        case scanner::token_type::GREATER:
            check_type(value_type::DOUBLE, left_operand, "Binary expressions expect to get a double as left operand!");
            check_type(value_type::DOUBLE, right_operand, "Binary expressions expect to get a double as right operand!");
            return std::any_cast<double>(left_operand) > std::any_cast<double>(right_operand);

        case scanner::token_type::GREATER_EQUAL:
            check_type(value_type::DOUBLE, left_operand, "Binary expressions expect to get a double as left operand!");
            check_type(value_type::DOUBLE, right_operand, "Binary expressions expect to get a double as right operand!");
            return std::any_cast<double>(left_operand) >= std::any_cast<double>(right_operand);

        case scanner::token_type::LESS:
            check_type(value_type::DOUBLE, left_operand, "Binary expressions expect to get a double as left operand!");
            check_type(value_type::DOUBLE, right_operand, "Binary expressions expect to get a double as right operand!");
            return std::any_cast<double>(left_operand) < std::any_cast<double>(right_operand);

        case scanner::token_type::LESS_EQUAL:
            check_type(value_type::DOUBLE, left_operand, "Binary expressions expect to get a double as left operand!");
            check_type(value_type::DOUBLE, right_operand, "Binary expressions expect to get a double as right operand!");
            return std::any_cast<double>(left_operand) <= std::any_cast<double>(right_operand);

        case scanner::token_type::EQUAL_EQUAL:
            check_type(value_type::DOUBLE, left_operand, "Binary expressions expect to get a double as left operand!");
            check_type(value_type::DOUBLE, right_operand, "Binary expressions expect to get a double as right operand!");
            return std::any_cast<double>(left_operand) == std::any_cast<double>(right_operand);

        case scanner::token_type::PLUS:
        {
            if (glox::to_type(left_operand) == value_type::STRING)
            {
                check_type(value_type::STRING, left_operand, "Binary expressions expect to get a string as left operand!");
                check_type(value_type::STRING, right_operand, "Binary expressions expect to get a string as right operand!");
                return std::any_cast<std::string>(left_operand) + std::any_cast<std::string>(right_operand);
            }
            else if (glox::to_type(left_operand) == value_type::DOUBLE)
            {
                check_type(value_type::DOUBLE, left_operand, "Binary expressions expect to get a double as left operand!");
                check_type(value_type::DOUBLE, right_operand, "Binary expressions expect to get a double as right operand!");
                return std::any_cast<double>(left_operand) + std::any_cast<double>(right_operand);
            }
            else
                throw err(0, "Not a valid binary expression!");
        }
        default:
            throw err(0, "Not a valid binary expression!");
    }
}

std::any interpreter::visit_opr_expr(const repr::opr &op) const
{
    throw err(0, "Operator expressions don't have a `evaluate` support!");
}

std::any interpreter::visit_string_literal_expr(const repr::string_literal &literal) const
{
    auto value = literal.get_expr0();
    std::string result = value;

    // get rid of the quotation marks around the string when it was first created!
    if (value[0] == '"' && value[value.size() - 1] == '"')
        result = value.substr(1, value.size() - 2);
    return result;
}

std::any interpreter::visit_unary_expr(const repr::unary &unary) const
{
    auto operand  = evaluate(unary.get_expr1());
    const auto& oper8or = unary.get_expr0();

    switch (oper8or.get_expr0().get_type()) {
        case scanner::token_type::MINUS:
            check_type(value_type::DOUBLE, operand, "Unary expressions expect to get a double as operand!");
            return -std::any_cast<double>(operand);

        case scanner::token_type::BANG:
            check_type(value_type::BOOLEAN, operand, "Unary expressions expect to get a boolean as operand!");
            return !std::any_cast<bool>(operand);
        default:
            throw err(0, "Not a valid unary expression!");
    }
}

std::any interpreter::visit_grouping_expr(const repr::grouping &group) const
{
    return evaluate(group.get_expr0());
}

std::any interpreter::visit_variable_expr(const repr::variable &variable) const
{
    auto variable_name = variable.get_expr0().get_lexeme();
    return environment.read(variable_name);
}

std::any interpreter::visit_print_statement(const stmt::print &st) const
{
    auto value = evaluate(st.get_expr0());

    std::cout << std::any_cast<double>(value) << '\n';

    return 0;
}

std::any interpreter::visit_expression_statement(const stmt::expression &st) const
{
    evaluate(st.get_expr0());

    return 0;
}

std::any interpreter::visit_variable_statement(const stmt::variable &variable) const
{
    std::any value = std::nullopt;
    auto var_name = variable.get_expr0().get_lexeme();

    if (variable.initialized()) value = evaluate(variable.get_expr1());

    environment.write(var_name, value, glox::to_type(value));

    return 0;
}

std::any interpreter::visit_assignment_expr(const repr::assignment &assignment) const
{
    auto var_name = assignment.get_expr0().get_lexeme();
    std::any value = evaluate(assignment.get_expr1());

    if (environment.exists(var_name))
    {
        environment.write(var_name, value, glox::to_type(value));
    }
    else
    {
        throw err(assignment.get_expr0().get_line(), "Tried to write to a variable that doesn't exist: " + var_name);
        return 1;
    }

    return 0;
}
}