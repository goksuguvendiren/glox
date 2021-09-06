//
// Created by Göksu Güvendiren on 9/4/21.
//

#pragma once

#include <map>
#include <error.hpp>

#include "glox.hpp"

namespace glox::stmt
{

class env_variable
{
public:
    env_variable(value_type type, const std::any& val) : type(type), value(val) {}
    std::any get() const { return value; }

private:
    value_type type;
    std::any value;
};

class environment
{
public:
    void write(const std::string& var_name, const std::any& value, value_type var_type)
    {
        if (exists(var_name))
        {
            variables.at(var_name) = env_variable{var_type, value};
        }
        else
        {
            variables.insert(std::make_pair<std::string, env_variable>(var_name.c_str(), env_variable{var_type, value}));
        }
    }

    std::any read(const std::string& var_name) const
    {
        auto var = variables.find(var_name);
        if (var != variables.end()) return var->second.get();

        throw err(0, "No variable in scope: " + var_name);
    }

    bool exists(const std::string& var_name) const
    {
        auto var = variables.find(var_name);
        return (var != variables.end());
    }

    auto size() const { return variables.size(); }
private:
    std::map<std::string, env_variable> variables;
};
}