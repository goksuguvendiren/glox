//
// Created by Göksu Güvendiren on 8/17/21.
//

#pragma once

namespace glox::repr
{
class binary;

template <class T>
class opr;

template <class T>
class visitor
{
public:
    T visit_binary_expr(const glox::repr::binary& binary);
    T visit_operator_expr(const glox::repr::opr<T>& op);
};

template <class T>
class expression
{
public:
    virtual T accept(visitor<T> visitor) = 0;
};
}
