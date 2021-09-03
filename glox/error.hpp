//
// Created by Göksu Güvendiren on 8/14/21.
//

#pragma once

#include <string>

namespace glox
{
class err : std::exception
{
public:
    err(int line, const std::string& message);
private:
    void report(int line, const std::string& message);
};
}
