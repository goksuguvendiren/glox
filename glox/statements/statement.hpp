//
// Created by Göksu Güvendiren on 9/4/21.
//

#pragma once

#include <any>

namespace glox::stmt
{
class print;
class expression;

class visitor
{
public:
    virtual std::any visit_print_statement(const stmt::print& st) const = 0;
    virtual std::any visit_expression_statement(const stmt::expression& st) const = 0;
};

class statement
{
public:
    virtual std::any accept(const visitor& visitor) const = 0;
    virtual ~statement() = default;
};
}
