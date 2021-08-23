//
// Created by Göksu Güvendiren on 8/17/21.
//

#pragma once

namespace glox::repr
{
template <class T>
class binary;

template <class T>
class opr;

template <class T>
class numeric_literal;

template <class T>
class visitor
{
public:
    virtual T visit_binary_expr(const repr::binary<T>& binary) const = 0;
    virtual T visit_opr_expr(const repr::opr<T>& op) const = 0;
    virtual T visit_numeric_literal_expr(const repr::numeric_literal<double>& op) const = 0;
};

template <class T>
class expression
{
public:
    virtual T accept(const visitor<T>& visitor) const = 0;
    virtual ~expression() = default;
};
}
