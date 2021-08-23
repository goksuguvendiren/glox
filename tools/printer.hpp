//
// Created by Göksu Güvendiren on 8/22/21.
//

#pragma once

#include <string>
#include "representer/expression.hpp"

namespace glox::tools
{
class printer : glox::repr::visitor<std::string>
{
    std::string to_string(const glox::repr::expression<std::string>& expr)
    {
        return expr.accept(*this);
    }
};
}
