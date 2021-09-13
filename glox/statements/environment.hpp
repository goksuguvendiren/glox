//
// Created by Göksu Güvendiren on 9/4/21.
//

#pragma once

#include <map>
#include <error.hpp>
#include <utility>

#include "glox.hpp"

namespace glox::stmt
{

class env_variable
{
public:
    env_variable(value_type type, std::any  val) : type(type), value(std::move(val)) {}

    [[nodiscard]]
    std::any get() const { return value; }

private:
    value_type type;
    std::any value;
};

class environment
{
public:
    environment() : enclosing(nullptr) {}

    explicit environment(environment* enc) : enclosing(enc) {}

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

    [[nodiscard]]
    std::any read(const std::string& var_name) const
    {
        auto var = variables.find(var_name);

        // does this environment have the variable?
        if (var != variables.end()) return var->second.get();

        // else, check parents
        if (enclosing) return enclosing->read(var_name);

        // not found anywhere
        throw err(0, "No variable in scope: " + var_name);
    }

    [[nodiscard]]
    bool exists(const std::string& var_name) const
    {
        auto var = variables.find(var_name);
        return (var != variables.end());
    }

    [[nodiscard]]
    auto size() const { return variables.size(); }

    [[nodiscard]]
    environment* parent() const { return enclosing; }

private:
    environment* enclosing;
    std::map<std::string, env_variable> variables;
};
}