//
// Auto-generated by Goksu Guvendiren Bakir.
//

#pragma once

#include <utility>
#include "../token.hpp"
#include "expression.hpp"

namespace glox::repr
{
class assignment : public repr::expression
{
public:
    assignment(
            std::unique_ptr<scanner::token> expr0,
            std::unique_ptr<repr::expression> expr1
    ) :
    expr0(std::move(expr0)),
    expr1(std::move(expr1))
    {}

    ~assignment() = default;

    const scanner::token& get_expr0() const { return *expr0; }
    const repr::expression& get_expr1() const { return *expr1; }

private:
    std::unique_ptr<scanner::token> expr0;
    std::unique_ptr<repr::expression> expr1;

    std::any accept(const visitor& visitor) const
    {
        return visitor.visit_assignment_expr(*this);
    }
};
}