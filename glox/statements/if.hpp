//
// Auto-generated by Goksu Guvendiren Bakir.
//

#pragma once

#include <utility>
#include "../token.hpp"
#include "expression.hpp"

namespace glox::stmt
{
class if_statement : public stmt::statement
{
public:
    if_statement(
            std::unique_ptr<repr::expression> expression,
            std::unique_ptr<stmt::statement> then_statement,
            std::unique_ptr<stmt::statement> else_statement,
    ) :
            expression(std::move(expression)),
            then_statement(std::move(then_statement)),
            else_statement(std::move(else_statement)),
    {}

    ~if_statement() = default;

    const repr::expression& get_expression() const { return *expression; }
    const stmt::statement& get_then_statement() const { return *then_statement; }
    const stmt::statement& get_else_statement() const { return *else_statement; }

private:
    std::unique_ptr<repr::expression> expression;
    std::unique_ptr<stmt::statement> then_statement;
    std::unique_ptr<stmt::statement> else_statement;

    std::any accept(const stmt_visitor& visitor) const
    {
        return visitor.visit_if_statement(this);
    }
};
}